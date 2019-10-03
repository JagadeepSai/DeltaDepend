#ifndef AST_HH
#define AST_HH

#include<string>
#include<iostream>
#include<vector>
#include<list>
#include <map>

using namespace std;

typedef vector<vector<int> > INDEXES;
class Ast;
class Cond_Ast;
class Incre_Ast;
class ARR_EQ_Ast;
class FOR_Ast;
class Arr_Ast;

/* !!! Everything is ZERO indexed !!! */

class Ast{
	
	int index; // Statement count [first is Zero]

	public:
	Ast();
	~Ast();
	int get_index();
	void set_index(int i);
	virtual void print(int l);
};
// Differently Used as We need the values of the bounds of for loop rather than just abstract ast for the condition
// as we are not interested in evaluating/ compile functions for these classes
// This will bring a change in the symbol table interpretation as to store a variable 
class FOR_Ast: public Ast{

	int i_start,i_end; 			// Iteration Bounds
	int ind_start, ind_end;  	// Start Index == Ast.index, End Index
	string iter_name; 			// Iter Variable name
	Ast * body;
	Cond_Ast * cond;
	Incre_Ast * Incre;
	int nested_level;

	public:
	FOR_Ast();
	~FOR_Ast();
	void set_i_start(int s);
	void set_i_end(int e);
	int get_i_start();
	int get_i_end();

	void set_ind_start(int s);
	void set_ind_end(int e);
	int get_ind_start();
	int get_ind_end();

	void set_nested_level(int n);
	int get_nested_level();
	
	void set_iter_name(string s);
	string get_iter_name();

	void set_Cond(Cond_Ast * b);
	Cond_Ast * get_Cond();

	void set_Incre(Incre_Ast * b);
	Incre_Ast * get_Incre();
	
	void set_body(Ast* b);
	Ast * get_body();

	void print(int l);

	string check_ast();
};

class ARR_Ast: public Ast{
	int nested_level,arr_dim;
	INDEXES indexes;
	bool isSource; 
	string arr_name;
	list<ARR_EQ_Ast*>* eqs;

	public:
	ARR_Ast();
	~ARR_Ast();
	void set_nested_level(int n);
	int get_nested_level();

	void set_arr_dim(int n);
	int get_arr_dim();
	void add_arr_dim(int v);
	
	void set_isSource(bool b);
	bool get_isSource();
	void set_arr_name(string a);
	string get_arr_name();
	
	void add_eqs(ARR_EQ_Ast* eq);
	list<ARR_EQ_Ast*>* get_eqs();


	void print(int l);
};
//-------------------------------------------------------------------------------------------
typedef enum
{
	le,
	leq,
	gt,
	gtq,
	eq,
	neq
} Comp_ops;

class Cond_Ast: public Ast {
	string var_name; 
	int value;
	Comp_ops op;
	
	public:
	Cond_Ast();
	~Cond_Ast();
	Cond_Ast(Comp_ops c, string s, int a);

	void set_var_name(string s);
	string get_var_name();

	void set_value(int a);
	int get_value();

	void set_Comp_ops(Comp_ops c);
	Comp_ops get_Comp_ops();

	void negate();
	void print(int l);
};
//-------------------------------------------------------------------------------------------
class Incre_Ast: public Ast {
	string var_name; 
	bool isIncre;

	public: 

	Incre_Ast();
	Incre_Ast(string s,bool b);
	~Incre_Ast();
	
	void set_var_name(string s);
	string get_var_name();

	void set_isIncre(bool s);
	bool get_isIncre();

	void print(int l);
};


// Only for expressions 
class ARR_EQ_Ast : public Ast {
	
	int consta ;  
	//FIXME: This can be changed to map<string,int> to make a bit easy 
	// take care about merge(..) if changing this
	list<string>* var_names; 
	list<int>* coeffs;

	public: 
	ARR_EQ_Ast();
	ARR_EQ_Ast(int l);
	ARR_EQ_Ast(string s,int l);
	~ARR_EQ_Ast();

	list<string>* get_var_names(); 
	list<int>* get_coeffs();

	void add_pair(string s,int c);
	void set_constant(int s);
	int get_constant();
	
	void merge(ARR_EQ_Ast * expr);

	void make_neg(bool all);

	string check_ast();

	void print(int l);

	

};
// Don't Update Index in this, Do it in Array Assign Ast
// class Assign_Ast: public Ast{
// 	string var_name;
// 	Ast* value;

// 	public:
// 	Assign_Ast();
// 	~Assign_Ast();

// 	void set_var_name(string s);
// 	string get_var_name();

// 	void set_value(Ast* a);
// 	Ast* get_value();

// 	void print(int l);
// };

// class Num_Ast: public Assign_Ast{
// 	int value;

// 	public:
// 	Num_Ast();
// 	Num_Ast(int v);
// 	~Num_Ast();

// 	void set_value(int a);
// 	int get_value();

// 	void print(int l);
// };
#endif