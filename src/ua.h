#ifndef tsip_ua
#define tsip_ua
#include "sip_server.h"
#include "line.h"
#include "base_event.h"
#include <string>
#include <map>
#include <queue>
#include <pthread.h>

using namespace std;

typedef map<const char*, Line*> line_map_t;
typedef queue<baseEvent*> event_queue_t;

class Ua{
 public:
  Ua(std::string bind="localhost", int port=5060);
  ~Ua();
  void set_realm(const char*);
  void set_proxy(const char*, int port=5060);
  void set_registrar(const char*, int port=5060);
  const char *get_proxy(){ return proxy.get_uri(true).c_str(); };
  const char *get_registrar(){ return registrar.get_uri(true).c_str(); };

  /* Line Related stuff */
  bool add_line(const char *user, const char *passwd);
  bool del_line(const char *key);
  void show_lines();

  void add_event(baseEvent *);
  void stop_everithing();

 protected:
  std::string bind_ip;
  int bind_port;
  std::string realm;
  sipServer registrar;
  sipServer proxy; 
  line_map_t lines;
  event_queue_t events;

  static void *event_loop(void *);
  
  /* sync stuff high dangerous */
  pthread_cond_t events_ready;
  pthread_mutex_t lines_lock;
  pthread_mutex_t event_lock;
  pthread_t threads[4];
 private:

};


#endif
