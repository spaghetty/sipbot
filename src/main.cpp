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
  Ua app("*",5477);
  app.set_realm("amati.delcospa.net");
  app.set_proxy("192.168.64.228");
  //app.add_event(&e1);
  //app.add_event(&e2);
  //app.add_event(&e3);
  //app.add_event(&e4);
  printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("502","502"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("502","502"))
    printf("try to add 500 again");
  app.add_line("703","703");
  app.show_lines();
  printf("===================================\n");
  app.del_line("703");
  app.show_lines();
  Line *l = app.get_line("502");
  if(l)
    printf("minchia che fico \n");
  printf("===================================\n");
  app.start_loop();
  
  while(! app.register_all())
    { sleep(0.5); }
  sleep(10);
  printf("bla\n");
  while(!l->unregister_it())
    sleep(0.5);
  sleep(20);
  app.stop_everything();
}
