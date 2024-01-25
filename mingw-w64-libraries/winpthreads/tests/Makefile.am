#FIXME: The test "test.c" is inherently broken currently.
check_PROGRAMS = t_clock_getres  t_clock_gettime  t_clock_nanosleep  t_clock_settime  #test

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/include

if MSVC
AM_LDFLAGS = ../libpthread.a
else
AM_LDFLAGS = -L$(top_builddir)/fakelib -L$(top_builddir) -lwinpthread -static

#FIXME: t_nanosleep uses getntptimeofday, specific to mingw.
check_PROGRAMS += t_nanosleep
endif

TESTS = $(check_PROGRAMS)
