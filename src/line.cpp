#include "line.h"

Line::Line()
{
  uname = "";
  passwd = "";
  domain = "localhost";
  realm = "localhost";
  proxy = NULL;
  registrar = NULL;
  main_agent = NULL;
};


int Line::set_info(const char *name, 
                   const char *pwd, 
                   const char *dom, 
                   const char* real)
{
  uname.assign(name);
  passwd.assign(pwd);
  domain.assign(dom);
  realm.assign(real);
  if(proxy == NULL)
    proxy = new sipServer(domain.c_str());
  if(registrar == NULL)
    registrar = proxy;
};
