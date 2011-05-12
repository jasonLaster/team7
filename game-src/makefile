BINS = graphic_note graphics
STDERR = 2>> output

UNAME := $(shell uname -s)

ifeq "$(UNAME)" "Darwin"
	OS=macosx
endif
ifeq "$(UNAME)" "Linux"
	OS=linux
endif

ifeq "$(OS)" "macosx"
CFLAGS = -Wall --std=c99 -pedantic -g  `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gtkglext-1.0 gtkglext-x11-1.0`
INCLUDES = -I/opt/local/include/
LIBS = -L/opt/local/lib -lfluidsynth `pkg-config --libs gtk+-2.0` `pkg-config --libs gtkglext-1.0` `pkg-config --libs gtkglext-x11-1.0`
endif
ifeq "$(OS)" "linux"
CFLAGS = -Wall --std=c99 -pedantic -g  `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs gtkglext-1.0 gtkglext-x11-1.0`
INCLUDES = -I/var/cache/apt/archives/include/
LIBS = -L/var/cache/apt/archives/lib -lfluidsynth `pkg-config --libs gtk+-2.0` `pkg-config --libs gtkglext-1.0 gtkglext-x11-1.0`
endif

all: graphics-driver

graphics.o:   graphics.c graphics.h
	gcc -c $(CFLAGS) -o graphics.o graphics.c $(INCLUDES)

gui.o:	gui.c gui.h
	gcc -c $(CFLAGS) -o gui.o gui.c $(INCLUDES)


clean:
	rm -f $(BINS)
	rm -f *.o
	rm -f documentation.html ../spec/technical-spec.html ../spec/technical-spec

doc:
	ruby ../spec/build-technical-documentation.rb *.h
	pandoc -o ../spec/technical-spec.html ../spec/technical-spec
	rm -f documentation.rb


# DRIVERS

graphics-driver.o: graphics_driver.c 
	gcc -c $(CFLAGS) -o graphics-driver.o Graphics_Driver.c $(INCLUDES)

<<<<<<< Updated upstream
<<<<<<< Updated upstream
graphics-driver: graphics-driver.o graphics.o graphics_helpers.o gui.o
=======
graphics-driver: graphics-driver.o graphics.o gui.o
>>>>>>> Stashed changes
=======
graphics-driver: graphics-driver.o graphics.o gui.o
>>>>>>> Stashed changes
	gcc -o graphics-driver graphics-driver.o graphics.o gui.o $(LIBS)
