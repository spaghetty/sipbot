#include "telephone_events.h"
#include <stdio.h>

int main(int argc, char argv[])
{
  clientEvent e1((event_type)25), e2((event_type)18);

  printf("lorenza puzza %d \n",(int)e1.getType());
}
