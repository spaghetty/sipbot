#include "ua.h"

#include <stdio.h>

Ua::Ua(std::string bind, int port)
{
  bind_ip = bind;
  bind_port = port;
}

void Ua::set_realm(const char *rm)
{
  realm = rm;
}

void Ua::set_proxy(const char *host, int port)
{
  if(registrar.is_empty())
    {
      registrar.set_ip(host);
      registrar.set_port(port);
    }
  proxy.set_ip(host);
  proxy.set_port(port);
}

int Ua::add_line(const char *user, const char *passwd)
{
  Line *l = new Line(this);
  l->set_info(user, passwd, realm.c_str(), proxy.get_uri(false).c_str());
  lines.insert( make_pair(user,l));
  return 1;
}

void Ua::show_lines()
{
  line_map_t::iterator it = lines.begin();
  for( it; it!=lines.end(); it++)
    {
      printf("uri %s \n",((*it).second)->get_uri(true).c_str());
    }
  
}
