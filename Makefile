CC=gcc
CFLAGS=-Wall -Wextra

.PHONY: all
all: brightness

brightness: brightness.o config.h
	$(CC) -o $@ $<
	sudo chown root:root $@
	sudo chmod u-w+s $@

.PHONY: clean
clean:
	rm -f *.o brightness
