SOURCES := $(wildcard *.[ch])
TARGETS := test-rbt test-hashTable test-linkList Experiment-es2
TODAY 	:= $(shell date +%Y%m%d) 
ARCHIVE := Esercizio2-ASD-$(TODAY).zip
CC		:= gcc
CFLAGS 	:= -std=c17 -ggdb3 -O2 -g3 -Wall

ifeq ($(ALL_ERRORS), yes)
CFLAGS += -Werror
endif

.PHONY: clean dist

all: $(TARGETS)

# dipendenze
# file objects
esercizio2.o: esercizio2.c esercizio2.h
test-rbt.o: test-rbt.c
test-hashTable.o: test-hashTable.c
test-linkList.o: test-linkList.c
HashRBT_final_version.o: HashRBT_final_version.c esercizio2.h

# executables
test-rbt: test-rbt.o
test-hashTable: test-hashTable.o
test-linkList: test-linkList.o
Experiment-es2: HashRBT_final_version.o esercizio2.o

clean:
	@rm -rf $(TARGETS) *.zip *.o

dist:
	@zip -9 $(ARCHIVE) $(SOURCES) *.pdf *.jpg Makefile
