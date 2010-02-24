#ifndef tsip_event_telephone
#define tsip_event_telephone

#include "call.h"
#include "base_event.h"

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
  callEvent(event_type, const char*, void *);

  const char *get_identity();
  void set_identity(const char *);

  void *get_handler();
  void set_handler(void *);

 protected:
  const char *identity;
  void *handle;
  int direction;
 private:
};

class incomingCallEvent: public callEvent
{
 public:
  incomingCallEvent(event_type, const char*, void *);;
  Call *get_context(){ return context; };
  void set_context(Call *c){ context = c; };
 protected:
  Call *context;
 private:
};

class outgoingCallEvent: public callEvent
{
 public:
  outgoingCallEvent(event_type, const char*, void *);;
  Call *get_context(){ return context; };
  void set_context(Call *c){ context = c; };
 protected:
  Call *context;
 private:
};

class networkEvent: public baseEvent{
 public:
  //events should be in [1,20]
  networkEvent(event_type);
 private:
};

#endif
