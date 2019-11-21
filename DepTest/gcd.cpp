#include <iostream> 
#include <string>
#include <vector> 
#include <map> 
#include "gcd.h"


using namespace std;
int getGCD(int a, int b) //2 variables a,b of LDE
{ 
    if (b == 0) {
       return a; 
    }
   else if (a == 0) {
       return b; 
   }
   else if (a == b) {
        return a; 
   }else if (b > a){
    return getGCD(a, b-a); 
   } 
    return getGCD(a-b, b); 
} 
//returns true if dependent as per gcd test else returns false
bool GcdTest(int a, int b, int c){
    int gcd=getGCD(a,b);
    if(c%gcd==0)
        return true;
    else
        return false;
}

bool GcdTestV(std::vector<int> v){
    return GcdTest(v[0],v[1],v[2]);
}

bool GcdTestMulU(std::vector<std::vector<int>> v){
    bool dependent=false;
    for (int i = 0; i < v.size(); i++) { 
            dependent= dependent || GcdTest(v[i][0],v[i][1],v[i][2]);
        }
        return dependent;
}

bool GcdTestMulI(std::vector<std::vector<int>> v){
    bool dependent=true;
    for (int i = 0; i < v.size(); i++) { 
            dependent= dependent && GcdTest(v[i][0],v[i][1],v[i][2]);
        }
        return dependent;
}


//************************************************************************************************
//EXACT TEST
//************************************************************************************************
std::vector<int> getFirstSol(int a, int b,int gcd){
std::vector<int> sol;
    for (int i = (-gcd*10); i * a <= gcd*10; i++) {
        if(i==0)
            continue; 

        if ((gcd - (i * a) % b == 0) && (gcd - (i * a))!=0) { 
            //cout<<"i:"<<i<<"  and "<<y0<<endl;
            int x0=i;
            int y0=(gcd - (i * a)) / b;
            sol.push_back(x0);
            sol.push_back(y0);
            //cout<<"xoyo:"<<x0<<"  and "<<y0<<endl;
            
            return sol; 
        } 
    } 
  
}

std::vector<int> Exact(int a, int b, int c, int lb, int ub){

std::vector<int> bounds;
/*get gcd(a,b)
solve ax + by = gcd (a, b), x0,y0
*/
int gcd=getGCD(a,b);
//cout<<"gcd:"<<gcd<<endl;
int cDash=c/gcd;
//cout<<"cDash:"<<cDash<<endl;

std::vector<int> x0y0=getFirstSol(a,b,gcd);
int x0=x0y0[0];
int y0=x0y0[1];
//intittalization of general solution
//x0=2;
//y0=-3;
int t=0;
int xg = cDash*x0 - b*t;
int yg = cDash*y0 + a*t;
//check for 4 inequalities
// lb<=xg lb<=yg xg<=ub yg<=ub
float tupper1=(cDash*x0-lb)/float(b);
float tlower1=(cDash*x0-ub)/float(b);
float tupper2=(ub-cDash*y0)/float(a);
float tlower2=(lb-cDash*y0)/float(a);
int up=0,lo=0;
//cout<<"lo1: "<<tlower1<<endl<<"lo2: "<<tlower2<<endl<<"up1: "<<tupper1<<endl<<"up2: "<<tupper2<<endl;
if(tupper1>tupper2){
    up=tupper2;
}else{
    up=tupper1;
}
if(tlower1<tlower2){
    lo=tlower2+0.5;
}
else{
    lo=tlower1+0.5;
}
//cout<<"lower:"<<lo<<endl<<"upper:"<<up<<endl;
if(lo<=up){
bounds.push_back(lo);
bounds.push_back(up);
}
return bounds;
} 



std::vector< std::vector<int>> ExactSourceSink(int a, int b, int c, int lb, int ub){

std::vector<std::vector<int>> sourceSinkVec;
/*get gcd(a,b)
solve ax + by = gcd (a, b), x0,y0
*/
int gcd=getGCD(a,b);
//cout<<"gcd:"<<gcd<<endl;
int cDash=c/gcd;
//cout<<"cDash:"<<cDash<<endl;

std::vector<int> x0y0=getFirstSol(a,b,gcd);
int x0=x0y0[0];
int y0=x0y0[1];
//intittalization of general solution
//x0=2;
//y0=-3;
int t=0;
int xg = cDash*x0 - b*t;
int yg = cDash*y0 + a*t;
//check for 4 inequalities
// lb<=xg lb<=yg xg<=ub yg<=ub
float tupper1=(cDash*x0-lb)/float(b);
float tlower1=(cDash*x0-ub)/float(b);
float tupper2=(ub-cDash*y0)/float(a);
float tlower2=(lb-cDash*y0)/float(a);
int up=0,lo=0;
//cout<<"lo1: "<<tlower1<<endl<<"lo2: "<<tlower2<<endl<<"up1: "<<tupper1<<endl<<"up2: "<<tupper2<<endl;
if(tupper1>tupper2){
    up=tupper2;
}else{
    up=tupper1;
}
if(tlower1<tlower2){
    lo=tlower2+0.5;
}
else{
    lo=tlower1+0.5;
}
//cout<<"lower:"<<lo<<endl<<"upper:"<<up<<endl;
if(lo<up){
//bounds.push_back(lo);
//bounds.push_back(up);
}

//Test for each iteration
for(t=lo;t<=up;t++){
    //cout<<"t:"<<t<<endl;
    xg = cDash*x0 - b*t;
    yg = cDash*y0 + a*t;
    std::vector<int> v;
    v.push_back(xg);
    v.push_back(yg);
    sourceSinkVec.push_back(v);
}
return sourceSinkVec;
} 


map<string, string> ExactDirectionVector(int a, int b, int c, int lb, int ub){
  std::vector<std::vector<int>> xv=ExactSourceSink(a,b,c,lb,ub);
  string forward="no";
  string backward="no";
  string loopindependent="no";
     for (int i = 0; i < xv.size(); i++) { 
            if(xv[i][0]<xv[i][1])
                forward="yes";
            if(xv[i][0]>xv[i][1])
                backward="yes";
            if(xv[i][0]==xv[i][1])
                loopindependent="yes";
        }

map<string, string> deps;

deps.insert(make_pair("forward", forward));
deps.insert(make_pair("backward", backward));
deps.insert(make_pair("loopindependent", loopindependent));
return deps;
}

bool isDependentExact(int a, int b, int c, int lb, int ub){
      bool dep=false;
      map<string,string> deps=ExactDirectionVector(a,b,c,lb,ub);
      if(deps["forward"]=="yes")
        dep=true;
      if(deps["backward"]=="yes")
        dep=true;
      if(deps["loopindependent"]=="yes")
        dep=true;
     return dep;   


}


int main(){
vector<vector<int> > vect{ { 2, 2, 3 }, 
                               { 4, 5, 6 }, 
                               { 7, 8, 9 } };
  vector<int> vc={2,4,5};
  bool des=GcdTestV(vc);                             
  cout<<"gcdVFalse:   "<<des<<endl;
  bool dependent=GcdTest(2,4,6);
  cout<<"gcdTrue:   "<<dependent<<endl;
  dependent=GcdTest(2,4,5);  
  cout<<"gcdFalse:  "<<dependent<<endl;
  dependent=GcdTestMulI(vect);                              
  cout<<"GcdMulITrue: "<<dependent<<endl;
  dependent=GcdTestMulU(vect);                              
  cout<<"GcdMulUTrue: "<<dependent<<endl;
  std::vector<int> v=getFirstSol(5,3,1);
  cout<<"xoyo:"<<v[0]<<"  and "<<v[1]<<endl;


  //exact
  std::vector<int> x=Exact(5,3,120,0,100);
  std::vector<std::vector<int>> xv=ExactSourceSink(5,3,120,0,100);
   for (int i = 0; i < xv.size(); i++) { 
            //cout<<"source:" << xv[i][0]<<" and Sink:   "<<xv[i][1]<<endl;
        }
  cout<<"From bounds:"<<x[0]<<" "<<x[1]<<endl;
  x=Exact(3,6,12,1,10);

  cout<<endl<<endl;
  bool dep=isDependentExact(5,3,120,0,100);
  map<string, string> deps=ExactDirectionVector(5,3,120,0,100);
  cout<<"is dep:    "<<dep<<endl;
  cout<<"backward:   "<<deps["backward"]<<endl;
  cout<<"forward:   "<<deps["forward"]<<endl;
  cout<<"loopindependent:   "<<deps["loopindependent"]<<endl;


  dep=isDependentExact(2,3,10,50,100);
  deps=ExactDirectionVector(2,3,10,50,100);
  cout<<"is dep:    "<<dep<<endl;
  cout<<"backward:   "<<deps["backward"]<<endl;
  cout<<"forward:   "<<deps["forward"]<<endl;
  cout<<"loopindependent:   "<<deps["loopindependent"]<<endl;

  }