CC=gcc
CFLAGS=-std=c11 -Wall -pedantic -W -Wextra
DEBUGFLAGS=-std=c11 -Wall -pedantic -W -Wextra -
FILES=ADT.o List.o ManagedMalloc.o Parser.o Scanner.o Start.o SymTable.o Token.o
TESTFILES=TestExpectToken.o Tests.o TestScanner.o TestStack.o TestSymTable.o
HEADERS=$(wildcard *.h)
%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ $^

default: $(FILES)
	$(CC) $(CFLAGS) compiler $^

test: $(FILES) $(TESTFILES)
	$(CC) $(CFLAGS) compiler-test $^
	./compiler-test