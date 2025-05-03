// Pines de los sensores
int sensor1 = 8;
int sensor2 = 7;
int sensor3 = 6;
int sensor4 = 5;
int sensor5 = 4;
int sensor6 = 3;
int sensor7 = 2;

// Buzzer y botón
int buzzer = 9;
int buttonPin = 10;

// Estado del botón
int buttonState = HIGH;
int lastButtonState = HIGH;
int songIndex = -1;

// Reproducción
unsigned long lastNoteTime = 0;
int noteIndex = 0;
bool playingSong = false;

// Estructura para notas
struct Note {
  int frequency;
  int duration;
};

// Tres cancioncitas más largas y cool
Note song1[] = {
  {262, 250}, {262, 250}, {392, 250}, {392, 250}, {440, 250}, {440, 250}, {392, 500},
  {349, 250}, {349, 250}, {330, 250}, {330, 250}, {294, 250}, {294, 250}, {262, 500}
};
int song1Len = sizeof(song1) / sizeof(song1[0]);

Note song2[] = {
  {330, 200}, {294, 200}, {262, 200}, {294, 200}, {330, 200}, {330, 200}, {330, 400},
  {294, 200}, {294, 200}, {294, 400}, {330, 200}, {392, 200}, {392, 400}
};
int song2Len = sizeof(song2) / sizeof(song2[0]);

Note song3[] = {
  {262, 300}, {294, 300}, {330, 300}, {349, 300}, {392, 300}, {440, 300}, {494, 300},
  {523, 500}, {494, 300}, {440, 300}, {392, 300}, {349, 300}, {330, 300}, {294, 300}, {262, 500}
};
int song3Len = sizeof(song3) / sizeof(song3[0]);

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  pinMode(sensor7, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(sensor1) == HIGH) { tone(buzzer, 262); stopSong(); return; }
  if (digitalRead(sensor2) == HIGH) { tone(buzzer, 294); stopSong(); return; }
  if (digitalRead(sensor3) == HIGH) { tone(buzzer, 330); stopSong(); return; }
  if (digitalRead(sensor4) == HIGH) { tone(buzzer, 349); stopSong(); return; }
  if (digitalRead(sensor5) == HIGH) { tone(buzzer, 392); stopSong(); return; }
  if (digitalRead(sensor6) == HIGH) { tone(buzzer, 440); stopSong(); return; }
  if (digitalRead(sensor7) == HIGH) { tone(buzzer, 494); stopSong(); return; }

  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    songIndex = (songIndex + 1) % 3;
    noteIndex = 0;
    playingSong = true;
    lastNoteTime = millis();
    playCurrentNote();
  }
  lastButtonState = buttonState;

  if (playingSong && millis() - lastNoteTime >= getCurrentNote().duration) {
    noteIndex++;
    if (noteIndex < getCurrentSongLength()) {
      playCurrentNote();
      lastNoteTime = millis();
    } else {
      playingSong = false;
      noTone(buzzer);
    }
  }

  if (!playingSong) noTone(buzzer);
}

void stopSong() {
  playingSong = false;
  noteIndex = 0;
}

Note getCurrentNote() {
  if (songIndex == 0) return song1[noteIndex];
  if (songIndex == 1) return song2[noteIndex];
  return song3[noteIndex];
}

int getCurrentSongLength() {
  if (songIndex == 0) return song1Len;
  if (songIndex == 1) return song2Len;
  return song3Len;
}

void playCurrentNote() {
  Note current = getCurrentNote();
  tone(buzzer, current.frequency);
}
