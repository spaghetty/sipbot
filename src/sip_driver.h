#ifndef tsip_sip_driver
#define tsip_sip_driver

class sipDriver
{
 public:
  virtual int start(){};
  virtual void stop(){};
  virtual int register_line(const char *display_name, const char *user_name, const char *registrar,const char *url, void **handler){};
};

#endif
