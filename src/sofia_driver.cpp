#include "sofia_driver.h"
#include "telephone_events.h"
#include "ua.h"
#include <sofia-sip/su_log.h>
#include <sofia-sip/su_addrinfo.h>
#include <sofia-sip/su_localinfo.h>
#include <sofia-sip/nua_tag.h>
#include <sofia-sip/sip_status.h>

sofiaDriver::sofiaDriver(Ua *main_ua, const char *url, const char* proxy, int max):
  sipDriver(max)
{
  ua = main_ua;
  su_home_init(home);
  pthread_mutex_init(&call_lock, NULL);
  su_log_set_level (su_log_default, 0);
  root = su_root_create(this); /* this is what we will get in magic */
  nua = nua_create(root,     /* Event loop */                             
		   (event_manager), /* Callback for processing events*/  
		   this,           /* Application environment */                
		   NUTAG_URL(url),                                             
		   NUTAG_PROXY(proxy),                                         
		   TAG_END());    /* should always finish the sequence */
};

Call *sofiaDriver::add_call(const char *id)
{
  Call *c;
  if( Call::count < max_call)
    {
      c = call_exist(id);
      if(!c)
	{
	  pthread_mutex_lock(&call_lock);
	  pair<call_map_t::iterator,bool> ret;
	  c = new Call(id);
	  ret = calls.insert( make_pair(id,c));
	  c = (*(ret.first)).second;
	  pthread_mutex_unlock(&call_lock);
	}
    }
  else
    c = NULL;
  if(c)
    printf("prova ancora : %d---%d\n",c->count, max_call);
  return c; 
};

Call *sofiaDriver::delete_call(const char *id)
{
  Call *c = NULL;
  printf("ahhh noi siamo esattamente qua");
  pthread_mutex_lock(&call_lock);
  call_map_t::iterator it = calls.find(id);
  if (it != calls.end())
    {
      c = (*(it)).second;
      calls.erase(it);
    }
  pthread_mutex_unlock(&call_lock);
  return c; 
};

Call *sofiaDriver::call_exist(const char *id){

  Call *res = NULL;
  pthread_mutex_lock(&call_lock);
  call_map_t::iterator it = calls.find(id);
  if(it != calls.end())
    res = it->second;
  pthread_mutex_unlock(&call_lock);
  return res;
}

sofiaDriver::~sofiaDriver()
{
  pthread_mutex_destroy(&call_lock);
  nua_destroy(nua);
  su_root_destroy(root);
  su_home_deinit(home);
  su_deinit();
};

int sofiaDriver::start()
{
  ua->add_event(new clientEvent(DRIVER_READY));
  su_root_run(root);
  return 1;
}

void sofiaDriver::stop()
{
  nua_shutdown(nua);
}

int sofiaDriver::register_line(const char *display_name, const char *user_name, const char *registrar, const char *url, const char *line)
{
  string param = "line=";
  param.append(line);
  baseEvent *e = new callEvent(REGISTER_START);
  nua_handle_t *hd = nua_handle(nua, NULL,
				SIPTAG_TO_STR(url),
				SIPTAG_FROM_STR(url),
				TAG_END());
  nua_register(hd,
	       //NUTAG_M_DISPLAY(display_name),
	       NUTAG_M_USERNAME(user_name),
	       NUTAG_M_PARAMS(param.c_str()),
	       NUTAG_REGISTRAR(registrar),
	       NUTAG_KEEPALIVE_STREAM(0),
	       TAG_END());
  ((callEvent*)e)->set_identity((nua_handle_local(hd)->a_url)->url_user);
  ((callEvent*)e)->set_handler((dialog_h)hd);
  ua->add_event(e);
  return 1;
}

int sofiaDriver::unregister_line(dialog_h dialog)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_unregister(hd,
		 SIPTAG_EXPIRES(0), 
		 TAG_END());
  return 1;
}

/* need to be in form "diget:<realm>:<user>:<passwd>" */
int sofiaDriver::auth_dialog(const char *auth, dialog_h dialog, const char *registrar)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_authenticate(hd,
		   NUTAG_AUTH(auth),
		   TAG_END());
  return 1;
}

int sofiaDriver::generate_call(const char *user_name, const char *dest, const char *from, const char *line)
{
  string param = "line=";
  param.append(line);
  nua_handle_t *hd = nua_handle(nua, NULL,
				SIPTAG_TO_STR(dest),
				SIPTAG_FROM_STR(from),
				TAG_END());
  nua_invite(hd,
	     NUTAG_M_USERNAME(user_name),
	     NUTAG_MEDIA_ENABLE(0),
	     TAG_END());
  return 0;
};

void sofiaDriver::send_line_free(dialog_h dialog)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_respond(hd,
              SIP_180_RINGING,
              TAG_END());
};

void sofiaDriver::send_line_busy(dialog_h dialog)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_respond(hd,
              SIP_486_BUSY_HERE,
              TAG_END());
};

void sofiaDriver::send_cancel(dialog_h dialog)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_cancel(hd,
             TAG_END());
};

void sofiaDriver::event_manager(nua_event_t event, 
				int status,
				const char *phrase, 
				nua_t *nua, 
				nua_magic_t *magic, 
				nua_handle_t *nh, 
				nua_hmagic_t *hmagic, 
				const sip_t *sip, 
				tagi_t *tags)
{
  sofiaDriver *This = (sofiaDriver *)magic;
  Call *c= NULL;
  printf("something new arrivASDAAAAAAAAAAAAAAAe here\n");
  switch (event){
  case nua_r_shutdown:
    if (status < 200) {
      /* shutdown in progress -> return */
      return;
    }
    su_root_break(This->root);
    break;
  case nua_r_register:
    if(status >= 401 && status <= 407 )
      {
	This->ua->add_event(new callEvent(AUTH_REQUIRED,
					  (nua_handle_local(nh)->a_url)->url_user,
					  nh));
      }
    if(status==200)
      {
	This->ua->add_event(new callEvent(REGISTER_DONE,
					  (nua_handle_local(nh)->a_url)->url_user,
					  nh));
      }
    if(status >= 500 )
      {
	This->ua->add_event(new callEvent(REGISTER_FAIL,
					  (nua_handle_local(nh)->a_url)->url_user,
					  nh));
      }
    break;
  case nua_r_invite:
    {
    printf("statusssssssssss %d\n",status);
    if (status >= 100 && status < 200)
      {
	c = This->add_call(sip->sip_call_id->i_id);
	if(c){
	  callEvent *e = new callEvent(RINGING_CALL,
				       (nua_handle_local(nh)->a_url)->url_user,
				       nh);
	  e->set_context(c);
	  This->ua->add_event(e);
	}
      }
    if ( status >= 200 && status < 300 )
      {
	c = This->add_call(sip->sip_call_id->i_id);
	if(c){
	  callEvent *e = new callEvent(CONNECTED_CALL,
				       (nua_handle_local(nh)->a_url)->url_user,
				       nh);
	  e->set_context(c);
	  This->ua->add_event(e);
	}
      }
    if( status >= 400 && status < 500 )
      {
	printf("we are yere to delete everithing \n");
	c = This->delete_call(sip->sip_call_id->i_id);
	if(c)
	  {
	    callEvent *e = new callEvent(CALL_FAIL,
					 (nua_handle_local(nh)->a_url)->url_user,
					 nh);
	    e->set_context(c);
	    This->ua->add_event(e);
	  }
      }
    break;
    }
  case nua_i_invite:
    {
      c = This->add_call(sip->sip_call_id->i_id);
      if(c)
	{
	  callEvent *e = new callEvent(RINGING_CALL,
				       (nua_handle_local(nh)->a_url)->url_user,
				       nh);
	  e->set_context(c);
	  This->ua->add_event(e);
          This->send_line_free(nh);
	}
      break;
    }
  case nua_i_cancel:
    {
      c = This->delete_call(sip->sip_call_id->i_id);
      if(c)
	{
	  callEvent *e = new callEvent(CANCEL_CALL,
				       (nua_handle_local(nh)->a_url)->url_user,
				       nh);
	  e->set_context(c);
	  This->ua->add_event(e);
	}
      break;
    }
  case nua_i_bye:
    {
      printf("got bye\n");
      c = This->delete_call(sip->sip_call_id->i_id);
      if(c)
	{
	  callEvent *e = new callEvent(CLOSE_CALL,
				       (nua_handle_local(nh)->a_url)->url_user,
				       nh);
	  e->set_context(c);
	  This->ua->add_event(e);
	}
      break;
    }
  case nua_r_bye:
    {
      break;
    }
  case nua_i_media_error:
    printf("ma vaffanculo ai media\n");
    break;
  case nua_i_state:
    {
      /* i_state section is (for now) just useful for new call creation */
      int state;
      string cid;
      sip_replaces_t *sip_r = nua_handle_make_replaces(nh, This->home,false);
      if(sip_r!=NULL)
	{
	  cid = sip_r->rp_call_id;
	  su_free(This->home, sip_r);
	  tl_gets(tags, 
		  NUTAG_CALLSTATE_REF(state),
		  TAG_END());
	  c = This->add_call(cid.c_str());
	  if(!c)
	    {
	      /* send cancel */
	      if(((nua_callstate)state) == nua_callstate_calling)
		{
		  /* outgoing stuff */
		  callEvent *a = new callEvent(REJECTED_CALL,
					       (nua_handle_local(nh)->a_url)->url_user,
					       nh);
                  This->send_cancel(nh);
		  This->ua->add_event(a);				      
		}
	      if(((nua_callstate)state) == nua_callstate_received)
		{
		  /* incoming stuff */
		  callEvent *a = new callEvent(REJECTED_CALL,
					       (nua_handle_local(nh)->a_url)->url_user,
					       nh);
		  printf("here something to disable\n");
                  This->send_line_busy(nh);
		  This->ua->add_event(a);
		}
	      nua_handle_destroy(nh);
	      This->delete_call(cid.c_str());
	    }
	  else
	    {
	      if(((nua_callstate)state) == nua_callstate_calling)
		{
		  /* outgoing stuff */
		  callEvent *a = new callEvent(NEW_CALL,
					       (nua_handle_local(nh)->a_url)->url_user,
					       nh);
		  c->set_as_outgoing();
		  a->set_context(c);
		  This->ua->add_event(a);				      
		}
	      if(((nua_callstate)state) == nua_callstate_received)
		{
		  /* incoming stuff */
		  callEvent *a = new callEvent(NEW_CALL,
					       (nua_handle_local(nh)->a_url)->url_user,
					       nh);
		  c->set_as_incoming();
		  a->set_context(c);
		  This->ua->add_event(a);				      
		}
	    }
	}	
      printf("call %s\n", nua_callstate_name((nua_callstate)state));
      break;
    }
  default:
    printf("driver gets event\n");
    break;
  }
};
