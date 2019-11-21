#ifndef _GCD_H 
#define _GCD_H

//gcd of 2 nos
int getGCD(int a, int b);

//returns true if dependent as per gcd test else returns false
bool GcdTest(int a, int b, int c);

//returns true if dependent as per gcd test else returns false with vector as arg
bool GcdTestV(std::vector<int> v);

//returns true if dependent as per gcd for any vectors of a,b,c: Union
bool GcdTestMulU(std::vector<std::vector<int>> v);
//returns true if dependent as per gcd for all vectors of a,b,c: Intersection
bool GcdTestMulI(std::vector<std::vector<int>> v);

//returns a vector of bounds of iteration for which dependence exist for eg: 72 to 80
std::vector<int> Exact(int a, int b, int c, int lb, int ub);

//returns a vector of all source sink pairs for which dependence is there for ax+by=c and lb<=x,y<=ub
std::vector< std::vector<int>> ExactSourceSink(int a, int b, int c, int lb, int ub);

//returns a map of three keys with yes or no for forward, backward, and loopindependent
//commented for gcd.h:23:1: error: ‘map’ does not name a type
//map<string, string> ExactDirectionVector(int a, int b, int c, int lb, int ub);


//returns true or false for dependence as detected by exact test
bool isDependentExact(int a, int b, int c, int lb, int ub);







#endif 