#include "base_event.h"
#ifndef tsip_event_telephone
#define tsip_event_telephone

class clientEvent: public baseEvent{
 public:
  //events should be in [41,60]
  clientEvent(event_type); 
 private:
};

class callEvent: public baseEvent{
 public:
  //events should be in [21,40]
  callEvent(event_type);
 private:
};

class networkEvent: public baseEvent{
 public:
  //events should be in [1,20]
  networkEvent(event_type);
 private:
};

#endif
