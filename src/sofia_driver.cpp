#include "sofia_driver.h"

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
  printf("driver gets event\n");
}
