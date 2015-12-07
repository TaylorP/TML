INSTALL_PATH?=/usr/local/bin
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

.PHONY: clean install
clean:
	find . -name "*.o" -type f -delete
	rm -f tml_parse
install: tml_parse
	install -m 0755 tml_parse $(INSTALL_PATH)/tml_parse