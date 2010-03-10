LDADD = $(SOFIA_SIP_UA_LIBS) $(LTLIBINTL)

noinst_LIBRARIES = libtsip.a
libtsip_a_SOURCES = call.cpp \
		base_event.cpp \
		telephone_events.cpp \
		sip_server.cpp \
		line.cpp \
		ua.cpp \
		event_handler.cpp \
		sofia_driver.cpp 

libtsip_a_LIBS = ../lib/libgnu.a

libtsip_a_CPPFLAGS = -I../lib -I../include $(XML_CPPFLAGS) $(SOFIA_SIP_UA_CFLAGS) $(PTHREAD_CFLAGS)
libtsip_a_DFLAGS = $(XML_LIBS) $(SOFIA_SIP_UA_LIBS) $(PTHREAD_LIBS)

AM_CPPFLAGS =  $(SOFIA_SIP_UA_CFLAGS)
