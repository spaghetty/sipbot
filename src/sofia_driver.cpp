#include "sofia_driver.h"
#include "telephone_events.h"
#include "ua.h"
#include <sofia-sip/su_log.h>

sofiaDriver::sofiaDriver(Ua *main_ua, const char *url, const char* proxy, int max):
  sipDriver(max)
{
  ua = main_ua;
  su_home_init(home);
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
};

Call *sofiaDriver::delete_call(const char *id)
{
};

sofiaDriver::~sofiaDriver()
{
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
  ((callEvent*)e)->set_handler((void*)hd);
  ua->add_event(e);
  return 1;
}

int sofiaDriver::unregister_line(void *dialog)
{
  nua_handle_t *hd = NULL;
  hd = (nua_handle_t*)dialog;
  nua_unregister(hd,
		 SIPTAG_EXPIRES(0), 
		 TAG_END());
  return 1;
}

/* need to be in form "diget:<realm>:<user>:<passwd>" */
int sofiaDriver::auth_dialog(const char *auth, void *dialog, const char *registrar)
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
    This->ua->add_event(new outgoingCallEvent(NEW_CALL,
					      (nua_handle_local(nh)->a_url)->url_user,
					      nh));
    Call *c = new Call(sip->sip_call_id->i_id,nh);
    if(!c->check_count(2))
      {
	printf("so cazzi %s\n",sip->sip_call_id->i_id);
      }
    break;
    }
  case nua_i_invite:
    This->ua->add_event(new incomingCallEvent(NEW_CALL,
					      (nua_handle_local(nh)->a_url)->url_user,
					      nh));
    /* try sending invite here */
    break;
  case nua_i_media_error:
    printf("ma vaffanculo ai media\n");
    break;
  case nua_i_state:
    printf("MA VAAFFANCULIO A I STATE\n");
    break;
  default:
    printf("driver gets event\n");
    break;
  }
}
