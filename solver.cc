
#ifndef SOLVER_CC
#define SOLVER_CC

#include "ast.hh"
#include "utils.cc" 

extern list<ARR_Ast*>* Reads,*Writes;
extern list<FOR_Ast*>* Fors;
map<int,list<string>*> fornests;


list<string>* allnames;
// list<ARR_Ast*>* allarrays;
void init(){
    // Get all names;
    list<string>* allnames_reads = get_allnames(Reads);
    list<string>* allnames_writes = get_allnames(Writes);
    for (auto const& i : *allnames_writes) {
        allnames->push_back(i);
    }
    for (auto const& i : *allnames_reads) {
        allnames->push_back(i);
    }

    for (auto const& i : *allnames) {
        allnames->push_back(i);
    }

    // 

}
bool solve_exact(){

}


void ddg(){
    init();
    // list<string>* allnames = new list<string>();
    
    
}

#endif