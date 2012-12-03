CC=gcc
CFLAGS=-Wall -Wextra

.PHONY: all
all: brightness

brightness: brightness.o
	$(CC) -o $@ $<
	sudo chown root:root $@
	sudo chmod u-w+s $@

.PHONY: clean
clean:
	rm -f *.o brightness
