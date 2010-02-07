bin_PROGRAMS = tsip
tsip_SOURCES = main.cpp base_event.cpp telephone_events.cpp sip_server.cpp line.cpp

tsip_LDADD = $(SOFIA_SIP_UA_LIBS) $(LTLIBINTL)

tsip_CPPFLAGS = $(XML_CPPFLAGS) $(SOFIA_SIP_UA_CFLAGS) $(PTHREAD_CFLAGS)
tsip_DFLAGS = $(XML_LIBS) $(SOFIA_SIP_UA_LIBS) $(PTHREAD_LIBS)

AM_CPPFLAGS =  $(SOFIA_SIP_UA_CFLAGS)
