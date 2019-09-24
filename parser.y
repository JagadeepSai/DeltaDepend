%{
    #include <stdio.h>
    #include <queue>
    #include <stack>
    #include <map>
    using namespace std;
    extern "C" void yyerror(char *);
    extern FILE * yyin;
    extern int yylex(void);
    extern int yylineno;
    int yyerror (const char *error )
    {
        fprintf ( stderr, "\tError: %s ,detected at line %d\n", error, yylineno );
        exit ( EXIT_FAILURE );
    }

    int nlevel ;  // Nested Level 
    int cur_index;
    stack<FOR_Ast*> index_scope;
    list<ARR_Ast*>* Reads,*Writes;
    list<FOR_Ast*>* Fors;
    map<string,pair<int,int> > forbounds;
    map<string,pair<int,int> > stmt_forbounds;
    map<string,int> arr_dims ; // For checking purposes

        string check_arr_index(string name,int cur_index){
            if(forbounds.find(name) == forbounds.end()){ 
                    return "Variable in array not found" ;
                }else{
                    pair<int,int> forb = stmt_forbounds[name];
                    if(forb.first < cur_index){
                        if(forb.second !=-1 && forb.second < cur_index){
                            return "Variable in Array out of scope";
                        }
                    }
                }
                return "";
        }

        string check_arr_dim(string name,int cur_dim){
            if(arr_dims.find(name) != arr_dims.end()){
                if(arr_dims[name] != cur_dim){
                    return "Array dimensions mismatch";
                }
            }
            return "";
        }

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

%type <AST> STMT PROG STMTs ARR_STMT FOR_STMT
%type <COND_AST> COND
%type <INC_AST> INCRE
%type <ARR_INDEX_EQ_AST> ARR_INDEX_EQ
%type <ARR_AST> ARRAY ARRAY1 ARRSUM 
%type <FOR_Ast> FOR


// %type  <AST> ASSIGN_VALUE ARR_INDEX_EQ STMT ASSIGN_STMT COND FUNCCALL
// %type  <ASTLIST> STMTs ARR_INDEX_EQLIST ARR_INDEX_EQLIST1
// %type  <STE_LIST> VARDEC VARDEC1 PARAMSt PARAMS PARAMS1 DECLS VARDECS

%right ASSIGN_OP   
%left  '+' '-'
// %left  '*' '/'


// %expect 1 // Just expecting 1 shift reduce conflict ( Used for if-else shift reduce conflict)

%start PROG

%%
PROG : STMT {
                MAIN = $1;
            }
STMT : 
    '{' STMTs '}' { $$ = new Ast(); }
    | FOR_STMT {$$ = $1;} 
    | ARR_STMT {$$ = $1;}
    
STMTs: 
    STMTs STMT      {$$=$1;}
    |               {$$=new Ast();}
    ;

// --------------------------------- Array ---------------------------------------------------------

ARR_INDEX_EQ : 
     INTEGER_NUMBER '*' NAME { 
                                    $$ = new ARR_EQ_Ast(*$3,$1);    
                                    string err = check_arr_index(*$3,cur_index);                  
                                    if(err != ""){ yyerror(err.c_str()); }               
                             }
    | ARR_INDEX_EQ '+' ARR_INDEX_EQ           { $1->merge($3); $$=$1;    }  
    | ARR_INDEX_EQ '-' ARR_INDEX_EQ           { $3->make_neg(false); $1->merge($3); $$=$1;  }    
    | NAME                    {     
                                    $$ = new ARR_EQ_Ast(*$1,1); 
                                    string err = check_arr_index(*$1,cur_index);                  
                                    if(err != ""){ yyerror(err.c_str()); }
                                }
    | INTEGER_NUMBER          { $$ = new ARR_EQ_Ast($1);                      }      


ARR_STMT : 
    ARRAY ASSIGN_OP ARRSUM ';'    {     cur_index++;
                                        $1->set_isSource(true); Writes->push_back($1); $$= new Ast();
                                  }

ARRSUM :
    ARRAY '+' ARRSUM { 
                        $1->set_isSource(false); Reads->push_back($1); $$ = new ARR_Ast();
                    }
    | ARRAY { $1->set_isSource(false); Reads->push_back($1); $$ = new ARR_Ast(); }
    
ARRAY : 
    NAME '[' ARR_INDEX_EQ ARRAY1 {  
                                    $4->set_arr_name(*$1);
                                    $4->add_arr_dim(1);
                                    string err = check_arr_dim(*$1,$4->get_arr_dim());                  
                                    if(err != ""){ yyerror(err.c_str()); } 
                                    arr_dims[*$1] = $4->get_arr_dim();
                                    $4->add_eqs($3);
                                    $4->set_nested_level(nlevel);
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
                        arr->set_index(cur_index);
                        $$ = arr;
                    }


// --------------------------------- For Loop ---------------------------------------------------------

FOR_STMT : 
    FOR '(' NAME ASSIGN_OP INTEGER_NUMBER ';' COND ';' INCRE ')' 
    
    {   string name = *$3;
        int i_start = $5, i_end = $7->get_value();

        FOR_Ast * forloop = new FOR_Ast();      // Making the For Ast
        forloop->set_iter_name(name);
        forloop->set_i_start(i_start);
        forloop->set_i_end(i_end);
        forloop->set_Cond($7);
        forloop->set_Incre($9);
        forloop->set_nested_level(nlevel);
        forloop->set_ind_start(cur_index);    
        forloop->set_index(cur_index); 
        
        string err = forloop->check_ast();       // Checking the For Ast 
        if(err != "") { yyerror(err.c_str()); }
        if(forbounds.find(name) != forbounds.end()){ 
            yyerror("iterator variables must be different");
        }else {
            forbounds[name] = make_pair(i_start,i_end);
            stmt_forbounds[name] = make_pair(cur_index,-1);                        
        }

        
        nlevel++;
        cur_index++;

        Fors->push_back(forloop); // Adding to the For list
        index_scope.push(forloop);

        // $$ = new Ast();   //Hack
    }  
    STMT {              FOR_Ast * forloop = index_scope.top();
                        forloop->set_ind_end(cur_index);
                        stmt_forbounds[forloop->get_iter_name()] = make_pair(forloop->get_ind_start(), forloop->get_ind_end());                        
                        nlevel--;
                        cur_index++;
                        index_scope.pop();
                        $$ = new FOR_Ast();
                    }

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

%%

void print_reads(){
    // list<ARR_Ast*> Reads
    list<ARR_Ast*>::iterator it = Reads->begin();
    for(;it != Reads->end();it++){
        (*it)->print(0);
        cout<<endl;
    }
}

void print_writes(){
    list<ARR_Ast*>::iterator it = Writes->begin();
    for(;it != Writes->end();it++){
        (*it)->print(0);
        cout<<endl;
    }
}

void print_fors(){
    list<FOR_Ast*>::iterator it = Fors->begin();
    for(;it != Fors->end();it++){
        (*it)->print(0);
        cout<<endl;
    }
}

int main(int argc,char* argv[])
{   
    nlevel = 0;
    cur_index = 0;
    Reads = new list<ARR_Ast*>(); 
    Writes = new list<ARR_Ast*>();
    Fors = new list<FOR_Ast*>();

    bool toprint = true;
    yyin = fopen(argv[1],"r");
    int ret = yyparse();

    if(ret==0){
        if(toprint){
        printf("Reads: ------------------------------------------ \n\n"); print_reads(); 
        printf("Writes: ------------------------------------------ \n\n"); print_writes(); 
        printf("Fors: ------------------------------------------ \n\n"); print_fors(); 
        // MAIN->print(0);
        printf("\n");
        }
    }
    else{
        printf("Error: %d Syntax Error \n",ret);
        exit(0);
    }
  return 1;
}

