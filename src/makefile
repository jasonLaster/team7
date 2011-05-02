OBJS =  core.o mapii.o notemapping.o synth.o instrument.o load.o gui.o support.o graphics.o graphic_note.o
BINS =  core mapii notemapping synth instrument load gui support graphic_note graphics main
PROGS = Core.c Mapii.c NoteMapping.c Synth.c Instrument.c Load.c Support.c Graphic_Note.c Graphics.c

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

all: psyche

main.o:  Main.c
	gcc -c $(CFLAGS) -o main.o Main.c $(INCLUDES)

notemapping.o: NoteMapping.c NoteMapping.h Instrument.h
	gcc -c $(CFLAGS) -o notemapping.o NoteMapping.c $(INCLUDES)

instrument.o: Instrument.c Instrument.h
	gcc -c $(CFLAGS) -o instrument.o Instrument.c $(INCLUDES)

mapii.o:  Mapii.c Mapii.h
	gcc -c $(CFLAGS) -o mapii.o Mapii.c $(INCLUDES)

synth.o:  Synth.c Synth.h
	gcc -c $(CFLAGS) -o synth.o Synth.c $(INCLUDES)

load.o:  Load.c Load.h
	gcc -c $(CFLAGS) -o load.o Load.c $(INCLUDES)

core.o:  Core.c Core.h
	gcc -c $(CFLAGS) -o core.o Core.c $(INCLUDES)

gui.o: Gui.c Gui.h
	gcc -c $(CFLAGS) -o gui.o Gui.c $(INCLUDES)

graphic_note.o: Graphic_Note.c Graphic_Note.h
	gcc -c $(CFLAGS) -o graphic_note.o Graphic_Note.c $(INCLUDES)

graphics.o:   Graphics.c Graphics.h
	gcc -c $(CFLAGS) -o graphics.o Graphics.c $(INCLUDES)

support.o:  Support.c Support.h
	gcc -c $(CFLAGS) -o support.o Support.c $(INCLUDES)

psyche: main.o $(OBJS)
	gcc -o psyche main.o $(OBJS) $(LIBS)
	#pandoc -o documentation.html documentation

clean:
	rm -f $(BINS)
	rm -f *.o
	rm -f documentation.html ../spec/technical-spec.html ../spec/technical-spec

doc:
	ruby ../spec/build-technical-documentation.rb *.h
	pandoc -o ../spec/technical-spec.html ../spec/technical-spec
	rm -f documentation.rb


# DRIVERS

# NOTEMAPPING driver
notemapping-driver.o: notemapping-driver.c NoteMapping.h Mapii.h Instrument.h Load.h
	gcc -c $(CFLAGS) -o notemapping-driver.o notemapping-driver.c

notemapping-driver: notemapping-driver.o mapii.o support.o notemapping.o instrument.o load.o
	gcc -o notemapping-driver notemapping-driver.o mapii.o support.o notemapping.o instrument.o load.o

# CORE driver
core-driver.o: core-driver.c Core.h
	gcc -c $(CFLAGS) -o core-driver.o core-driver.c $(INCLUDES)

core-driver: core-driver.o core.o mapii.o notemapping.o synth.o instrument.o support.o load.o
	gcc -o core-driver core-driver.o core.o mapii.o notemapping.o synth.o instrument.o support.o load.o $(LIBS)

# LOAD driver 
load-driver.o: Load_Driver.c Load.c
	gcc -c $(CFLAGS) -o load-driver.o Load_Driver.c $(INCLUDES)

load-driver:  load-driver.o load.o
	gcc $(CFLAGS) -o load-driver Mapii.c NoteMapping.c Load.c Load_Driver.c Support.c 

# GRAPHIC driver 

graphics-driver.o: Graphics_Driver.c 
	gcc -c $(CFLAGS) -o graphics-driver.o Graphics_Driver.c $(INCLUDES)

graphics-driver: graphics-driver.o graphics.o graphic_note.o
	gcc -o graphics-driver graphics-driver.o graphics.o graphic_note.o $(LIBS)
