#ifndef CORE_H
#define CORE_H

#include <fluidsynth.h>

#include "Mapii.h"
#include "Synth.h"
#include "Instrument.h"

typedef struct core Core;
struct core {
	int current_subdiv;
	Mapii *keyboard_map;
	FluidSynth *synth;
	Instrument *player;
	Instrument *song;
};

/* Prototypes */
Core* core_new(const char *keyboard_map_file);
void core_load_song(Core* core, char* const songfile);
void core_destroy(Core* core);
void core_play_song(Core* core);
void print_keys_pressed(Core* core);

#endif

