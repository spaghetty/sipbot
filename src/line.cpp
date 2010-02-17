#include "line.h"
#include "ua.h"

Line::Line(Ua *app)
{
  uname = "";
  passwd = "";
  domain = "localhost";
  realm = "localhost";
  proxy = NULL;
  registrar = NULL;
  is_registered = 0;
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
  if(main_agent->driver != NULL)
    {
      is_registered = -1; // TRING //
      std::string u = "<sip:";
      u.append(uname);
      u.append("@");
      u.append((registrar->get_uri(false)).c_str());
      u.append(">");
      (main_agent->driver)->register_line(uname.c_str(),
					  uname.c_str(),
					  registrar->get_uri(true).c_str(),
					  u.c_str());
      return true;
    }
  return false;  
};

bool Line::unregister_it()
{
  if(reg_handler and is_registered == 1)
    {
      (main_agent->driver)->unregister_line(reg_handler);
      return true;
    }
  return false;
};

string Line::get_auth()
{
  string auth = "digest:";
  auth.append("\"");
  auth.append(domain);
  auth.append("\"");
  auth.append(":");
  auth.append(uname);
  auth.append(":");
  auth.append(passwd);

  return auth;
};

void Line::auth_dialog(void *dialog)
{
  
  main_agent->driver->auth_dialog(get_auth().c_str(),dialog, registrar->get_uri(true).c_str());

}

bool Line::generate_call(const char *dialstring)
{
}
