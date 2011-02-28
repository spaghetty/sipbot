#include "telephone_events.h"
#include "sip_server.h"
#include "line.h"
#include "ua.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>
#include <string.h>
#include <netdb.h>
/*! example ua.cpp
  stuff here just to start documenting something
*/

#define LOST 0
#define HOME 1
#define WORK 2


int main(int argc, char* argv[])
{
  struct hostent *myhost;
  int location;
  location = LOST;
  in_addr ia;
  char myip[16];
  const char *real_line, *other_party;
  char machine_name[HOST_NAME_MAX+1];
  memset(machine_name, 0, HOST_NAME_MAX+1);
  gethostname (machine_name, HOST_NAME_MAX);
  myhost = gethostbyname(machine_name);
  
  
  if (myhost)
    {
      
      ia.s_addr = *((u_long *) (myhost->h_addr_list[0]));
      strcpy(myip,inet_ntoa(ia));
    }
  printf("Got Ip Addr %s\n",myip);
  Ua app("*",5477,2);
  printf("%s\n",myip);
  if(strcmp(myip,"192.168.2.108")==0)
    {
      /* home sweet home */
      printf("well i'm at home\n");
      location = HOME;
      app.set_realm("192.168.1.108");
      app.set_proxy("192.168.1.108");
    }
  if(strcmp(myip,"192.168.64.37")==0)
    {
      /* i'm at work */
      printf("well i'm at work\n");
      location = WORK;
      app.set_realm("testpbx.fastdatatel.net");
      app.set_proxy("192.168.69.1");
    }

  //printf("this is just setted proxy %s\n", app.get_proxy());
  /*if(app.add_line("2000","2000"))
    app.show_lines();
  printf("===================================\n");
  if(app.add_line("2001","1234"))
    printf("try to add 500 again");//you'll never get this
  app.add_line("703","703");
  //app.show_lines();
  printf("===================================\n");
  app.del_line("703");
  app.del_line("2000");
  app.del_line("2001");*/
  /* real line */
  if(location != LOST)
    {
      if(location == WORK)
	{
	  app.add_line("2005","2005");
	  real_line="2005";
	  other_party="2003";
	}
      else
	{
	  app.add_line("2000","2000");
	  real_line="2000";
	  other_party="5000";
	}
      app.show_lines();
      Line *l = app.get_line(real_line);
      if(l)
	printf("a line is valid\n");
      printf("===================================\n");
      app.start_loop();
      
      while(! app.register_all())
	{ 
	  printf(".");
	  sleep(1); 
	}
      printf("\n");
      printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
      sleep(5);
      /*
	while(!l->unregister_it())
	sleep(0.5);
      */
      if( l )
	{
	  if(l->generate_call(other_party))
	    {
	      printf("successfully generated call to %s ext -> \n",other_party);//, l->get_registrar(false));
	    }
	}
      else
	{
	  printf("hai sbagliato linea\n");
	}
      
      sleep(30);
      app.stop_everything();
    }
  else
    {
      printf("damn we are lost\n");
    }
  return 1;
}
