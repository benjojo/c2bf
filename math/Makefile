BF_CC=../cc/c2bf-cc

all: bf_math.o

.PREFIXES: .c .o

.c.o:
	$(BF_CC) < $< > $@

clean:
	rm -f bf_math.o
