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
  Ua app("localhost",5060);
  app.set_realm("spaghetty.net");
  app.set_proxy("192.168.1.109");
  app.add_event(&e1);
  app.add_event(&e2);
  app.add_event(&e5);
  app.add_event(&e3);
  app.add_event(&e4);
  printf("this is just setted proxy %s\n", app.get_proxy());
  if(app.add_line("500","500"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("500","500"))
    printf("try to add 500 again");
  app.add_line("600","600");
  app.show_lines();
  printf("===================================\n");
  app.del_line("500");
  app.show_lines();
  printf("===================================\n");
  app.start_loop();
  sleep(1);
  app.stop_everithing();
  /*clientEvent e1((event_type)25), e2((event_type)18);
  sipServer *s = new sipServer("prova", "");
  std::string a = s->get_uri(1);
  l->set_info("500","500","192.168.1.109","prova.com");
  delete s;
  printf("uri %s \n",a.c_str());
  printf("uri %s \n",l->get_uri(true).c_str()); */
}
