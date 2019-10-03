#ifndef HEADER_HH
#define HEADER_HH

// #include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

#include "solver.cc"
#include "ast.hh"
// #include "program.hh"
// #include "alltokens.hh"
#include "symbol.hh"
// #include "procedure.hh"

// extern Program prog;
// extern symbolt global_stable;

extern Ast * MAIN;

extern "C" int yylex(void);
// #include <string.h>
// #include <stdlib.h>

#endif