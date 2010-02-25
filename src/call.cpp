#include "call.h"
#include <stdio.h>
#include <stdlib.h>

int Call::count = 0;

Call::Call(const char *id)
{
  Call::count++;
  callid = id;
  is_incoming = -1;
};

Call::~Call()
{ 
  Call::count--; 
};

bool Call::check_count(int max)
{ 
  return (Call::count<max); 
};

void Call::set_as_incoming()
{
  is_incoming = 1;
};

void Call::set_as_outgoing()
{
  is_incoming = 0;
};

bool Call::check_is_incoming()
{
  return (is_incoming!= 0);
};

bool Call::direction_is_valid()
{
  return (is_incoming >= 0);
};

void Call::print_count()
{
  printf("il count e' %d\n",Call::count);
};

void Call::set_handle(dialog_h hd)
{
  dialog = hd;
};

dialog_h Call::get_handle()
{
  return dialog;
};

