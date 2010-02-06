#ifndef tsip_event_base
#define tsip_event_base

typedef enum event_t{
  UNKNOWN=0,
  NEW_CALL=10,
  RINGING,
  HOLD_CALL,
  HELD_CALL,
  RELEASE_CALL,
} event_type;

class baseEvent{
 public:
  baseEvent(event_type, int, int);
  event_type getType(){ return etype; };

 protected:
  baseEvent(){};

  event_type etype;
 private:
};

#endif
