CC=gcc
CFLAGS=-O2 -g
LDFLAGS=

LEX=flex

YACC=yacc

LD_OBJS=ld.o staticize.o trace.o

all: c2bf-ld

c2bf-ld: $(LD_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LD_OBJS) -o $@

.PREFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LD_OBJS) c2bf-ld
