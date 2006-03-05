CC=gcc
CFLAGS=-O2 -g
LDFLAGS=

all: c2bf-1to2 c2bf-1to4

c2bf-1to2: c2bf-1to2.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

c2bf-1to4: c2bf-1to4.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

.PREFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f c2bf-1to2 c2bf-1to4 c2bf-1to2.o c2bf-1to4.o
