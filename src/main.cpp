#include "telephone_events.h"
#include "sip_server.h"
#include "line.h"
#include "ua.h"
#include <stdio.h>
#include <string>

#define WORK true
#define real_line "722"

int main(int argc, char* argv[])
{
  Ua app("*",5477,2);
  if(WORK)
    {
      app.set_realm("erin.delcospa.net");
      app.set_proxy("192.168.64.224");
    }
  else
    {
      app.set_realm("192.168.1.102");
      app.set_proxy("192.168.1.102");
    }
  //printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("1002","502"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("1002","1234"))
    printf("try to add 500 again");//you'll never get this
  app.add_line("703","703");
  //app.show_lines();
  printf("===================================\n");
  app.del_line("703");
  app.del_line("502");
  app.del_line("1002");
  /* real line */
  if(WORK)
    {
      app.add_line("722","722");
    }
  else
    {
      app.add_line("1002","1234");
    }
  app.show_lines();
  Line *l = app.get_line(real_line);
  if(l)
    printf("minchia che fico \n firnokkio maledetto\n");
  printf("===================================\n");
  app.start_loop();
  
  while(! app.register_all())
    { 
      printf(".");
      sleep(1); 
    }
  printf("\n");
  //sleep(2);
  printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  sleep(5);
  /*
  while(!l->unregister_it())
    sleep(0.5);
  */
  /*if (l->generate_call("500@amati.delcospa.net")){
    printf("successfully generated call: 500@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
    }*/
  /*if(l->generate_call("700"))
    {
      printf("successfully generated call: 503@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
      }*/
  sleep(30);
  app.stop_everything();
}


