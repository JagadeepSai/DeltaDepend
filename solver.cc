
#ifndef SOLVER_CC
#define SOLVER_CC

#include "ast.hh"
#include "utils.cc" 

void myadd(list<eq_result*>* e1,list<eq_result*>* e2){
    for(auto const& i : *e2){
            e1->push_back(i);
        }
}

class eq_result
{
    public:
    bool notDependent;


    int stmt_ind1;
    int stmt_ind2;
    bool antiD;
    string loop_var;
    eq_result(){
        stmt_ind1 = -1;
        stmt_ind2 = -1;
    }
    ~eq_result();
    void print(){}
};
class ddg
{   
    public:
    list<eq_result*>* edges;
    ddg(){  this->edges = new list<eq_result*>(); }
    ~ddg();
    list<eq_result*>* get_edges(){
        return this->edges;
    }
    void print(){}
    void add_list(list<eq_result*>*e){
        myadd(this->edges,e);
    }
    void add(eq_result* e){
        this->edges->push_back(e);
    }
    void add_ddg(ddg*d){
        this->add_list(d->get_edges());
    }

};

// FIXME: moves these inside ddg and have a header separate header file 
extern list<ARR_Ast*>* Reads,*Writes;
extern list<FOR_Ast*>* Fors;
extern map<string,pair<int,int> > forbounds;
extern map<string,pair<int,int> > stmt_forbounds;

// list<string>* allnames;
// list<ARR_Ast*>* allarrays;
// void init(){
//     // Get all names;
//     list<string>* allnames_reads = get_allnames(Reads);
//     list<string>* allnames_writes = get_allnames(Writes);
//     for (auto const& i : *allnames_writes) {
//         allnames->push_back(i);
//     }
//     for (auto const& i : *allnames_reads) {
//         allnames->push_back(i);
//     }

//     for (auto const& i : *allnames) {
//         allnames->push_back(i);
//     }

//     // 

// }

map<string,int> con_eq(ARR_EQ_Ast* e1){
    map<string,int> res;
    res[""] = e1->get_constant();
    list<string>* var = e1->get_var_names();
    list<int>* coe = e1->get_coeffs();
    list<string>::iterator varit= var->begin();
    list<int>::iterator coeit = coe->begin();
    
    for(;varit != var->end(); varit++, coeit++){
        res[*varit] += *coeit; 
    }
    return res;
}
map<string,int> get_eq(ARR_EQ_Ast* e1, ARR_EQ_Ast* e2){
    // Computes e1 = e2;
    map<string,int> con1 = con_eq(e1);
    map<string,int> con2 = con_eq(e2);
    for ( const auto &mapit : con2 ) {
        con1[mapit.first] -= mapit.second ;
    }
    return con1;
}

ddg* arr_solve(list<ARR_EQ_Ast*>* s1,list<ARR_EQ_Ast*>* s2  ){
    ddg* res = new ddg();
    list<ARR_EQ_Ast*>::iterator eqsit1 = s1->begin(); 
    list<ARR_EQ_Ast*>::iterator eqsit2 = s2->begin(); 

    for(;eqsit1!= s1->end();eqsit1++,eqsit2++){
        res->add( solve_eq( get_eq(*eqsit1,*eqsit2)) );
    }

}

eq_result* solve_eq(map<string,int> eq){
    // Generate the result using various tests
    //TODO:
}

// In these solving fill all the obtainable
// GCD test will 
bool solve_gcd(map<string,int> eq){
    // TODO:

}




void ddg_solve(){
    // init();
    // list<string>* allnames = new list<string>();
    ddg* graph = new ddg();
    string name;
    int stmt_ind;
    list<ARR_EQ_Ast*>* eqs;
    for (auto const& i : *Writes) {
        name = i->get_arr_name();
        stmt_ind = i->get_index();
        eqs = i->get_eqs();
        for (auto const& j : *Reads) {
            if(j->get_arr_name() == name && stmt_ind != j->get_index()){
                graph->add_ddg(arr_solve(eqs,j->get_eqs()));
            }
        
        }
        for (auto const& j : *Writes) {
            if(j->get_arr_name() == name && stmt_ind != j->get_index()){
                //TODO:
            }
        
        }
        
        
    }
    
}

#endif