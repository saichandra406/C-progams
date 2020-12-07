CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=test-main

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
future.o: future.h
future.o: eval.h
future.o: cards.h
input.o: input.h
input.o: eval.h
input.o: cards.h
test-main.o: input.h
test-main.o: future.h
test-main.o: eval.h
test-main.o: deck.h
test-main.o: cards.h
