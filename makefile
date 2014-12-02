PROJECT = Program_3
TARGET = fly

SRC_FILES = \
  Makefile \
  fly.cpp \
  flight.cpp

OBJ_FILES = \
  fly.o \
  flight.o

HDR_FILES = \
  flight.h
CC = g++
CFLAGS = -g -Wall 

$(TARGET):  	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -g -o $@

$(PROJECT).tar.gz \
dist:		$(SRC_FILES)
		tar -cvvf $(PROJECT).tar $(SRC_FILES)
		gzip $(PROJECT).tar

clean:
		rm -f $(TARGET) *.o *~


