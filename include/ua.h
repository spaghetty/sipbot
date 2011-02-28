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
#include <limits.h>

using namespace std;

typedef map<string, Line*> line_map_t;
typedef queue<baseEvent*> event_queue_t;

/**
   This class rappresente the main sip user agent.
   This is the unique access point to the internal stuff.
 */

class Ua{
 public:

  /** \brief this is the main constructor
      Constructing this class you build the full feature sip agent

      \param bind std::string the address on which to bind can be "*" for all
      \param port int the port to use (default 5060)
      \param max_line max number or lines the phone support (contestual call)
      \return Ua object
   */
  Ua(std::string bind="localhost", int port=5060, int max_line=INT_MAX);
  ~Ua();
  void set_realm(const char*);
  void set_proxy(const char*, int port=5060);
  void set_registrar(const char*, int port=5060);
  const char *get_proxy(){ return proxy.get_uri(true).c_str(); };
  const char *get_registrar(){ return registrar.get_uri(true).c_str(); };
  void get_local_ip(){};

  /** @name Line Management
      Line Related stuff

      A line identify a registered entity
     @{
   */
  bool add_line(const char *user, const char *passwd);
  bool del_line(const char *key);
  Line *get_line(const char* key);
  void show_lines();
  bool register_all();
  /** @} */

  void add_event(baseEvent *);
  void stop_everything();
  void start_loop();

  bool driver_ready;

 protected:
  friend class Line;
  friend class eventHandler;
  std::string bind_ip;  /// the ip we are binded on
  int bind_port;        /// the port we are bindend on
  int max_call;         /// max contemporary call
  std::string realm;    
  sipServer registrar;  /// registrar server ip
  sipServer proxy;      /// proxy server ip
  line_map_t lines;     /// line map
  event_queue_t events; /// event queue
  eventHandler *evh;    /// application event handler
  sipDriver *driver;    /// the underlying sip stack (now just sofia)

  /* multithreaded stuff */
  static void *event_loop(void *);
  static void *sip_driver(void *);

  /* sync stuff high dangerous */
  pthread_cond_t events_ready;
  pthread_mutex_t lines_lock;
  pthread_mutex_t event_lock;
  pthread_t threads[4];
  int state;
 private:
};

/** \example base_test/test_ua.cpp
 * This is an example on Ua class usage.
 * Rappresent the management of base sip client showing most of the implemented functions.
 */


#endif
