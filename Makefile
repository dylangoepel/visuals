CC = clang -O0 -g
CFLAGS = $(shell pkg-config --cflags --libs cairo gtk+-3.0)

binaries = $(shell ls *.c | sed "s,\.c$$,,g")

all: $(binaries)

.PHONY: clean
clean:
	rm -f $(binaries)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
