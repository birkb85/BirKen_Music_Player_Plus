// Source available on:
// https://github.com/birkb85/BirKen_Music_Player_Plus

#include <Tone.h>  // https://github.com/bhagman/Tone
#include "Notes.h"
#include "Song69.h"
#include "TestSong.h"
#include "Thunder.h"
#include "Sang_57_enkel.h"
#include "Holding_fast_enkel.h"

Tone tones[2];
int noteIndexes[2] = { 0, 0 };
int noteDurations[2] = { 0, 0 };

unsigned long time;
unsigned long timeOld;
unsigned long timeElapsed;

void setup(void) {
  //Serial.begin(9600);

  tones[0].begin(5);
  tones[1].begin(6);

  time = millis();
  timeOld = time;
  timeElapsed = 0;
}

void loop(void) {
  time = millis();
  timeElapsed = time - timeOld;
  timeOld = time;

  // Possibility of cutting sound after an amount of millis, so you dont go crazy :P
  // if (time > 60000) {
  //   tones[0].stop();
  //   tones[1].stop();
  //   return;
  // }

  // ---- PLAY TRACKS BELOW HERE ----

  playTrack(0, song69Notes, song69Durations, song69Size);

  // playTrack(0, testSongNotes, testSongDurations, testSongSize);

  // playTrack(0, thunderNotes, thunderDurations, thunderSize);

  // playTrack(0, Sang_57_enkel_Notes1, Sang_57_enkel_Durations1, Sang_57_enkel_Size1);
  // playTrack(1, Sang_57_enkel_Notes2, Sang_57_enkel_Durations2, Sang_57_enkel_Size2);

  // playTrack(0, Holding_fast_enkel_Notes1, Holding_fast_enkel_Durations1, Holding_fast_enkel_Size1);
  // playTrack(1, Holding_fast_enkel_Notes2, Holding_fast_enkel_Durations2, Holding_fast_enkel_Size2);
}

void playTrack(int toneIndex, int *notes, int *durations, int size) {
  if (noteDurations[toneIndex] > 0) {
    noteDurations[toneIndex] -= timeElapsed;
  } else {
    int note = pgm_read_word_near(notes + noteIndexes[toneIndex]);
    int noteNext = 0;
    if (noteIndexes[toneIndex] < size - 1) {
      noteNext = pgm_read_word_near(notes + noteIndexes[toneIndex] + 1);
    } else {
      noteNext = pgm_read_word_near(notes);
    }
    int duration = pgm_read_word_near(durations + noteIndexes[toneIndex]);

    if (note > 0) {
      if (noteNext > 0 && noteNext == note && duration > 50) {
        tones[toneIndex].play(note, duration - 50);
      } else {
        tones[toneIndex].play(note);
      }
    } else {
      tones[toneIndex].stop();
    }
    noteDurations[toneIndex] += duration;

    // Serial.print("Note: ");
    // Serial.print(note);
    // Serial.print(", duration: ");
    // Serial.println(duration);

    if (noteIndexes[toneIndex] < size - 1) {
      noteIndexes[toneIndex]++;
    } else {
      noteIndexes[toneIndex] = 0;
    }
  }
}