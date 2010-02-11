#include "telephone_events.h"

clientEvent::clientEvent(event_type t):
  baseEvent(t,0,20)
{
}
callEvent::callEvent(event_type t):
  baseEvent(t,21,40)
{
}
networkEvent::networkEvent(event_type t):
  baseEvent(t,0,20)
{
}

