SOURCES := $(wildcard *.[ch])
TARGETS := test-rbt test-hashTable test-linkList HashRBT-final-version
TODAY 	:= $(shell date +%Y%m%d) 
ARCHIVE := Esercizio2-ASD-$(TODAY).zip
CC		:= gcc
CFLAGS 	:= -g -ggdb3 -Wall

ifeq ($(ALL_ERRORS), yes)
CFLAGS += -Werror
endif

.PHONY: all clean dist

all: $(TARGETS)

# dipendenze
# file objects
test-rbt.o: test-rbt.c
test-hashTable.o: test-hashTable.c
test-linkList.o: test-linkList.c
esercizio2.o: esercizio2.c esercizio2.h
HashRBT-final-version.o: HashRBT-final-version.c esercizio2.h

test-rbt: test-rbt.o
test-hashTable: test-hashTable.o
test-linkList: test-linkList.o
HashRBT-final-version: HashRBT-final-version.o esercizio2.o esercizio2.h


clean:
	@rm -rf $(TARGETS) *.zip *.o results.txt

dist:
	@zip -9 $(ARCHIVE) $(SOURCES) *.pdf *.jpg *.jpeg *.png *.txt Makefile
