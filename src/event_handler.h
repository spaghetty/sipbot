#ifndef tsip_event_handler
#define tsip_event_handler
#include "base_event.h"
#include "telephone_events.h"
class Ua;

class eventHandler
{
 public:

 protected:
  
  friend class Ua;
  eventHandler(Ua*);

  bool manage_event(baseEvent*);
  bool network_event(networkEvent *e);
  bool client_event(clientEvent *e);
  bool call_event(callEvent *e);
 private:
  Ua *uagent;
};

#endif
