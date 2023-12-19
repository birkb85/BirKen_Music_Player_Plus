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
int songNumber = 0;
int buttonDelay = 0;

const int speaker1Pin = 8;  
const int speaker2Pin = 5;  
const int buttonPin = A0;  // the number of the pushbutton pin to change song

bool buttonPressed = false;

unsigned long time;
unsigned long timeOld;
unsigned long timeElapsed;

void setup(void) {
  //Serial.begin(2000000); //(9600);

  tones[0].begin(speaker1Pin);
  tones[1].begin(speaker2Pin);

  pinMode(buttonPin, INPUT);

  time = millis();
  timeOld = time;
  timeElapsed = 0;
}

void loop(void) {
  time = millis();
  timeElapsed = time - timeOld;
  timeOld = time;

  int buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && buttonPressed == false && buttonDelay <= 0) {
    changeTrack(songNumber+1);
    buttonPressed = true;
  } else if (buttonState == LOW && buttonPressed == true && buttonDelay <= 0) {
    buttonPressed = false;
    buttonDelay = 500;
  }

  if (buttonDelay > 0) buttonDelay -= timeElapsed;

  //Serial.println(timeElapsed);

  // Possibility of cutting sound after an amount of millis, so you dont go crazy :P
  // if (time > 1000) {
  //   tones[0].stop();
  //   tones[1].stop();
  //   return;
  // }

  // ---- PLAY TRACKS BELOW HERE ----

  switch(songNumber) {
    case 0:
      playTrack(0, Holding_fast_enkel_Notes1, Holding_fast_enkel_Durations1, Holding_fast_enkel_Size1);
      playTrack(1, Holding_fast_enkel_Notes2, Holding_fast_enkel_Durations2, Holding_fast_enkel_Size2);
      break;

    case 1:
      playTrack(0, Sang_57_enkel_Notes1, Sang_57_enkel_Durations1, Sang_57_enkel_Size1);
      playTrack(1, Sang_57_enkel_Notes2, Sang_57_enkel_Durations2, Sang_57_enkel_Size2);
      break;
      
    case 2:
      playTrack(0, thunderNotes, thunderDurations, thunderSize);
      noteIndexes[1] = -1;
      break;
      
    case 3:
      playTrack(0, song69Notes, song69Durations, song69Size);
      noteIndexes[1] = -1;
      break;
      
    case 4:
      playTrack(0, testSongNotes, testSongDurations, testSongSize);
      noteIndexes[1] = -1;
      break;

    default:
      changeTrack(0);
      break;
  }
  
  if (noteIndexes[0] == -1 && noteIndexes[1] == -1) {
    changeTrack(songNumber+1);
  }
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
      noteIndexes[toneIndex] = -1;
    }
  }
}

void changeTrack(int trackNumber) {
  songNumber = trackNumber;
  noteIndexes[0] = 0;
  noteIndexes[1] = 0;
  noteDurations[0] = 0;
  noteDurations[1] = 0;
}