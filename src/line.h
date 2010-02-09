#ifndef tsip_line
#define tsip_line

#include "sip_server.h"
#include <string>

class Ua;

class Line
{
 public:
  Line(Ua *);
  int set_info(const char*, const char*, const char*, const char*);
  int set_outproxy(char*, int =5060);
  int set_registrar(char*, int =5060);
  const char *get_registrar(bool b){ return registrar->get_uri(b).c_str(); };
  std::string get_uri(bool with);
 protected:
 private:

  std::string uname;
  std::string passwd;
  std::string domain;
  std::string realm;
  sipServer *proxy;
  sipServer *registrar;
  Ua *main_agent;
};

#endif
