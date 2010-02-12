#ifndef tsip_line
#define tsip_line

#include "sip_server.h"
#include <string>

class Ua;

class Line
{
 public:
  int set_info(const char*, const char*, const char*, const char*);
  int set_outproxy(char*, int =5060);
  int set_registrar(char*, int =5060);
  const char *get_registrar(bool b){ return registrar->get_uri(b).c_str(); };
  std::string get_uri(bool with);
  bool register_it();
  bool unregister_it();
  bool generate_call(const char *dialstring);

 protected:
  Line(Ua *);
  friend class Ua;
  void *reg_handler;
 private:

  std::string uname;
  std::string passwd;
  std::string domain;
  std::string realm;
  std::string url;
  sipServer *proxy;
  sipServer *registrar;
  Ua *main_agent;
};

#endif
