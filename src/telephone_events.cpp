#include "telephone_events.h"
#include <stdio.h>

clientEvent::clientEvent(event_type t):
  baseEvent(t,41,60)
{
}
callEvent::callEvent(event_type t):
  baseEvent(t,21,40)
{
  identity=NULL;
}

callEvent::callEvent(event_type t, const char *id, void *h):
  baseEvent(t,21,40)
{
  identity=id;
  handle=h;
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
  baseEvent(t,0,20)
{
}

