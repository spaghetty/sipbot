#include "telephone_events.h"
#include "sip_server.h"
#include "line.h"
#include "ua.h"
#include <stdio.h>
#include <string>

int main(int argc, char* argv[])
{
  clientEvent e1((event_type)25), e2((event_type)18), e5(EXIT);
  callEvent e3((event_type)30),e4((event_type)35);
  Ua app("192.168.64.224",5066);
  app.set_realm("amati.delcospa.net");
  app.set_proxy("192.168.64.228");
  app.add_event(&e1);
  app.add_event(&e2);
  app.add_event(&e3);
  app.add_event(&e4);
  printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("500","500"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("500","500"))
    printf("try to add 500 again");
  app.add_line("703","703");
  app.show_lines();
  printf("===================================\n");
  app.del_line("500");
  app.show_lines();
  printf("===================================\n");
  app.start_loop();
  
  while(! app.register_all())
    { sleep(0.5); }
  sleep(20);
  app.stop_everything();
}
