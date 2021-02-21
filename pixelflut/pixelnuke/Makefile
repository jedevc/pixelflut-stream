.PHONY: default all clean

CC ?= gcc
TARGET ?= pixelnuke

override CFLAGS += -Wall -pthread
override LDFLAGS += -pthread

LIBS = -levent -levent_pthreads -lrt -lGL -lGLEW -lglfw

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
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o $(TARGET)
