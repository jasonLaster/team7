#include <fluidsynth.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "Synth.h"

static char* audio_driver();

FluidSynth* fluidsynth_new() {
  fluid_settings_t* settings = new_fluid_settings();
  FluidSynth* synth = new_fluid_synth(settings);
  fluid_synth_program_change(synth, 0, 4);
  fluid_settings_setstr(settings, "audio.driver", audio_driver());
  new_fluid_audio_driver(settings, synth);
  fluid_synth_sfload(synth, "FluidR3_GM.sf2", 1);
  return synth;
}

// definitely want to release the fluidsynth object
// probably want to delete all the other shit as well
void fluidsynth_destroy(FluidSynth* fluid) {
	delete_fluid_synth(fluid);
}

/* AUDIO_DRIVER gets the audio driver for the appropriate operating system
 */
static char* audio_driver(){
  struct utsname info;
  uname(&info);  
  return !strcmp(info.sysname, "Darwin")  ? "coreaudio" : "alsa";
  return "coreaudio";
}