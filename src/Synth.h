#ifndef SYNTH_H
#define SYNTH_H

typedef fluid_synth_t FluidSynth;


/* Prototypes */
FluidSynth* fluidsynth_new();
void fluidsynth_destroy(FluidSynth* fluid);

#endif
