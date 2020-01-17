CC = gcc-9
PROG = hashtab_test
CFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu11 -O0
LDLIBS =

default: bin/$(PROG)

bin/$(PROG): bin/$(PROG).o bin/hashtab.o
	$(CC) $^ $(LDLIBS) -o $@

bin/$(PROG).o: src/$(PROG).c
	$(CC) $(CFLAGS) -o $@ -c $<

bin/hashtab.o: src/hashtab.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fv bin/*.o bin/$(PROG)
