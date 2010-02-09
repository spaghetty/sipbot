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


