bin_PROGRAMS = tsip
tsip_SOURCES = main.cpp base_event.cpp telephone_events.cpp sip_server.cpp line.cpp ua.cpp event_handler.cpp sofia_driver.cpp

tsip_LDADD = $(SOFIA_SIP_UA_LIBS) $(LTLIBINTL)
tsip_LIBS = ../lib/libgnu.a

tsip_CPPFLAGS = -I../lib $(XML_CPPFLAGS) $(SOFIA_SIP_UA_CFLAGS) $(PTHREAD_CFLAGS)
tsip_DFLAGS = $(XML_LIBS) $(SOFIA_SIP_UA_LIBS) $(PTHREAD_LIBS)

AM_CPPFLAGS =  $(SOFIA_SIP_UA_CFLAGS)
