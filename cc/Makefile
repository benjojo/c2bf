CC=gcc
CFLAGS=-O2 -g
LDFLAGS=

LEX=flex

YACC=yacc

DISPAST_OBJS=dispast.o gram.o main.o scan.o 
CC_OBJS=dispast.o gram.o genbfmain.o scan.o genbf/libgenbf.a

all: c2bf-dispast c2bf-cc

c2bf-dispast: $(DISPAST_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DISPAST_OBJS) -o $@

c2bf-cc: $(CC_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CC_OBJS) -o $@

genbf/libgenbf.a: genbf/*.c
	cd genbf ; $(MAKE)

.PREFIXES: .y .l .c .o

.y.c:
	$(YACC) -dv $<
	mv y.tab.c $@

.l.c:
	$(LEX) -t $< > $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(DISPAST_OBJS) $(CC_OBJS) gram.c y.tab.h y.output scan.c \
		c2bf-dispast c2bf-cc
	cd genbf ; $(MAKE) clean
