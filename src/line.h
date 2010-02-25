#ifndef tsip_line
#define tsip_line

#include "sip_server.h"
#include "sip_driver.h"
#include <string>

class Ua;
class eventHandler;

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
  void auth_dialog(dialog_h dialog);
  int get_register_status(){ return is_registered; }
;
 protected:
  Line(Ua *);
  friend class Ua;
  friend class eventHandler;
  dialog_h reg_handler;
  std::string get_auth();
  int is_registered;

 private:
  std::string uname;
  std::string passwd;
  std::string domain;
  std::string realm;
  std::string url;
  std::string line;
  sipServer *proxy;
  sipServer *registrar;
  Ua *main_agent;
};

#endif
