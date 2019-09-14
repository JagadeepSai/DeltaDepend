#ifndef PROCEDURE_HH
#define PROCEDURE_HH


class Procedure;

#include "ast.hh"
#include "symbol.hh" 
#include <list>




class Procedure{
    public:
    string name;
    Symbol_Table* ftable; // This stores the variabes occuring in expr
    int nargs;
    list<VARI_Ast*>* arglist;
    Ast* fexpress; 
    // list<Ast*> arglist;

    Procedure(string name,Ast * value);
    Procedure(string name);
    ~Procedure();
    void set_ftable(symbolt * ftable);
    void set_nargs(int nargs);
    void set_expres(Ast * f);
    symbolt* get_ftable();
    void set_arglist(list<VARI_Ast*>* arglist);
    Ast * get_expres();
    
    // void check_args(int num);
    // void check_args(list<Ast*> given_args);

};


#endif
