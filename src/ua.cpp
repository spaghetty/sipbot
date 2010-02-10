#include "ua.h"

#include <stdio.h>

Ua::Ua(std::string bind, int port)
{
  int ret;
  bind_ip = bind;
  bind_port = port;
  ret = pthread_mutex_init(&lines_lock, NULL);
  ret += pthread_mutex_init(&event_lock, NULL);
}

Ua::~Ua()
{
  pthread_mutex_destroy(&lines_lock);
  pthread_mutex_destroy(&event_lock);
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

bool Ua::add_line(const char *user, const char *passwd)
{
  pthread_mutex_lock(&lines_lock);
  pair<line_map_t::iterator,bool> ret;
  Line *l = new Line(this);
  l->set_info(user, passwd, realm.c_str(), proxy.get_uri(false).c_str());
  ret = lines.insert( make_pair(user,l));
  pthread_mutex_unlock(&lines_lock);
  return ret.second;
}

bool Ua::del_line(const char *key)
{
  pthread_mutex_lock(&lines_lock);
  bool ret = false;
  line_map_t::iterator it = lines.find(key);
  if( it != lines.end())
    {
      lines.erase(it);
      ret = true;
    }
  pthread_mutex_unlock(&lines_lock);
  return ret;
}

void Ua::show_lines()
{
  pthread_mutex_lock(&lines_lock);
  line_map_t::iterator it = lines.begin();
  for( it; it!=lines.end(); it++)
    {
      printf("uri %s \n",((*it).second)->get_uri(true).c_str());
    }
  pthread_mutex_unlock(&lines_lock);
}
