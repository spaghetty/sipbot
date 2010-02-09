#ifndef tsip_ua
#define tsup_ua
#include "sip_server.h"
#include "gl_avltreehash_list.h"
#include <string>

class Ua{
 public:
  Ua(std::string bind="localhost", int port=5060);
  void set_realm(const char*);
  void set_proxy(const char*, int port=5060);
  void set_registrar(const char*, int port=5060);
  const char *get_proxy(){ return proxy.get_uri(true).c_str(); };
  const char *get_registrar(){ return registrar.get_uri(true).c_str(); };

  /* Line Related stuff */

 protected:
  std::string bind_ip;
  int bind_port;
  std::string realm;
  sipServer registrar;
  sipServer proxy;
  gl_list_t lines;
 private:
};


#endif
