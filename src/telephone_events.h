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
  callEvent(event_type, const char*, dialog_h);

  const char *get_identity();
  void set_identity(const char *);

  dialog_h get_handler();
  void set_handler(dialog_h);
  
  Call *get_context(){ return context; };
  void set_context(Call *c){ context = c; };

 protected:
  const char *identity;
  dialog_h handle;
  Call *context;
  int direction;
 private:
};

class networkEvent: public baseEvent{
 public:
  //events should be in [1,20]
  networkEvent(event_type);
 private:
};

#endif
