#ifndef tsip_sofia_driver
#define tisp_sofia_driver

#include "sip_driver.h"
#include "call.h"
#include <sofia-sip/nua.h>
#include <map>
#include <string>

typedef std::map<std::string, Call*> call_map_t;

class Ua;

class sofiaDriver: public sipDriver
{
 public:
  sofiaDriver(Ua *main_ua, const char *bind_url, const char *proxy, int max);
  ~sofiaDriver();
  
  /* Driver inteface function */
  int start();
  void stop();
  int register_line(const char *display_name, 
		    const char *user_name, 
		    const char *registrar,
		    const char *url,
		    const char *line);

  int unregister_line(void *nh);

  int auth_dialog(const char *, void *dialog, const char*);

  int generate_call(const char *display_name, const char *dest, const char *from, const char *line);

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

  Call *add_call(const char *id);
  Call *delete_call(const char *id);
  void app_shutdown();
  su_home_t home[1];
  su_root_t *root;
  call_map_t *calls;
  nua_t *nua;
  nua_handle_t *handle;
  Ua *ua;
 private:
};

#endif
