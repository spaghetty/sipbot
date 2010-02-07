#ifndef tsip_sip_server
#define tsip_sip_server

#include <string>

class sipServer
{
 public:
  sipServer(){};
  sipServer(const char*, const char* ="", int =5060);
  int get_port(){ return port; };
  std::string &get_ip(){ return ip; };
  std::string get_uri(bool);
 protected:
 private:
  std::string fqhn;
  std::string ip;
  int port;
};

#endif
