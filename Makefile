CC=g++
CFLAGS=-g -Wall -o
OPTIONS=-std=gnu++11
BUILDDIR=build
SRCDIR=src
TARGETDIR=bin
TARGET=middleware server client

all:$(TARGET)
middleware:$(SRCDIR)/middleware.cpp $(BUILDDIR)/calls.o $(BUILDDIR)/linkedlist.o $(BUILDDIR)/objects.o $(BUILDDIR)/services.o $(BUILDDIR)/marshall.o
	$(CC) $^ $(CFLAGS) $(TARGETDIR)/$@
#	$(CC) $^ $(OPTIONS) $(CFLAGS) $(TARGETDIR)/$@
server:$(SRCDIR)/server.cpp $(BUILDDIR)/calls.o $(BUILDDIR)/linkedlist.o $(BUILDDIR)/objects.o $(BUILDDIR)/marshall.o
	$(CC) $^ $(CFLAGS) $(TARGETDIR)/$@
#	$(CC) $^ $(OPTIONS) $(CFLAGS) $(TARGETDIR)/$@
client:$(SRCDIR)/client.cpp $(BUILDDIR)/calls.o $(BUILDDIR)/linkedlist.o $(BUILDDIR)/objects.o $(BUILDDIR)/marshall.o
	$(CC) $^ $(CFLAGS) $(TARGETDIR)/$@
#	$(CC) $^ $(OPTIONS) $(CFLAGS) $(TARGETDIR)/$@
$(BUILDDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) -c $^ -o $@
#	$(CC) $(OPTIONS) -c $^ -o $@
clean:
	rm -rf $(BUILDDIR)/* $(TARGETDIR)/*
