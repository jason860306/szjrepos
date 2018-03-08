# Rules for the test code(use 'make check' to execute)
TESTS=MoneyApp
check_PROGRAMS=$(TESTS)
MoneyApp_SOURCES=Money.h MoneyTest.h MoneyTest.cpp MoneyApp.cpp
MoneyApp_CXXFLAGS=$(CPPUNIT_CFLAGS)
MoneyApp_LDFLAGS=$(CPPUNIT_LIBS) -ldl
