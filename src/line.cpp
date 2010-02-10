#include "line.h"

Line::Line(Ua *app)
{
  uname = "";
  passwd = "";
  domain = "localhost";
  realm = "localhost";
  proxy = NULL;
  registrar = NULL;
  main_agent = app;
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
  return 1;
};


int Line::set_outproxy(char *px, int po)
{
  if( proxy == NULL)
    proxy = new sipServer(px,"",po);
  else
    {
      proxy->set_ip(px);
      proxy->set_port(po);
    }
  return 1;
};

int Line::set_registrar(char *ip, int po)
{
  if( registrar == NULL)
    registrar = new sipServer(ip,"",po);
  else
    {
      registrar->set_ip(ip);
      registrar->set_port(po);
    }
  return 1;
};


std::string Line::get_uri(bool with)
{
  std::string res;
  res.assign(uname);
  res.append("@");
  res.append(domain);
  if(with)
    {
      res.append(">");
      res.insert(0,"<sip:");
    }
  return res;
};

bool Line::register_it()
{
};

bool Line::unregister_it()
{
};

bool Line::generate_call(const char *dialstring)
{
}
