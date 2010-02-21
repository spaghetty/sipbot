#include "telephone_events.h"
#include <stdio.h>

clientEvent::clientEvent(event_type t):
   baseEvent(t,CLIENT_EXIT,CLIENT_FAIL)
{
}
callEvent::callEvent(event_type t):
  baseEvent(t,NEW_CALL,REGISTER_FAIL)
{
  identity=NULL;
}

callEvent::callEvent(event_type t, const char *id, void *h):
  baseEvent(t,NEW_CALL,CALL_FAIL)
{
  identity=id;
  handle=h;
  direction = 0;
}

incomingCallEvent::incomingCallEvent(event_type t, const char *id, void *h):
  callEvent(t,id,h)
{
  direction= -1;
}

outgoingCallEvent::outgoingCallEvent(event_type t, const char *id, void *h):
  callEvent(t,id,h)
{
  direction = 1;
}

void callEvent::set_identity(const char *i)
{
  identity = i;
}

const char *callEvent::get_identity()
{
  return identity;
}

void *callEvent::get_handler()
{
  return handle;
}
void callEvent::set_handler(void *h)
{
  handle = h;
}

networkEvent::networkEvent(event_type t):
  baseEvent(t,NETWORK_EVENT,NETWORK_FAIL)
{
}

