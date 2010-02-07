#ifndef tsip_line
#define tsip_line

#include "sip_server.h"
#include <string>

class Ua;

class Line
{
 public:
  Line();
  int set_info(const char*, const char*, const char*, const char*);
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
