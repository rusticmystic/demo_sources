LDFLAGS += `pkg-config --libs glib-2.0 gstreamer-1.0`
CFLAGS += `pkg-config --cflags glib-2.0 gstreamer-1.0`

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

all: demo

demo: $(OBJECTS)
	libtool --mode=link --tag=CC $(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(wildcard *.o) demo

