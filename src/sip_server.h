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
  void set_port(int p){ port = p;};
  void set_ip(const char *i){ ip.assign(i); };
  bool is_empty() { return ip.length()==0; };
 protected:
 private:
  std::string fqhn;
  std::string ip;
  int port;
};

#endif
