#ifndef  tsip_call
#define tsip_call

class Call
{
 public:
  Call(const char *id, void *dg);
  ~Call();
  bool check_count(int max);
  void  print_count();
  
  static int count;

 protected:
  const char *callid;
  void *dialog;
 private:
};

#endif
