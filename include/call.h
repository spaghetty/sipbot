#ifndef  tsip_call
#define tsip_call

#include "sip_driver.h"

class Call
{
 public:
  Call(const char *id);
  ~Call();
  bool check_count(int max);
  void  print_count();

  void set_as_incoming();
  void set_as_outgoing();
  bool check_is_incoming();
  bool direction_is_valid();

  void set_handle(dialog_h hd);
  dialog_h get_handle();
  

  static int count;

 protected:
  const char *callid;
  dialog_h dialog;
  int is_incoming;
  
 private:
};

#endif
