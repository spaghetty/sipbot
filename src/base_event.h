#ifndef tsip_event_base
#define tsip_event_base

typedef enum event_t{
  UNKNOWN=0,
  /* network events should be in [1,20] */
  NETWORK_EVENT=1,
  NETWORK_FAIL=20,
  /* callEvent events should be in [21,60] */
  /* specific releted to call [21,40] */
  NEW_CALL=21,
  RINGING_CALL,
  HOLD_CALL,
  HELD_CALL,
  REJECTED_CALL,
  RELEASE_CALL,
  CALL_FAIL=40,
  /* generic signalig stuff [41,60] */
  AUTH_REQUIRED,
  REGISTER_START,
  REGISTER_DONE,
  REGISTER_FAIL=60,  
  /* client events should be in [61,80] */
  CLIENT_EXIT=61,
  DRIVER_READY,
  CLIENT_FAIL=80,
} event_type;

class baseEvent{
 public:
  baseEvent(event_type, int, int);
  event_type getType(){ return etype; };
  bool is(event_type);

 protected:
  baseEvent(){};

  event_type etype;
 private:
};

#endif
