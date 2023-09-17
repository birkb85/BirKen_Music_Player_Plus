#include <Tone.h>  // https://github.com/bhagman/Tone
#include "Notes.h"
#include "Thunder.h"
#include "Song69.h"
#include "Sang_57_enkel_lysere_bass.h"
#include "TestSong.h"

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

  // Bare lige hurtig mulighed for at afbryde den så man ikke bliver sindsyg. :P
  if (time > 60000) {
    tones[0].stop();
    tones[1].stop();
    return;
  }

  // playTrack(0, testSongNotes, testSongDurations, testSongSize, testSongDurationMultiplier);

  // playTrack(0, thunderNotes, thunderDurations, thunderSize, thunderDurationMultiplier);
  // playTrack(1, thunderNotes, thunderDurations, thunderSize, thunderDurationMultiplier);

  playTrack(0, Sang_57_enkel_lysere_bass_Notes1, Sang_57_enkel_lysere_bass_Durations1, Sang_57_enkel_lysere_bass_Size1);
  playTrack(1, Sang_57_enkel_lysere_bass_Notes2, Sang_57_enkel_lysere_bass_Durations2, Sang_57_enkel_lysere_bass_Size2);
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
      if (noteNext > 0 && noteNext == note && duration > 20) {
        tones[toneIndex].play(note, duration - 20);
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