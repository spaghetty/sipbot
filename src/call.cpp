#include "call.h"
#include <stdio.h>
#include <stdlib.h>

int Call::count = 0;

Call::Call(const char *id)
{
  Call::count++;
  callid = id;
};

Call::~Call()
{ 
  Call::count--; 
};

bool Call::check_count(int max)
{ 
  return (Call::count<max); 
};

void Call::print_count()
{
  printf("il count e' %d\n",Call::count);
}
