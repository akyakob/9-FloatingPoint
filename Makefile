CC = gcc
CFLAGS = -O1 -g -Wall -std=c99 -pedantic -lm -DEN_TIME
MFLAGS = -O1 -g -Wall -std=c99 -pedantic -lm
SOURCE = quadTest.c
OBJ = $(patsubst %.c, %.o, $(SOURCE))
EXE = quadTest
EXEMEM = quadTest_mem
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes 
RESULTS = out.txt
MEMTXT = mem.txt

.SILENT:
all: $(EXE) $(EXEMEM)

$(EXE): $(SOURCE)
	@echo "Compiling quadTest with timing enabled"
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE)

$(EXEMEM): $(SOURCE)
	@echo "Compiling quadTest with timing disabled"
	$(CC) $(MFLAGS) $(SOURCE) -o $(EXEMEM)

test: $(EXE) 
	@echo "Testing... "
	@echo " " > $(RESULTS)
	@echo "Testing ./quadTest -a 0 -b 0 -c 1" >> $(RESULTS)
	./$(EXE) -a 0 -b 0 -c 1 >> $(RESULTS) 2>&1
	@echo " " >> $(RESULTS)
	@echo "Testing ./quadTest -a 1 -b 0" >> $(RESULTS)
	./$(EXE) -a 1 -b 0 >> $(RESULTS) 2>&1
	@echo " " >> $(RESULTS)
	@echo "Testing ./quadTest -a 1 -b 0 -c 1" >> $(RESULTS)
	./$(EXE) -a 1 -b 0 -c 1 >> $(RESULTS) 
	@echo "check out.txt for results"

.PHONY: mem clean test all help
mem: $(EXEMEM)
	@echo "running valgrind..."
	$(VALGRIND) ./$(EXEMEM) -a 1 -b 0 -c 1 > $(MEMTXT) 2>&1
	@echo "valgrind output in mem.txt"

clean: 
	-rm -f $(EXE) $(RESULTS) $(MEMTXT) $(EXEMEM)

help:
	@echo "make options are: all, clean, mem, test"

