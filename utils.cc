
#ifndef UTILS_CC
#define UTILS_CC

#include "ast.hh"
#include <map>

extern list<ARR_Ast*>* Reads,*Writes;
extern list<FOR_Ast*>* Fors;

list<string>* get_allnames(list<ARR_Ast*>* a) {
    map<string,bool> temp;
    list<string>* ret = new list<string>();
    for (auto const& i : *a) {
            temp[i->get_arr_name()] = true;
    }
    for ( const auto &myPair : temp ) {
        ret->push_back(myPair.first);
    }

    return ret;
}

list<ARR_Ast*>* get_arr(string name,list<ARR_Ast*>* a,int ind = -1){
    list<ARR_Ast*>* ret = new list<ARR_Ast*>();
    for (auto const& i : *a) {
        if((i->get_arr_name() == name)){
            if(ind != -1 && ind != i->get_index()){
                ret->push_back(i);
            }
        }
    }
    return ret;
}

#endif