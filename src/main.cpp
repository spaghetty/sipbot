#include "telephone_events.h"
#include "sip_server.h"
#include <stdio.h>
#include <string>

int main(int argc, char* argv[])
{
  clientEvent e1((event_type)25), e2((event_type)18);
  sipServer *s = new sipServer("prova", "");
  printf("lorenza puzza %d \n",(int)e1.getType());
  std::string a = s->get_uri(1);
  delete s;
  printf("uri %s \n",a.c_str());
}
