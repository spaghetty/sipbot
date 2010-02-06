#include "base_event.h"

baseEvent::baseEvent(event_type t, int start=0, int stop=100)
{
  if(t>start and t< stop)
    etype = t;
  else
    etype = (event_type)UNKNOWN;
}
