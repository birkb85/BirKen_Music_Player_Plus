#ifndef TESTSONG_H
#define TESTSONG_H

const int testSongSize = 8;
const int testSongDurationMultiplier = 30;

const int testSongNotes[] PROGMEM = {
  NOTE_E3, NOTE_E3, 0, NOTE_CS3, NOTE_CS3, 0, NOTE_D3, NOTE_E3
};

const int testSongDurations[] PROGMEM = {
  32, 32, 32, 32, 32, 32, 32, 32
};

#endif
