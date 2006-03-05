CC=gcc
CFLAGS=-O2 -g
LDFLAGS=

OBJS=bfstrip.o

all: c2bf-strip

c2bf-strip: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

.PREFIXES: .y .l .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) c2bf-strip
