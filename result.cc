#include "result.hh"

eq_result::eq_result(){
    this->stmtInd1 = -1;
    this->stmtInd2 = -1;
}
eq_result::~eq_result(){}

bool eq_result::getNotDependent(){      return this->notDependent;  }
int eq_result::getStmtInd1(){           return this->stmtInd1;      }
int eq_result::getStmtInd12(){          return this->stmtInd2;      }
bool eq_result::getAntiD(){             return this->antiD;         }
map<string,int> eq_result::getDist(){   return this->dist;          }
string eq_result::getLoopVar(){         return this->loopVar;       }

void  eq_result::setNotDependent(bool b){   this->notDependent = b; }
void  eq_result::setStmtInd1(int a){        this->stmtInd1 = a;     }
void  eq_result::setStmtInd12(int a){       this->stmtInd2 = a;     }
void  eq_result::setAntiD(bool b){          this->antiD = b;        }
void  eq_result::setDist(map<string,int> a){this->dist = a;         }
void  eq_result::setLoopVar(string s){      this->loopVar = s;      }

void eq_result::print(){}

ddg::ddg(){  this->edges = new list<eq_result*>(); }
ddg::~ddg(){}
list<eq_result*>* ddg::getEdges(){      return this->edges;             } 
void ddg::addList(list<eq_result*>*e){  myadd(this->edges,e);           }
void ddg::addE(eq_result* e){           this->edges->push_back(e);      }
void ddg::addDDG(ddg*d){                this->addList(d->getEdges());   }

void ddg::print(){}