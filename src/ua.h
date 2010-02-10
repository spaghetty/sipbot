#ifndef tsip_ua
#define tsip_ua
#include "sip_server.h"
#include "line.h"
#include <string>
#include <map>

using namespace std;

typedef map<const char*, Line*> line_map_t;

class Ua{
 public:
  Ua(std::string bind="localhost", int port=5060);
  void set_realm(const char*);
  void set_proxy(const char*, int port=5060);
  void set_registrar(const char*, int port=5060);
  const char *get_proxy(){ return proxy.get_uri(true).c_str(); };
  const char *get_registrar(){ return registrar.get_uri(true).c_str(); };

  /* Line Related stuff */
  int add_line(const char *user, const char *passwd);
  void show_lines();
 protected:
  std::string bind_ip;
  int bind_port;
  std::string realm;
  sipServer registrar;
  sipServer proxy; 
  line_map_t lines;
 private:
};


#endif
