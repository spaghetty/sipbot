#ifndef tsip_event_handler
#define tsip_event_handler
#include "base_event.h"
class Ua;

class eventHandler
{
 public:

 protected:
  
  friend class Ua;
  eventHandler(Ua*);

  bool manage_event(baseEvent*);
  bool network_event(baseEvent *e);
  bool client_event(baseEvent *e);
  bool call_event(baseEvent *e);
 private:
  Ua *uagent;
};

#endif
