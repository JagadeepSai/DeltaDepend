#ifndef SYMBOL_HH
#define SYMBOL_HH

#include<string>
#include<list>
using namespace std; 

class Symbol_Table; // Entries of For and Array 
class Symbol_Table_Entry; 
typedef enum
{
	FORLOOP,
	ARRAY
} Type_en;

class Symbol_Table
{
    list<Symbol_Table_Entry *> stable; 
    public:

    Symbol_Table();
    ~Symbol_Table();

    // bool is_empty();
    // void operator==(Symbol_Table & list);


    void print();
    void add_entry(Symbol_Table_Entry * entry);
};

class Symbol_Table_Entry
{
    string var_name; // FOR: Iterator name, ARR: array name 
    Type_en entry_Type;
    int index; 
};


#endif
