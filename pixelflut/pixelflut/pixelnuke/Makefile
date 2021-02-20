.PHONY: default all clean

CC = gcc
LD = ld
CFLAGS = -Wall -pthread
LDFLAGS = -pthread
LIBS = -levent -levent_pthreads -lrt -lGL -lGLEW -lglfw
TARGET = pixelnuke

default: CFLAGS += -O2 -flto
default: $(TARGET)
all: default

debug: CFLAGS += -DDEBUG -g
debug: $(TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -fuse-ld=$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o $(TARGET)
