#include "telephone_events.h"
#include "sip_server.h"
#include "line.h"
#include "ua.h"
#include <stdio.h>
#include <string>

#define WORK 0
#define real_line "1001"

int main(int argc, char* argv[])
{
  Ua app("*",5477);
  if(WORK)
    {
      app.set_realm("amati.delcospa.net");
      app.set_proxy("192.168.64.228");
    }
  else
    {
      app.set_realm("192.168.1.102");
      app.set_proxy("192.168.1.102");
    }
  //printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("502","502"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("502","502"))
    printf("try to add 500 again");//you'll never get this
  app.add_line("703","703");
  app.show_lines();
  printf("===================================\n");
  app.del_line("703");
  app.del_line("502");
  /* real line */
  if(WORK)
    {
      app.add_line("502","502");
    }
  else
    {
      app.add_line("1001","1234");
    }
  app.show_lines();
  Line *l = app.get_line(real_line);
  if(l)
    printf("minchia che fico \nfirnokkio maledetto\n");
  printf("===================================\n");
  app.start_loop();
  
  while(! app.register_all())
    { sleep(0.5); }
  sleep(2);
  printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  /*
  while(!l->unregister_it())
    sleep(0.5);
  */

  /*
  if (l->generate_call("500@amati.delcospa.net")){
    printf("successfully generated call: 500@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
  }
  if(l->generate_call("503@amati.delcospa.net")){
    printf("successfully generated call: 503@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
    }*/

  sleep(30);
  app.stop_everything();
}


