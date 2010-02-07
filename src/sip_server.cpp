#include "sip_server.h"
#include <sstream>
#include <string>

sipServer::sipServer(const char *ip, const char *fqhn, int port)
{
  this->ip.assign(ip);
  this->fqhn.assign(fqhn);
  this->port = port;
}

std::string sipServer::get_uri(bool type)
{
  std::string s;
   std::stringstream tmp;
  if(type)
    s.append("sip:");
  if( fqhn.length() > 5 )
    s.append(fqhn);
  else
  s.append(ip);
  s.append(":");
  tmp << port;
  s.append(tmp.str());
  return s;
}
