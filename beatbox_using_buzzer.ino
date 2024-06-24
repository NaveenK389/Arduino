// define the pins for the buzzer and the button
#define BUZZER_PIN 4
#define BUTTON_PIN 2

// define the frequency of each note
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// define the melody
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4,
  NOTE_F4, NOTE_E4, NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4,
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_B4,
  NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4
};

// define the duration of each note
int duration[] = {
  250, 250, 500, 500,
  500, 1000, 250, 250,
  500, 500, 500, 1000,
  250, 250, 500, 500,
  500, 1000, 250, 250,
  500, 500, 500, 1000,
  1000
};

// define the length of the melody
int melodyLength = sizeof(melody) / sizeof(int);

void setup() {
  // initialize the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
  // initialize the button pin as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // check if the button is pressed
  
    // play the melody
    for (int i = 0; i < melodyLength; i++) {
      tone(BUZZER_PIN, melody[i], duration[i]);
      delay(duration[i]);
    }
  
}
