
#ifndef RESULT_HH
#define RESULT_HH

#include "ast.hh"

class eq_result
{   
    
    bool notDependent;
    int stmtInd1;
    int stmtInd2;
    bool antiD;
    map<string,int> dist;
    string loopVar;

    public:
    eq_result();
    ~eq_result();
    
    bool getNotDependent();
    int getStmtInd1();
    int getStmtInd12();
    bool getAntiD();
    map<string,int> getDist();
    string getLoopVar();

    void  setNotDependent(bool b);
    void  setStmtInd1(int a);
    void  setStmtInd12(int a);
    void  setAntiD(bool b);
    void  setDist(map<string,int> a);
    void  setLoopVar(string s);

    void print();


}; 
void myadd(list<eq_result*>* e1,list<eq_result*>* e2){
    for(auto const& i : *e2){
            e1->push_back(i);
        }
}


class ddg
{   
    
    list<eq_result*>* edges;
    public:
    ddg();
    ~ddg();
    list<eq_result*>* getEdges();
    void setEdges(list<eq_result*>*);
    void addList(list<eq_result*>*e);
    void addE(eq_result* e);
    void addDDG(ddg*d);
    void print();

};

#endif          