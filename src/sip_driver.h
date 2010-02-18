#ifndef tsip_sip_driver
#define tsip_sip_driver

class sipDriver
{
 public:
  sipDriver(int max){ max_call = max; }; 
  virtual int start(){return 0;}
  virtual void stop(){}
  virtual int register_line(const char *display_name, const char *user_name,
                            const char *registrar, const char *url,
                            const char *line){return 0;}
  virtual int unregister_line(void *nh){return 0;}
  virtual int auth_dialog(const char *, void *, const char*){return 0;}
  virtual int generate_call(const char *user_name, const char *dest,
                            const char *from, const char *line){return 0;}
 protected:
  int max_call;
};

#endif
