#ifndef tsip_event_base
#define tsip_event_base

typedef enum event_t{
  UNKNOWN=0,
  /* network events should be in [1,20] */
  NETWORK_EVENT=1,
  NETWORK_FAIL=20,
  /* callEvent events should be in [21,40] */
  NEW_CALL=21,
  RINGING,
  HOLD_CALL,
  HELD_CALL,
  RELEASE_CALL,
  AUTH_REQUIRED,
  REGISTER_START,
  REGISTER_DONE,
  REGISTER_FAIL,
  CALL_FAIL=40,
  /* client events should be in [41,60] */
  CLIENT_EXIT=41,
  DRIVER_READY,
  CLIENT_FAIL=60,
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
