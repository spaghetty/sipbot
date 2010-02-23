#include "telephone_events.h"
#include "sip_server.h"
#include "line.h"
#include "ua.h"
#include <stdio.h>
#include <string>

int main(int argc, char* argv[])
{
  clientEvent e1((event_type)25), e2((event_type)18), e5(CLIENT_EXIT);
  callEvent e3((event_type)30),e4((event_type)35);
  Ua app("*",5477,2);
  app.set_realm("erin.delcospa.net");
  app.set_proxy("192.168.64.224");
  //app.add_event(&e1);
  //app.add_event(&e2);
  //app.add_event(&e3);
  //app.add_event(&e4);
  printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("772","772"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("772","772"))
    printf("try to add 500 again");//you'll never get this
  app.add_line("703","703");
  app.show_lines();
  printf("===================================\n");
  app.del_line("703");
  app.show_lines();
  Line *l = app.get_line("772");
  if(l)
    printf("minchia che fico \nfirnokkio maledetto\n");
  printf("===================================\n");
  app.start_loop();
  
  while(! app.register_all())
    { sleep(0.5); }
  sleep(2);
  printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  sleep(5);
  /*
  while(!l->unregister_it())
    sleep(0.5);
  */
  /*if (l->generate_call("500@amati.delcospa.net")){
    printf("successfully generated call: 500@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
    }*/
  if(l->generate_call("700@erin.delcospa.net")){
    printf("successfully generated call: 503@amatrix.delcospa.net -> %s\n", l->get_registrar(false));
  }
  sleep(30);
  app.stop_everything();
}


