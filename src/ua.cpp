#include "ua.h"
#include "telephone_events.h"
#include <stdio.h>
#include <stdlib.h>

Ua::Ua(std::string bind, int port)
{
  int ret;
  int i;
  bind_ip = bind;
  bind_port = port;
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
  pthread_mutex_unlock(&lines_lock);
  return ret.second;
};

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
  add_event(new clientEvent((event_type)EXIT));
  for(i=0; i<4; i++)
    {
      if(NULL != threads[i])
	pthread_join(threads[i],NULL);
    }
};

void Ua::show_lines()
{
  pthread_mutex_lock(&lines_lock);
  line_map_t::iterator it = lines.begin();
  for( it; it!=lines.end(); it++)
    {
      printf("uri %s \n",((*it).second)->get_uri(true).c_str());
    }
  pthread_mutex_unlock(&lines_lock);
};

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
      stop = (EXIT == (e->getType()));
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
  This->sip_loop_rand_event_gen();
  pthread_exit(NULL);
}

void *Ua::sip_loop_rand_event_gen()
{

  add_event(new callEvent((event_type)(rand()%40)));
  if( state < 0)
    {
      return NULL;
    }
  sleep((rand()%5)/1000);
  sip_loop_rand_event_gen();
}
