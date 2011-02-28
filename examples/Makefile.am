bin_PROGRAMS=tsiptest
tsiptest_SOURCES= base_text/test_ua.cpp 

tsiptest_LDADD = ../src/libtsip.a $(SOFIA_SIP_UA_LIBS)
tsiptest_LIBS = ../lib/libgnu.a

tsiptest_CPPFLAGS = -I../lib -I../include $(XML_CPPFLAGS) $(SOFIA_SIP_UA_CFLAGS) $(PTHREAD_CFLAGS)
tsiptest_DFLAGS = $(XML_LIBS) $(SOFIA_SIP_UA_LIBS) $(PTHREAD_LIBS)

AM_CPPFLAGS =  $(SOFIA_SIP_UA_CFLAGS)
