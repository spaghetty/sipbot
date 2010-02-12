#include "sofia_driver.h"
#include "ua.h"

sofiaDriver::sofiaDriver(Ua *main_ua, const char *url, const char* proxy)
{
  ua = main_ua;
  su_home_init(home);
  root = su_root_create(this); /* this is what we will get in magic */
  nua = nua_create(root,     /* Event loop */                             
		   (event_manager), /* Callback for processing events*/  
		   this,           /* Application environment */                
		   NUTAG_URL(url),                                             
		   NUTAG_PROXY(proxy),                                         
		   TAG_END());    /* should always finish the sequence */
}

sofiaDriver::~sofiaDriver()
{
  nua_destroy(nua);
  su_root_destroy(root);
  su_home_deinit(home);
  su_deinit();
}

int sofiaDriver::start()
{
  ua->driver_ready=true;
  su_root_run(root);
  return 1;
}

void sofiaDriver::stop()
{
  nua_shutdown(nua);
}

int sofiaDriver::register_line(const char *display_name, const char *user_name, const char *registrar, const char *url, void **handler)
{
  nua_handle_t *hd = nua_handle(nua, NULL,
				SIPTAG_TO_STR(url),
				SIPTAG_FROM_STR(url),
				TAG_END());
  nua_register(hd,
	       //NUTAG_M_DISPLAY(display_name),
	       //NUTAG_M_USERNAME(user_name),
	       NUTAG_REGISTRAR(registrar),
	       NUTAG_KEEPALIVE_STREAM(0),
	       TAG_END());
  (*handler) = (void *) hd;
  return 1;
}

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
	printf("need auth\n");
      }
    if(status==200)
      {
	printf("everything right here around with register\n");
      }
    break;
  default:
    printf("driver gets event\n");
    break;
  }
}
