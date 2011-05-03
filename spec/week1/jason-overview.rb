##################################
Main

  Main Methods
  main
  quit_app

##################################
Psyche

  Psyche Struct
    notes  ~ *NoteMapping
    player ~ *Instrument
    song   ~ *Instrument

  Psyche Methods
    psyche_new => *Psyche
    cb_keypress
    cb_keyrelease
    cb_beat
    cb_load_song
    cb_play_song
    pyche_destroy

##################################
NoteMapping

  NoteMapping Struct
    piano_notes ~ *[string] e.g. ["c", "d", ... "c'", "d'"]
    qwerty_keys ~ *[char] e.g. ['q', 'w', 'e'...]
    medi_notes  ~ *[int] e.g. [60,61,62...]
    num ~ int

  NoteMapping Methods
    load_note_mapping(filename) => NoteMapping*
    piano_note_index(string) => int
    qerty_key_index(char) => int
    note_mapping_destroy

##################################
Instruments

  Instrument Struct
    instrument ~ int
    synth      ~ *FluidSynth
    notes      ~ *[int]

  Instrument Methods
    new_instrument => *Instrument
    note_on(Instrument* instrument, int) => 0 or 1   # e.g. song.note_on(note*beat) => 1 , player.note_on(key)
    instrument_destroy

##################################    
Synth

  Synth Methods
    new_synth
    synth_on
    synth_off
    synth_destroy
