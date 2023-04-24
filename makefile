CC = gcc

CFLAGS = -Wall -O3

LDFLAGS = -lm -lSDL2

OBJFILES =	src/math/quaternion.o \
			src/iso/point2d.o src/iso/point3d.o src/iso/color.o src/iso/light.o src/iso/face.o src/iso/faceset.o  \
			src/ui/sdl_gfx.o src/ui/model.o \
			src/sdl_main.o

TARGET = iso

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
