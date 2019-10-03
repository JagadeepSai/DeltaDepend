
// #ifndef SOLVER_CC
// #define SOLVER_CC

// #include "ast.hh"
#include "result.hh"
// #include "utils.cc" 
#include <algorithm> 

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




void printEq(map<string,int> eq){
    cout<<" ";
    for(auto const &i: eq){
        cout<<i.second<<"*"<<i.first<<" ";
    }
}
map<string,int> convertEq(ARR_EQ_Ast* e1){
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
map<string,int> subtractEq(map<string,int> con1,map<string,int> con2){
    // Computes e1 = e2;
    for ( const auto &mapit : con2 ) {
        con1[mapit.first] -= mapit.second ;
    }
    return con1;
}
bool isConstantDist(map<string,int> d){
    bool check;
    for(auto const&i:d){
        if(i.second != 0){
            if(i.first == ""){
                check = true;
            }else{
                return false;
            }
        } 
    }
    return check;
}
map<string,int> renameEq(map<string,int> eq,string suffix){
// Adds  Suffix to the equation 
    map<string, int> newEq;
    for (auto const& i : eq){
        newEq[i.first + suffix] = i.second;
    }
    return newEq;
}
map<string,int> getEq(map<string,int> con1, map<string,int> con2){
    map<string,int> eq1 = renameEq(con1,"1");
    map<string,int> eq2 = renameEq(con2,"2");
    
    // After Renaming we get the equation
    return subtractEq(eq1,eq2);
}

bool solveGcd(map<string,int> eq){
    // NOTE: Equation is of the form ax+by = c;
    int a[2]; int temp = 0;
    for(auto const & i : eq){
        if(i.first != "") { a[temp] = i.second; temp++;  }
    }
    return (eq[""] % __gcd(a[0], a[1])) == 0;
}

bool solveBanarjee(map<string,int>eq){

}





eq_result* solveEq(map<string,int> eq){
    // Generate the result using various tests
    //TODO:
    eq_result * ans = new eq_result();
    if (eq.size() == 3){
        if(solveGcd(eq)){

        }else {
            ans->setNotDependent(true);
            return ans;
        }
    }

}


ddg* arrSolve(list<ARR_EQ_Ast*>* s1,list<ARR_EQ_Ast*>* s2  ){
    ddg* res = new ddg();
    eq_result * temp;
    list<ARR_EQ_Ast*>::iterator eqsit1 = s1->begin(); 
    list<ARR_EQ_Ast*>::iterator eqsit2 = s2->begin(); 

    for(;eqsit1!= s1->end();eqsit1++,eqsit2++){
        map<string,int> con1 = convertEq(*eqsit1);
        map<string,int> con2 = convertEq(*eqsit2);
        map<string,int> eq   =  getEq(con1,con2);
        map<string,int> dist = subtractEq(con1,con2);
        if(isConstantDist(dist)){
            temp = solveEq(eq);
            if(solveGcd(eq)){

            }
            if (! temp->getNotDependent) res->addE( temp );
        }
        
    }

}

// In these solving fill all the obtainable
// GCD test will 


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
                graph->addDDG(arrSolve(eqs,j->get_eqs()));
            }
        
        }
        for (auto const& j : *Writes) {
            if(j->get_arr_name() == name && stmt_ind != j->get_index()){
                //TODO:
            }
        
        }
        
        
    }
    
}

// #endif