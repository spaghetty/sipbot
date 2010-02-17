
#ifndef tsip_sofia_driver
#define tisp_sofia_driver

#include "sip_driver.h"
#include <sofia-sip/nua.h>

class Ua;

class sofiaDriver: public sipDriver
{
 public:
  sofiaDriver(Ua *main_ua, const char *bind_url, const char *proxy);
  ~sofiaDriver();
  
  /* Driver inteface function */
  int start();
  void stop();
  int register_line(const char *display_name, 
		    const char *user_name, 
		    const char *registrar,
		    const char *url);

  int unregister_line(void *nh);

  int auth_dialog(const char *, void *dialog, const char*);

  /* end Driver stuff */
 protected:
  static void event_manager(nua_event_t, 
			    int,
			    const char*, 
			    nua_t*, 
			    nua_magic_t*, 
			    nua_handle_t*, 
			    nua_hmagic_t*, 
			    const sip_t*, 
			    tagi_t*);

  void app_shutdown();
  su_home_t home[1];
  su_root_t *root;
  nua_t *nua;
  nua_handle_t *handle;
  Ua *ua;
 private:
};

#endif
