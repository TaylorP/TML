IDIR=./
CC=g++
CFLAGS=-std=c++11 -O3 -I$(IDIR)
PLAIN_OBJ = main.o \
			element/functionElement.o \
			element/textElement.o \
			function/functionTable.o \
			parser/parser.o \
			text/replacer/apostropheReplacer.o \
			text/replacer/dashReplacer.o \
			text/replacer/pairReplacer.o \
			text/replacer/replacerTable.o \
			text/replacer/urlReplacer.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

tml_parse: $(PLAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o
	rm -f tml_parse
