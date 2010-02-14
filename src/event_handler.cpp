#include "event_handler.h"
#include "telephone_events.h"
#include "ua.h"
#include <stdio.h>

eventHandler::eventHandler(Ua *agent)
{
  uagent = agent;
}

bool eventHandler::manage_event(baseEvent *e)
{
  if( e->getType()>=NETWORK_EVENT and e->getType()<=NETWORK_FAIL)
    return network_event((networkEvent*)e);
  if( e->getType()>=NEW_CALL and e->getType()<=CALL_FAIL)
    return call_event((callEvent*)e);
  if( e->getType()>=CLIENT_EXIT and e->getType()<=CLIENT_FAIL)
    return client_event((clientEvent*)e);
  return true;
}

bool eventHandler::network_event(baseEvent *e)
{
}

bool eventHandler::call_event(baseEvent *e)
{
}

bool eventHandler::client_event(baseEvent *e)
{
  if(e->is(CLIENT_EXIT))
      uagent->state = -1;
  if(e->is(DRIVER_READY))
      uagent->driver_ready = 1;
  return true;
}
