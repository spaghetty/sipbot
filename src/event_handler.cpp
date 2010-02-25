#include "event_handler.h"
#include "telephone_events.h"
#include "ua.h"
#include <stdio.h>
#include <string.h>

eventHandler::eventHandler(Ua *agent)
{
  uagent = agent;
}

bool eventHandler::manage_event(baseEvent *e)
{
  if( e->getType()>=NETWORK_EVENT and e->getType()<=NETWORK_FAIL)
    return network_event((networkEvent*)e);
  if( e->getType()>=NEW_CALL and e->getType()<=REGISTER_FAIL)
    return call_event((callEvent*)e);
  if( e->getType()>=CLIENT_EXIT and e->getType()<=CLIENT_FAIL)
    return client_event((clientEvent*)e);
  return true;
}

bool eventHandler::network_event(networkEvent *e)
{
  return true;
}

bool eventHandler::call_event(callEvent *e)
{
  if(e->is(REGISTER_START))
    {
      const char *key = e->get_identity();
      Line *l=uagent->get_line(key);
      if(l!=NULL)
	{
	  l->reg_handler = e->get_handler();
	}
    }
  if(e->is(AUTH_REQUIRED))
    {
      const char *key = e->get_identity();
      Line *l=uagent->get_line(key);
      if(l!=NULL)
	{
	  if(l->reg_handler == e->get_handler())
	    {
	      l->auth_dialog(e->get_handler());
	    }
	}
    }
  if(e->is(REGISTER_DONE))
    {
      const char *key = e->get_identity();
      Line *l=uagent->get_line(key);
      if(l!=NULL)
	{
	  l->is_registered = 1; // succesfull registered //
	}
    }
  if(e->is(CANCEL_CALL) ||
     e->is(RELEASE_CALL)||
     e->is(CLOSE_CALL) ||
     e->is(CALL_FAIL) )/* this part here is just a temp fix, use will delete call in real use state */
    {
      Call *c = e->get_context();
      if(c)
	delete c;
    }
  return true;
}

bool eventHandler::client_event(clientEvent *e)
{
  if(e->is(CLIENT_EXIT))
    uagent->state = -1;
  if(e->is(DRIVER_READY))
    uagent->driver_ready = 1;
  return true;
}
