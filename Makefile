CC=gcc
CFLAGS=-Wall -Wextra -Werror -fstack-protector-all -O2

PROG=brightness
BIN=/usr/bin

.PHONY: all
all: $(PROG)

.PHONY: install
install: $(PROG)
	install -m 4555 -o root -g root -s $(PROG) $(BIN)

.PHONY: uninstall
uninstall:
	rm -f $(BIN)/$(PROG)

.PHONY: clean
clean:
	rm -f *.o $(PROG)

$(PROG): $(PROG).o config.h
	$(CC) -o $@ $<
