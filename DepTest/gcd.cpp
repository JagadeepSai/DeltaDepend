#include <iostream> 
#include <stdlib.h> 
#include <string>
#include <vector> 
#include <map> 
#include<sstream>
#include "gcd.h"

using namespace std;
//Input coefMap:i1,i2,i3....,c[i1*x+i2*y+i3*z=c] 
//returns true or false for dependence
bool ExtendedGcd(std::map<string, int> coefMap);
//returns true if dependent as per banerjee test else returns false
bool BanerjeeTest(int a, int b, int c, int LB, int UB);
bool getDependence(int min, int max, int c);
map<string, int> getMinMax(int a, int b, int LB, int UB);


//Input coefMap:i1,i2,i3....,c[i1*x+i2*y+i3*z=c] boundMap: lb1,ub1,lb2,ub2...
//return vector 1st record:source, 2nd sink, 3rd source, 4th sink and so on...
std::vector<int> Exhaustive(map<string, int> coefMap, map<string, int> boundMap);

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
//EXTENDED GCD TEST
//************************************************************************************************

bool ExtendedGcd(map<string, int> coefMap){
  int min=0,max=0;
  bool dependent=true;
  int coefSize=coefMap.size() -1;
  //cout<<"coef size: "<<coefSize<<endl;
  std::vector<int> v;

  switch (coefSize)
  {
    case 2: 
     {
      v.push_back(coefMap["i1"]);
      v.push_back(coefMap["i2"]);
      v.push_back(coefMap["c"]);
      dependent=GcdTestV(v);
      break;
    }
    case 4: {
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["c"];

      int gc1=getGCD(a,b);
      int gc2=getGCD(c,d);

      dependent=GcdTest(gc1,gc2,e);
      break;
      }

   case 6: {
      min=0,max=0;
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["i5"];
      int f=coefMap["i6"];
      int g=coefMap["c"];


      int gc1=getGCD(a,b);
      int gc2=getGCD(c,d);
      int gc3=getGCD(e,f);
      gc2=getGCD(gc2,gc3);
      dependent=GcdTest(gc1,gc2,g);
      break;}

   case 8: {
      min=0,max=0;
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["i5"];
      int f=coefMap["i6"];
      int g=coefMap["i7"];
      int h=coefMap["i8"];
      int i=coefMap["c"];

      int gc1=getGCD(a,b);
      int gc2=getGCD(c,d);
      int gc3=getGCD(e,f);
      int gc4=getGCD(g,h);
      gc1=getGCD(gc1,gc2);
      gc2=getGCD(gc3,gc4);
      dependent=GcdTest(gc1,gc2,i);

      break;}
  
  }
  return dependent;
}
//************************************************************************************************
//EXHAUSTIVE TEST for LDE
//************************************************************************************************

std::vector<int> Exhaustive(map<string, int> coefMap, map<string, int> boundMap){
std::vector<int> v;
  int min=0,max=0;
  bool dependent=true;
  int a=coefMap["i1"];
  int b=coefMap["i2"];
  int c=coefMap["c"];
  int lb1=boundMap["lb1"];
  int ub1=boundMap["ub1"];

  for(int i=lb1;i<=ub1;i++){
    for(int j=lb1;j<=ub1;j++){
        if(a*i+b*j==c){
        v.push_back(i);
        v.push_back(j);
        }

    }
    
    }

return v;
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



//MERGED Banerjee HERE

bool BanerjeeTest(int a, int b, int c, int LB, int UB){
    int min=0,max=0;
    bool dependent=true;
    if(a>=0 && b>=0){
      min=LB*a +LB*b;
      max=UB*a+UB*b;

    }
    else if(a>=0 && b<0){
      min=LB*a +UB*b;
      max=UB*a+LB*b;
    }
    else if(a<0 && b>=0 ){
      min=UB*a +LB*b;
      max=LB*a+UB*b;

    }
    else if(a<0 && b<0){
      min=UB*a +UB*b;
      max=LB*a+LB*b;

    }
    else{
      //if some error, returning imprecise, but sound value
      return true;
    }
      //cout<<"min:   "<<min<<"max: "<<max<<endl;
    if(min <= c && c<= max){
      dependent=true;
    }
    else{
      dependent=false;
    }
    return dependent;
}
/* if don't want to with int args, pass vector in the following order:
a,    b,    c,    lb,     ub
v[0] v[1]   v[2]  v[3]    v[4]
*/
bool BanerjeeTestV(std::vector<int> v){
  return BanerjeeTest(v[0],v[1],v[2],v[3],v[4]);

}

//Input coefMap:i1,i2,i3....,c[i1*x+i2*y+i3*z=c] boundMap: lb1,ub1,lb2,ub2...
//returns true or false for dependence
bool ExtendedBanerjee(map<string, int> coefMap, map<string, int> boundMap){
  int min=0,max=0;
  bool dependent=true;
  int coefSize=coefMap.size() -1;
  //cout<<"coef size: "<<coefSize<<endl;
  int boundSize=boundMap.size();
  std::vector<int> v;

  switch (coefSize)
  {
    case 2:
     {
      v.push_back(coefMap["i1"]);
      v.push_back(coefMap["i2"]);
      v.push_back(coefMap["c"]);
      v.push_back(boundMap["lb1"]);
      v.push_back(boundMap["ub1"]);
      dependent=BanerjeeTestV(v);
      break;
    }
    case 4: {
      min=0,max=0;
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["c"];
      int lb1=boundMap["lb1"];
      int lb2=boundMap["lb2"];
      int ub1=boundMap["ub1"];
      int ub2=boundMap["ub2"];

      map<string, int> minMaxMap;
      minMaxMap=getMinMax(a,b,lb1,ub1);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];
      //cout<<"min:   "<<min<<"max: "<<max<<endl;

      minMaxMap=getMinMax(c,d,lb2,ub2);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];
      //cout<<"min:   "<<min<<"max: "<<max<<endl;
      /*
      std::vector<int> v;
      v=getMinMax(a,b,lb1,ub1);
      min=min+v[0];
      max=max+v[1];

      v=getMinMax(c,d,lb2,ub2);
      min=min+v[0];
      max=max+v[1];
    */
      dependent=getDependence(min,max,e);
      break;
      }

   case 6: {
      min=0,max=0;
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["i5"];
      int f=coefMap["i6"];
      int g=coefMap["c"];

      int lb1=boundMap["lb1"];
      int lb2=boundMap["lb2"];
      int lb3=boundMap["lb3"];
      int ub1=boundMap["ub1"];
      int ub2=boundMap["ub2"];
      int ub3=boundMap["ub3"];
      map<string, int> minMaxMap;
      minMaxMap=getMinMax(a,b,lb1,ub1);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      minMaxMap=getMinMax(c,d,lb2,ub2);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      minMaxMap=getMinMax(e,f,lb3,ub3);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      //cout<<"min:   "<<min<<"max: "<<max<<endl;

      dependent=getDependence(min,max,g);
      break;}

   case 8: {
      min=0,max=0;
      int a=coefMap["i1"];
      int b=coefMap["i2"];
      int c=coefMap["i3"];
      int d=coefMap["i4"];
      int e=coefMap["i5"];
      int f=coefMap["i6"];
      int g=coefMap["i7"];
      int h=coefMap["i8"];
      int i=coefMap["c"];

      int lb1=boundMap["lb1"];
      int lb2=boundMap["lb2"];
      int lb3=boundMap["lb3"];
      int lb4=boundMap["lb4"];
      int ub1=boundMap["ub1"];
      int ub2=boundMap["ub2"];
      int ub3=boundMap["ub3"];
      int ub4=boundMap["ub4"];
      map<string, int> minMaxMap;
      minMaxMap=getMinMax(a,b,lb1,ub1);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      minMaxMap=getMinMax(c,d,lb2,ub2);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      minMaxMap=getMinMax(e,f,lb3,ub3);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      minMaxMap=getMinMax(g,h,lb4,ub4);
      min=min+minMaxMap["min"];
      max=max+minMaxMap["max"];

      //cout<<"min:   "<<min<<"max: "<<max<<endl;

      dependent=getDependence(min,max,i);
      break;}

  }
  return dependent;


}
//returns minimum and maximum values as a map for extended banerjee
//this is called iteratively for each pair of variables in LDE with their lb and ub
//bool getDependence(int min, int max, int c)
map<string, int> getMinMax(int a, int b, int LB, int UB){
  int min=0,max=0;
  map<string, int> minMaxMap;
   if(a>=0 && b>=0){
      min=LB*a +LB*b;
      max=UB*a+UB*b;

    }
    else if(a>=0 && b<0){
      min=LB*a +UB*b;
      max=UB*a+LB*b;
    }
    else if(a<0 && b>=0 ){
      min=UB*a +LB*b;
      max=LB*a+UB*b;

    }
    else if(a<0 && b<0){
      min=UB*a +UB*b;
      max=LB*a+LB*b;

    }
    minMaxMap.insert(make_pair("min", min));
    minMaxMap.insert(make_pair("max", max));

    return minMaxMap;

}

bool getDependence(int min, int max, int c){
  bool dependent=true;
  if(min <= c && c<= max){
      dependent=true;
    }
    else{
      dependent=false;
    }
    return dependent;
}



int main(){
    int input=0;
       
    while(1){
          cout<<"Choose one of the options:"<<endl;
          cout<<"Enter 1 for Exact Test for direction vector"<<endl;
          cout<<"Enter 2 for Exact Test to get source sink pairs"<<endl;
          cout<<"Enter 3 for Exhaustive Test to get source sink pairs"<<endl;
          cout<<"Enter 4 for GCD and Extended GCD Test"<<endl;
          cout<<"Enter 5 for Banerjee and Extended Banerjee Test"<<endl;
          cout<<"Enter 6 to exit"<<endl;
          cin>>input;
          cin.ignore();
    switch(input){
        case 1:{
            std::string line;
            int number;
            vector<int> v;
            cout << "Enter coefficient of LDE separated by spaces: a b c lb ub"<<endl;
            getline(std::cin, line);
            istringstream stream(line);
            while (stream >> number)
                v.push_back(number);
            map<string, string> deps=ExactDirectionVector(v[0],v[1],v[2],v[3],v[4]);
            cout<<"backward:    "<<deps["backward"]<<endl;
            cout<<"forward:      "<<deps["forward"]<<endl;
            cout<<"loopindependent:   "<<deps["loopindependent"]<<endl;            
            break;    
        }
        case 2:{
            std::string line;
            int number;
            vector<int> v;
            cout << "Enter coefficient of LDE separated by spaces: a b c lb ub"<<endl;
            getline(std::cin, line);
            istringstream stream(line);
            while (stream >> number)
                v.push_back(number);
            std::vector<std::vector<int>> xv=ExactSourceSink(v[0],v[1],v[2],v[3],v[4]);
           for (int i = 0; i < xv.size(); i++) { 
            cout<<"source:  " << xv[i][0]<<" and Sink:   "<<xv[i][1]<<endl;
        }
            break;
        }
        case 3:{
            std::string line;
            int number;
            vector<int> v;
            cout << "Enter coefficient of LDE separated by spaces for Exhaustive Test: a b c lb ub"<<endl;
            getline(std::cin, line);
            istringstream stream(line);
            while (stream >> number)
                v.push_back(number);
            map<string,int> coef;
            map<string,int> boundMap;
            //cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3]<<" "<<v[4]<<" "<<endl;
            coef.insert(make_pair("i1", v[0]));
            coef.insert(make_pair("i2", v[1]));
            coef.insert(make_pair("c", v[2]));
            boundMap.insert(make_pair("lb1", v[3]));
            boundMap.insert(make_pair("ub1", v[4]));
            std::vector<int> xv=Exhaustive(coef,boundMap);
            cout << "Running exhaustive"<<endl;
            
            for (int i = 0; i < xv.size(); i++) { 
            cout<<"source:  " << xv[i]<<" and Sink:   "<<xv[i+1]<<endl;
            i++;
            }
            break;
        }
        case 4:{
            std::string line;
            int number;
            vector<int> v;
            cout << "Enter coefficient of LDE separated by spaces: i1 i2 i3 i4 i5.....c"<<endl;
            getline(std::cin, line);
            istringstream stream(line);
            while (stream >> number)
                v.push_back(number);          
            map<string,int> coef;
            int size=v.size()-1;
            switch (size){
                case 2:{
                     coef.insert(make_pair("i1", v[0]));
                     coef.insert(make_pair("i2", v[1]));
                     coef.insert(make_pair("c", v[2]));
                    break;
                }
                case 4:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("c", v[4]));
                    
                    break;
                }
                case 6:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("i5", v[4]));
                    coef.insert(make_pair("i6", v[5]));
                    coef.insert(make_pair("c", v[6]));
                    
                    break;
                }
                case 8:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("i5", v[4]));
                    coef.insert(make_pair("i6", v[5]));
                    coef.insert(make_pair("i7", v[6]));
                    coef.insert(make_pair("i8", v[7]));
                    coef.insert(make_pair("c", v[8]));
                    break;
                }

            }
            bool dep=ExtendedGcd(coef);
            cout<<"Depenedence: "<<dep<<endl;
            

            break;

        }
            case 5:{
            std::string line;
            int number;
            vector<int> v;
            cout << "Enter coefficient and bounds of LDE separated by spaces: i1 i2 i3 i4 i5.....c lb1 ub1 lb2 ub2....where lb is lower bound and ub is upper bound"<<endl;
            getline(std::cin, line);
            istringstream stream(line);
            while (stream >> number)
                v.push_back(number);          
            map<string,int> coef,bound;
            int size=(v.size()-1)/2;
            switch (size){
                case 2:{
                     coef.insert(make_pair("i1", v[0]));
                     coef.insert(make_pair("i2", v[1]));
                     coef.insert(make_pair("c", v[2]));

                     bound.insert(make_pair("lb1", v[3]));
                     bound.insert(make_pair("ub1", v[4]));

                    break;
                }
                case 4:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("c", v[4]));

                    bound.insert(make_pair("lb1", v[5]));
                    bound.insert(make_pair("ub1", v[6]));
                    bound.insert(make_pair("lb2", v[7]));
                    bound.insert(make_pair("ub2", v[8]));
                    
                    break;
                }
                case 6:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("i5", v[4]));
                    coef.insert(make_pair("i6", v[5]));
                    coef.insert(make_pair("c", v[6]));

                    bound.insert(make_pair("lb1", v[7]));
                    bound.insert(make_pair("ub1", v[8]));
                    bound.insert(make_pair("lb2", v[9]));
                    bound.insert(make_pair("ub2", v[10]));
                    bound.insert(make_pair("lb3", v[11]));
                    bound.insert(make_pair("ub3", v[12]));

                    break;
                }
                case 8:{
                    coef.insert(make_pair("i1", v[0]));
                    coef.insert(make_pair("i2", v[1]));
                    coef.insert(make_pair("i3", v[2]));
                    coef.insert(make_pair("i4", v[3]));
                    coef.insert(make_pair("i5", v[4]));
                    coef.insert(make_pair("i6", v[5]));
                    coef.insert(make_pair("i7", v[6]));
                    coef.insert(make_pair("i8", v[7]));
                    coef.insert(make_pair("c", v[8]));

                    bound.insert(make_pair("lb1", v[9]));
                    bound.insert(make_pair("ub1", v[10]));
                    bound.insert(make_pair("lb2", v[11]));
                    bound.insert(make_pair("ub2", v[12]));
                    bound.insert(make_pair("lb3", v[13]));
                    bound.insert(make_pair("ub3", v[14]));
                    bound.insert(make_pair("lb4", v[15]));
                    bound.insert(make_pair("ub4", v[16]));
                    break;
                }

            }
            bool dep=ExtendedBanerjee(coef,bound);
            cout<<"Depenedence: "<<dep<<endl;
            

            break;

        }
        case 6:{
                cout<<"Bye bye"<<endl;
                exit(0);
                break;
        }
    }




    }


    /*
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





    //NEW CODE TEST
map<string, int> coef;

coef.insert(make_pair("i1", 5));
coef.insert(make_pair("i2", 3));
coef.insert(make_pair("c", 120));

dependent=false;
dependent=ExtendedGcd(coef);
cout<<"BEXTTrue:   "<<dependent<<endl;



///4 variable lde
coef.insert(make_pair("i3", 4));
coef.insert(make_pair("i4", 60));

dependent=true;
dependent=ExtendedGcd(coef);
cout<<"BEXTTrue:   "<<dependent<<endl;

///6 variable lde
coef.insert(make_pair("i5", 4));
coef.insert(make_pair("i6", 60));

dependent=false;
dependent=ExtendedGcd(coef);
cout<<"BEXTTrue:   "<<dependent<<endl;



///8 variable lde
coef.insert(make_pair("i7", 4));
coef.insert(make_pair("i8", 60));

dependent=false;
dependent=ExtendedGcd(coef);
cout<<"BEXTTrue:   "<<dependent<<endl;

map<string, int> boundMap;
boundMap.insert(make_pair("lb1", 0));
boundMap.insert(make_pair("ub1", 100));


// v=ExactSourceSink(5,3,120,0,100);
 v=Exhaustive(coef,boundMap);
 for(int i=0;i<18;i++){
 cout<<v[i]<<"and"<<v[i+1]<<endl;
 i++;
 }

*/

  }