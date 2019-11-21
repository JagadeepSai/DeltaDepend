#include <iostream> 
#include <vector> 
using namespace std;

//returns true if dependent as per banerjee test else returns false
bool BanerjeeTest(int a, int b, int c, int LB, int UB);



//returns true if dependent as per banerjee test else returns false
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

int main(){
vector<int>  v={ 2, 2, 3,0,10};
  

  bool dependent=BanerjeeTest(2,4,6,0,10);
  cout<<"BTrue:   "<<dependent<<endl;

  dependent=BanerjeeTest(-2,4,6,0,10);
  cout<<"BTrue:   "<<dependent<<endl;
  
  dependent=BanerjeeTest(2,-4,6,0,10);
  cout<<"BTrue:   "<<dependent<<endl;


  dependent=BanerjeeTest(-2,-4,6,10,20);  
  cout<<"BFalse:  "<<dependent<<endl;
  
  dependent=BanerjeeTest(2,4,6,10,20);  
  cout<<"BFalse:  "<<dependent<<endl;
  
  dependent=BanerjeeTest(2,4,6,10,20);  
  cout<<"BFalse:  "<<dependent<<endl;
  
  dependent=BanerjeeTestV(v);                              
  cout<<"BTrueV: "<<dependent<<endl;
  

  }