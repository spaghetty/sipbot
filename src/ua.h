#ifndef tsip_ua
#define tsip_ua
#include "sip_server.h"
#include "sip_driver.h"
//#include "sofia_driver.h"
#include "line.h"
#include "base_event.h"
#include "event_handler.h"
#include <string>
#include <map>
#include <queue>
#include <pthread.h>

using namespace std;

typedef map<string, Line*> line_map_t;
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
  Line *get_line(const char* key);
  void show_lines();
  bool register_all();

  void add_event(baseEvent *);
  void stop_everything();
  void start_loop();

  bool driver_ready;

 protected:
  friend class Line;
  friend class eventHandler;
  std::string bind_ip;
  int bind_port;
  std::string realm;
  sipServer registrar;
  sipServer proxy; 
  line_map_t lines;
  event_queue_t events;
  eventHandler *evh;
  sipDriver *driver;

  /* multithreaded stuff */
  static void *event_loop(void *);
  static void *sip_driver(void *);

  /* tmp stuff some just for fun */
  void *sip_loop_rand_event_gen();
  /* end of tmp stuff this sould be removed soon */

  /* sync stuff high dangerous */
  pthread_cond_t events_ready;
  pthread_mutex_t lines_lock;
  pthread_mutex_t event_lock;
  pthread_t threads[4];
  int state;
 private:
};


#endif
