#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include <iostream>
#include <exception>
#include <vector>

using namespace std;

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

const int DEF_LEN    = 10;
const int MEM_STEP   = 50;
const int MAX_DATASZ = 301; //azaza

int arrays_count = 0;
const char* OK_EXITING     = "You've deleted all the arrays.\n";
const char* NOT_OK_EXITING = "You've not deleted all the arrays.\n'";
