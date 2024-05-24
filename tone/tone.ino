#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

//notes in the melody
int melody[] = {
  NOTE_C3, NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_E3, 0, NOTE_D3, NOTE_E3, NOTE_F3, 0, NOTE_E3,
  NOTE_D3, NOTE_C3, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_D3 
};

int melody2[] = {
  NOTE_C3, NOTE_E3, NOTE_C3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_G3, NOTE_A3, NOTE_E3,
  NOTE_B3, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_E3, NOTE_G3, NOTE_D3, NOTE_E3, NOTE_C3   
};

int noteDurations[] = {
  8, 8, 8, 4, 4, 8, 8, 8, 4, 8, 8, 8, 4, 
  8, 8, 4, 4, 8, 4, 4, 8, 4, 4
};

int noteDurations2[] = {
  4, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 
  8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 4
};

int melodyNumber = 0;
bool previousState = HIGH;
bool isPlaying = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(6, INPUT_PULLUP);
}

void loop() {
  bool presentState = digitalRead(6);

  if (presentState == LOW && previousState == HIGH) {
    isPlaying = !isPlaying;
    delay(50); // 簡單的防止按鈕抖動
  }
  previousState = presentState;

  if (isPlaying) {
    if (melodyNumber == 0) {
      for (int thisNote = 0; thisNote < 23; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); // stop the tone playing:

        // 檢查按鈕狀態以防止按鈕改變時卡在循環中
        presentState = digitalRead(6);
        if (presentState == LOW && previousState == HIGH) {
          isPlaying = !isPlaying;
          melodyNumber = 1;
          thisNote = 23;
        }
        previousState = presentState;
      }
    } else if (melodyNumber == 1) {
      for (int thisNote = 0; thisNote < 23; thisNote++) {
        int noteDuration = 1000 / noteDurations2[thisNote];
        tone(8, melody2[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8); // stop the tone playing:

        // 檢查按鈕狀態以防止按鈕改變時卡在循環中
        presentState = digitalRead(6);
        if (presentState == LOW && previousState == HIGH) {
          isPlaying = !isPlaying;
          melodyNumber = 0;
          thisNote = 23;
        }
        previousState = presentState;
      }
    }
  } else {
    noTone(8); // 確保在暫停時不播放音樂
  }
}
