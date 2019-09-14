#include "ast.hh"
using namespace std;

bool deb=false;
void debug(string s) { if(deb) cout<<s <<endl;}
void space_print(int d){
    for(int i=0;i<d;i++){
        printf("\t");
    }
}






Ast * MAIN = new Ast();
//-------------------------------------------------------------
Ast::Ast(){
    index = 0;
}
Ast::~Ast(){}

int Ast::get_index(){
    return this->index;
}
void Ast::set_index(int i){
    this->index = i;
}
void Ast::print(int l){}

//----------------------------------------------------------------------------
/****** FOR AST ************/
//----------------------------------------------------------------------------
FOR_Ast::FOR_Ast(){
    this->i_start = 0;
    this->i_end = 0;
    this->ind_start = 0;
    this->ind_end = 0;
    this->cond = new Cond_Ast();
    this->iter_name = "$$";
    this->body = new Ast();

}
FOR_Ast::~FOR_Ast(){}

void FOR_Ast::set_i_start(int s){       this->i_start = s;      }
void FOR_Ast::set_i_end(int e){         this->i_end =e ;        }
int FOR_Ast::get_i_start(){             return this->i_start;   }
int FOR_Ast::get_i_end(){               return this->i_end;     }

void FOR_Ast::set_ind_start(int s){     this->ind_start = s;    }
void FOR_Ast::set_ind_end(int e){       this->ind_end =e ;      }
int FOR_Ast::get_ind_start(){           return this->ind_start; }
int FOR_Ast::get_ind_end(){             return this->ind_end;   }

void FOR_Ast::set_iter_name(string s){  this->iter_name = s;    }
string FOR_Ast::get_iter_name(){        return this->iter_name; }

void FOR_Ast::set_body(Ast* b){         this->body = b;         }
Ast * FOR_Ast::get_body(){              return this->body;      }

void FOR_Ast::set_Cond(Cond_Ast * b){   this->cond = b;      }
Cond_Ast* FOR_Ast::get_Cond(){          return this->cond;   }

void FOR_Ast::set_Incre(Incre_Ast * b){ this->Incre = b;    }
Incre_Ast * FOR_Ast::get_Incre(){       return this->Incre; }

string FOR_Ast::check_ast(){
    if(this->iter_name != this->cond->get_var_name() || this->cond->get_var_name() != this->Incre->get_var_name()){
        // cout << this->iter_name << " : "<< this->cond->get_var_name() << " : "<< this->Incre->get_var_name()<<endl;
        return "Different Variables in the FOR loop";
    }
    return "";
}
void FOR_Ast::print(int l){
    if(debug) { cout<< "FOR_Ast print "<<endl; }
    cout<<this->get_index() << ":FOR ( " << this->iter_name << " = " << this->i_start << " ; "; 
    this->cond->print(l); cout << " ; "; this->Incre->print(l);
    cout << " ) "<<endl;
    space_print(l); cout<<" { "<<endl;
    // this->body->print(l+1);
    space_print(l); cout<<" } "<<endl;

    if(debug) { cout<< "FOR_Ast print ENDED"<<endl; }
}
//----------------------------------------------------------------------------
/****** ARR AST ************/
//----------------------------------------------------------------------------
ARR_Ast::ARR_Ast(){
    debug("ARR_Ast CONS");
    this->arr_dim = nested_level = 0;
    this->isSource = false;
    this->arr_name = "_";
    this->eqs = new list<ARR_EQ_Ast*>();
    debug("ENDED");
}
ARR_Ast::~ARR_Ast(){}
void ARR_Ast::set_nested_level(int n){      this->nested_level = n;     }
int ARR_Ast::get_nested_level(){            return this->nested_level;  }

void ARR_Ast::set_arr_dim(int n){           this->arr_dim = n;          }
int ARR_Ast::get_arr_dim(){                 return this->arr_dim;       }
void ARR_Ast::add_arr_dim(int v){           this->arr_dim += v;         }

void ARR_Ast::set_isSource(bool b){         this->isSource = b;         }
bool ARR_Ast::get_isSource(){               return this->isSource;      }
void ARR_Ast::set_arr_name(string a){       this->arr_name = a;         }
string ARR_Ast::get_arr_name(){             return this->arr_name;      }

void ARR_Ast::add_eqs(ARR_EQ_Ast* eq){
        debug("ARR_Ast Add EQ");             
        this->eqs->push_back(eq); 
        debug("ENDED");     
    }
list<ARR_EQ_Ast*>* ARR_Ast::get_eqs(){  return this->eqs; }


void ARR_Ast::print(int l){
    cout<< this->arr_name << " ";
    list<ARR_EQ_Ast*>::iterator eq_iter = this->eqs->begin();
    for(;eq_iter != this->eqs->end(); eq_iter ++){
        cout<<"[ ";
        (*eq_iter)->print(l);
        cout<<" ]";
    }
    cout<<" ";
    debug("ENDED");     
}





//-------------------------------------------------------------------------------------------
Cond_Ast::Cond_Ast(){}
Cond_Ast::~Cond_Ast(){}

Cond_Ast::Cond_Ast(Comp_ops c, string s, int a){
    this->value = a;
    this->var_name = s;
    this->op = c;
}

void Cond_Ast::set_var_name(string s){          this->var_name = s; }
string Cond_Ast::get_var_name(){                return this->var_name; }

void Cond_Ast::set_value(int a){                this->value = a; }
int Cond_Ast::get_value(){                      return this->value; }

void Cond_Ast::set_Comp_ops(Comp_ops c){        this->op = c;   }
Comp_ops Cond_Ast::get_Comp_ops(){              return this->op; }

void Cond_Ast::print(int l){
    cout<<" " <<this->var_name;
    switch (this->op)
    {
    case 0: cout<<" < "; break;
    case 1: cout<<" <= "; break;
    case 2: cout<<" > "; break;
    case 3: cout<<" >= "; break;
    case 4: cout<<" == "; break;
    case 5: cout<<" != "; break;
    default: break;
    }

    cout<<" " << this->value;
}
//-------------------------------------------------------------------------------------------

Incre_Ast::Incre_Ast(){}
Incre_Ast::Incre_Ast(string s,bool b){          this->var_name = s;   this->isIncre = b;  }
Incre_Ast::~Incre_Ast(){ }

void Incre_Ast::set_var_name(string s){         this->var_name = s; }
string Incre_Ast::get_var_name(){               return this->var_name;  }

void Incre_Ast::set_isIncre(bool s){            this->isIncre = s;      }
bool Incre_Ast::get_isIncre(){                  return this->isIncre;   }

void Incre_Ast::print(int l){
    cout<< " " << this->var_name << " ";
    if(this->isIncre) cout<< "++ "; else cout<<"-- ";
}

// ---------------------------------------------------------------------------------------

ARR_EQ_Ast::ARR_EQ_Ast(){   
    debug("ARR_EQ_Ast CONST NIL ");     
    this->var_names = new list<string>() ;
    this->coeffs = new list<int>() ;
    this->consta = 0;
    debug("ENDED");     
}
ARR_EQ_Ast::~ARR_EQ_Ast(){}

ARR_EQ_Ast::ARR_EQ_Ast(string s,int l){
    debug("ARR_EQ_Ast CONST STRING INT ");
    this->var_names = new list<string>() ;
    this->coeffs = new list<int>() ;
    this->var_names->push_back(s);
    this->coeffs->push_back(l);  
    debug("ENDED");     
}
ARR_EQ_Ast::ARR_EQ_Ast(int c){ 
    debug("ARR_EQ_Ast CONST CONSTANT ");     
    this->var_names = new list<string>() ;
    this->coeffs = new list<int>() ;
    this->consta =c ;
    debug("ENDED");     
}   
list<string>* ARR_EQ_Ast::get_var_names() { return this->var_names; }
list<int>* ARR_EQ_Ast::get_coeffs(){        return this->coeffs;  }

void ARR_EQ_Ast::add_pair(string s,int c){
    this->var_names->push_back(s);
    this->coeffs->push_back(c);
}
void ARR_EQ_Ast::set_constant(int s){
    this->consta = s;
}
int ARR_EQ_Ast::get_constant(){
    return this->consta;
}

string ARR_EQ_Ast::check_ast(){
    if(this->var_names->size() != this->coeffs->size()) {
        return "Mismatch of Equations";
    }

    return "";
}

void ARR_EQ_Ast::make_neg(bool all){
    if(this->coeffs->size() == 0) { 
        this->consta *= -1;
    }else{ 
        int temp;
        if(all){
            //TODO:
            // for(;c_iter != this->end(); var_iter++){
        }else {
            temp = this->coeffs->front();
            this->coeffs->pop_front();
            this->coeffs->push_front(-temp);
        }
    }
}
void ARR_EQ_Ast::merge(ARR_EQ_Ast * expr){
    debug("ARR_EQ_Ast merge");
    list<string> * v = expr->get_var_names();
    list<int> * c = expr->get_coeffs();
    list<string>::iterator var_iter = v->begin();
    list<int>::iterator coff_iter = c->begin();
    
    for(;var_iter != v->end(); var_iter++,coff_iter++){
        this->var_names->push_back(*var_iter);
        this->coeffs->push_back(*coff_iter);
    }

    this->consta += expr->get_constant();
    debug("ENDED");     
}

void ARR_EQ_Ast::print(int l){
    debug("ARR_EQ_Ast print");
    
    list<string>::iterator var_iter = this->var_names->begin();
    list<int>::iterator coff_iter = this->coeffs->begin();
    for(;var_iter != this->var_names->end();var_iter++,coff_iter++){
        cout<<*coff_iter<< "*" <<*var_iter<<" + ";
    }
    cout<<this->consta;
    debug("ENDED");     
    
}
// //----------------------------------------------------------------------------
// /****** NUM AST ************/
// //----------------------------------------------------------------------------
// Num_Ast::Num_Ast(){ }
// Num_Ast::Num_Ast(int v){                     this->value = v;        }
// Num_Ast::~Num_Ast(){ }

// void Num_Ast::set_value(int a){              this->value = a;        }
// int Num_Ast::get_value(){                    return this->value;     }

// void Num_Ast::print(int l){
//     cout<< this->value;
// }



// //----------------------------------------------------------------------------
// /****** ASSIGN AST ************/
// //----------------------------------------------------------------------------
// Assign_Ast::Assign_Ast(){ }
// Assign_Ast::~Assign_Ast(){ }

// void Assign_Ast::set_var_name(string s){       this->var_name = s;      }
// string Assign_Ast::get_var_name(){             return this->var_name;   }    

// void Assign_Ast::set_value(Ast* a){              this->value = a;        }
// Ast* Assign_Ast::get_value(){                    return this->value;     }

// void Assign_Ast::print(int l){
//     space_print(l); cout<< this->var_name << " = " ; 
//     this->value->print(l);
//      cout<<endl;
// }