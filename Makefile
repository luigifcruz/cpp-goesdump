CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/GOESDump
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11 -c -Wall
LIB := -lsathelper
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean

#CC=g++
#CFLAGS=-std=c++11 -c -Wall
#LDFLAGS=-lsathelper
#SOURCES=main.cpp DataHandler.cpp StatisticsHandler.cpp WatchMan.cpp Demuxer.cpp
#OBJECTS=$(SOURCES:.cpp=.o)
#EXECUTABLE=GOESDump
#
#all: $(SOURCES) $(EXECUTABLE)
#
#$(EXECUTABLE): $(OBJECTS)
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
#
#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@
#