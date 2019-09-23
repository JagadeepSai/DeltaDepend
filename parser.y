%{
    #include <stdio.h>
    #include <queue>
    using namespace std;
    extern "C" void yyerror(char *);
    extern FILE * yyin;
    extern int yylex(void);
    extern int yylineno;
    int yyerror (const char *error )
    {
        fprintf ( stderr, "\tError: %s detected at line %d\n", error, yylineno );
        exit ( EXIT_FAILURE );
    }

    int global_index ;  // For Scopes 
    int cur_index;
    queue<int > index_scope;
    list<ARR_Ast*> Reads,Writes;
    list<FOR_Ast*> Fors;

%}
%code requires {
    #include "headers.h"
}
%union{
    string *    stringer;
    char        character;
    int         integer;
    struct Ast*    AST;
    struct Cond_Ast*    COND_AST;
    struct Incre_Ast*   INC_AST;
    struct ARR_EQ_Ast*    ARR_INDEX_EQ_AST;
    struct ARR_Ast*     ARR_AST;
    list <Ast*>*   ASTLIST;
    list<Symbol_Table_Entry*>* STE_LIST;

}


%token INTEGER ASSIGN_OP
%token GTE LTE LT GT EQ NEQ NOT
%token FOR 
%token <stringer>  NAME 
%token <integer>   INTEGER_NUMBER 

%type <AST> STMT PROG FOR STMTs ARR_STMT
%type <COND_AST> COND
%type <INC_AST> INCRE
%type <ARR_INDEX_EQ_AST> ARR_INDEX_EQ
%type <ARR_AST> ARRAY ARRAY1 ARRSUM 


// %type  <AST> ASSIGN_VALUE ARR_INDEX_EQ STMT ASSIGN_STMT COND FUNCCALL
// %type  <ASTLIST> STMTs ARR_INDEX_EQLIST ARR_INDEX_EQLIST1
// %type  <STE_LIST> VARDEC VARDEC1 PARAMSt PARAMS PARAMS1 DECLS VARDECS

%right ASSIGN_OP   
%left  '+' '-'
// %left  '*' '/'


// %expect 1 // Just expecting 1 shift reduce conflict ( Used for if-else shift reduce conflict)

%start PROG

%%
PROG : ARR_STMT {
                MAIN = $1;
            }
STMT : 
    '{' STMTs '}' { $$ = new Ast(); }
    | FOR '(' NAME ASSIGN_OP INTEGER_NUMBER ';' COND ';' INCRE ')' 
    
    {   string name = *$3;
        int i_start = $5, i_end = $7->get_value();

        FOR_Ast * forloop = new FOR_Ast();      // Making the For Ast
        forloop->set_iter_name(name);
        forloop->set_i_start(i_start);
        forloop->set_i_end(i_end);
        forloop->set_Cond($7);
        forloop->set_Incre($9);
                                                
        string err = forloop->check_ast();       // Checking the For Ast 
        if(err != "") { yyerror(err.c_str()); }
        // forloop->print(global_index); // Printing 

        // TODO: Change the increment Conditions
        forloop->set_ind_start(global_index);     
        index_scope.push(global_index);
        global_index++;

        Fors.push_back(forloop); // Adding to the For list
        
        // $$ = new Ast();   //Hack
    }  
    STMT {
                        global_index--;
                        index_scope.pop();
                    }
    
STMTs: 
    STMTs STMT      {$$=$1;}
    |               {$$=new Ast();}
    ;

// --------------------------------- Array ---------------------------------------------------------

ARR_INDEX_EQ : 
     INTEGER_NUMBER '*' NAME { $$ = new ARR_EQ_Ast(*$3,$1);                   }
    | ARR_INDEX_EQ '+' ARR_INDEX_EQ           { $1->merge($3); $$=$1;    }  
    | ARR_INDEX_EQ '-' ARR_INDEX_EQ           { $3->make_neg(false); $1->merge($3); $$=$1;  }    
    | NAME                    { $$ = new ARR_EQ_Ast(*$1,1);                   }
    | INTEGER_NUMBER          { $$ = new ARR_EQ_Ast($1);                      }      


ARR_STMT : 
    ARRAY '=' ARRSUM ';'    { Writes.push_back($1); $$= new Ast();}

ARRSUM :
    ARRAY '+' ARRSUM {  Reads.push_back($1); $$ = new ARR_Ast();}
    | ARRAY { $1->set_isSource(false); Reads.push_back($1); $$ = new ARR_Ast(); }
    


// EXPR : 
//        EXPR '-' EXPR 
//     |  EXPR '+' EXPR 
//     | NAME            
//     | INTEGER_NUMBER 
//     | ARRAY 

ARRAY : 
    NAME '[' ARR_INDEX_EQ ARRAY1 {  
                                    $4->set_arr_name(*$1);
                                    $4->add_arr_dim(1);
                                    $4->add_eqs($3);
                                    $$ = $4;
                                }

ARRAY1 : 
    ']' '[' ARR_INDEX_EQ ARRAY1 {      
                                $4->add_eqs($3); 
                                $4->add_arr_dim(1);
                                $$ = $4;
                         }
    | ']'            { 
                        ARR_Ast * arr = new ARR_Ast(); 
                        arr->set_index(global_index);
                        $$ = arr;
                    }


// --------------------------------- For Loop ---------------------------------------------------------
INCRE : 
    NAME '+''+'   { $$ = new Incre_Ast(*$1,true); }
    | NAME '-''-'   { $$ = new Incre_Ast(*$1,false); }
      

COND : 
    '(' COND ')'                    { $$ = $2; } 
    | NAME LT   INTEGER_NUMBER        { $$ = new Cond_Ast(le,*$1,$3); } 
    | NAME LTE  INTEGER_NUMBER        { $$ = new Cond_Ast(leq,*$1,$3); } 
    | NAME GT   INTEGER_NUMBER        { $$ = new Cond_Ast(gt,*$1,$3); } 
    | NAME GTE  INTEGER_NUMBER        { $$ = new Cond_Ast(gtq,*$1,$3); } 
    | NAME EQ   INTEGER_NUMBER        { $$ = new Cond_Ast(eq,*$1,$3); } 
    | NAME NEQ  INTEGER_NUMBER        { $$ = new Cond_Ast(neq,*$1,$3); } 
    | NOT COND                        { $2->negate(); $$=$2; }


// STMT:
//     | '{' STMTs '}'                     {  
//                                             
//                                         }
//     | FOR '(' ASSIGN_STMT ';' COND ';' ASSIGN_STMT ')' STMT { 
//                                             
//                                         }
//     ;



%%

int main(int argc,char* argv[])
{   
    global_index = 0;
    cur_index = 0;
    yyin = fopen(argv[1],"r");
    int ret = yyparse();
    if(ret==0){
        printf("AST: ------------------------------------------ \n\n"); 
        // MAIN->print(0);
        printf("\n");
    }
    else{
        printf("Error: %d Syntax Error \n",ret);
        exit(0);
    }
  return 1;
}