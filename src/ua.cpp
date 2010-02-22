#include "ua.h"
#include "telephone_events.h"
#include "sofia_driver.h"
#include <stdio.h>
#include <stdlib.h>

Ua::Ua(std::string bind, int port, int max_c)
{
  int ret;
  int i;
  bind_ip = bind;
  bind_port = port;
  max_call = max_c;
  driver_ready = false;
  evh = new eventHandler(this);
  for( i=0; i < 4; i++)
    threads[i]=NULL;
  ret = pthread_mutex_init(&lines_lock, NULL);
  ret += pthread_mutex_init(&event_lock, NULL);
  pthread_cond_init(&events_ready, NULL);
};

Ua::~Ua()
{
  pthread_mutex_destroy(&lines_lock);
  pthread_mutex_destroy(&event_lock);
  pthread_cond_destroy(&events_ready);
  delete driver;
  delete evh;
};


void Ua::start_loop()
{
  pthread_create(&threads[0], NULL, &Ua::event_loop, (void *)this);
  pthread_create(&threads[1], NULL, &Ua::sip_driver, (void *)this);
};

void Ua::set_realm(const char *rm)
{
  realm = rm;
};

void Ua::set_proxy(const char *host, int port)
{
  if(registrar.is_empty())
    {
      registrar.set_ip(host);
      registrar.set_port(port);
    }
  proxy.set_ip(host);
  proxy.set_port(port);
};

bool Ua::add_line(const char *user, const char *passwd)
{
  pthread_mutex_lock(&lines_lock);
  pair<line_map_t::iterator,bool> ret;
  Line *l = new Line(this);
  l->set_info(user, passwd, realm.c_str(), proxy.get_uri(false).c_str());
  ret = lines.insert( make_pair(user,l));
  if(!(ret.second))
    delete l;
  pthread_mutex_unlock(&lines_lock);
  return ret.second;
};

Line *Ua::get_line(const char* key)
{
  Line *ret = NULL;
  pthread_mutex_lock(&lines_lock);
  line_map_t::iterator it = lines.find(key);
  if ( it != lines.end())
    ret = it->second;
  pthread_mutex_unlock(&lines_lock);
  return ret;
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
};

void Ua::stop_everything()
{
  printf("go on\n");
  int i;
  state = -1;
  driver->stop();
  add_event(new clientEvent((event_type)CLIENT_EXIT));
  for(i=0; i<4; i++)
    {
      if(threads[i])
	pthread_join(threads[i],NULL);
    }
};

void Ua::show_lines()
{
  pthread_mutex_lock(&lines_lock);

  for(line_map_t::iterator it = lines.begin(); it != lines.end(); it++)
    printf("key:%s, uri %s \n", (*it).first.c_str(),
           ((*it).second)->get_uri(true).c_str());

  pthread_mutex_unlock(&lines_lock);
};

bool Ua::register_all()
{
  if(driver_ready)
    {
      pthread_mutex_lock(&lines_lock);

      for(line_map_t::iterator it = lines.begin(); it != lines.end(); it++)
        ((*it).second)->register_it();

      pthread_mutex_unlock(&lines_lock);
      return true;
    }
  return false;
}

void *Ua::event_loop(void *self)
{
  bool stop = false;
  Ua *This =  static_cast<Ua*>(self);
  pthread_mutex_lock(&(This->event_lock));
  while( !This->events.empty() and !stop)
    {
      baseEvent *e = (This->events).front();
      (This->events).pop();
      printf ("got event %d\n", (int)e->getType());
      This->evh->manage_event(e);
      stop = (CLIENT_EXIT == (e->getType()));
    }
  if(stop)
    {
      pthread_mutex_unlock(&(This->event_lock));
      pthread_exit(NULL);
      return NULL;
    }
  pthread_cond_wait(&(This->events_ready), &(This->event_lock));
  pthread_mutex_unlock(&(This->event_lock));
  event_loop(This);
  return NULL;
};

void Ua::add_event(baseEvent *e)
{
  bool empty= false;
  pthread_mutex_lock(&event_lock);
  empty = events.empty();
  events.push(e);
  if(empty)
    pthread_cond_signal(&events_ready);
  pthread_mutex_unlock(&event_lock);
}

void *Ua::sip_driver(void *self)
{
  Ua *This = static_cast<Ua*>(self);
  // build url in the scheme of sip:ip:port
  sipServer url((This->bind_ip).c_str(),"",This->bind_port);
  This->driver = new sofiaDriver(This, url.get_uri(true).c_str(), 
				 (This->proxy).get_uri(true).c_str(),
				 2);
  //This->sip_loop_rand_event_gen();
  This->driver->start();
  pthread_exit(NULL);
}
