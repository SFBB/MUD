CC=g++
CFLAGS=-c -Wall -std=c++2a
LDFLAGS=
DIR=src
SOURCES=$(wildcard $(DIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@(rm -f $(DIR)/*.o)
	@echo clean done!

.PHONY:run
run:
	@(./$(EXECUTABLE))

.PHONY:uninstall
uninstall:
	@(rm -f $(EXECUTABLE))
	@echo uninstall done!
