#ifndef tsip_sip_driver
#define tsip_sip_driver

typedef void* dialog_h;

class sipDriver
{
 public:
  sipDriver(int max){ max_call = max; }; 
  virtual int start(){return 0;}
  virtual void stop(){}
  virtual int getlocalip(){};
  virtual int register_line(const char *display_name, const char *user_name,
                            const char *registrar, const char *url,
                            const char *line){return 0;}
  virtual int unregister_line(dialog_h nh){return 0;}
  virtual int auth_dialog(const char *, dialog_h, const char*){return 0;}
  virtual int generate_call(const char *user_name, const char *dest,
                            const char *from, const char *line){return 0;}

  virtual void send_cancel(dialog_h dialog){}
  virtual void send_line_busy(dialog_h dialog){}

 protected:
  virtual void send_line_free(dialog_h dialog){}

  int max_call;
};

#endif
