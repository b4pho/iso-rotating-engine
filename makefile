CC = gcc

CFLAGS = -Wall -O3

LDFLAGS = -lm -lSDL2

OBJFILES =	obj/math/quaternion.o \
		obj/iso/point2d.o \
		obj/iso/point3d.o \
		obj/iso/color.o \
		obj/iso/light.o \
		obj/iso/face.o \
		obj/iso/faceset.o \
		obj/ui/sdl_gfx.o \
		obj/ui/model.o \
		obj/sdl_main.o

TARGET = iso
VPATH=%.c src
VPATH=%.h src
VPATH=%.o obj

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(TARGET) *~
