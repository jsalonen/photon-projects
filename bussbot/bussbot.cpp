#include <application.h>

#define LOUDNESSSENSOR_PIN A0
#define BUZZER_PIN D1

double loudness = 0.0;
double cumulatedLoudness = 0.0;
enum BussMode { MONITORING, CUMULATING, PURGING };
BussMode bussMode;

#define LOUDNESS_CUMULATION_MINIMUM 5000
#define LOUDNESS_AUTOPURGE_THRESHOLD 10000

void setup() {
  pinMode(LOUDNESSSENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  bussMode = MONITORING;
}

void loop() {
  loudness = analogRead(LOUDNESSSENSOR_PIN);

  switch(bussMode) {
    case MONITORING:
      if(loudness > 400.0f) {
        bussMode = CUMULATING;
      }
      delay(10);
      break;

    case CUMULATING:
      cumulatedLoudness += loudness;
      if(loudness < 100.0f || cumulateLoudness > LOUDNESS_AUTOPURGE_THRESHOLD) {
        if(cumulatedLoudness > LOUDNESS_CUMULATION_MINIMUM) {
          bussMode = PURGING;
        } else {
          cumulatedLoudness = 0.0f;
          bussMode = MONITORING;
        }
      }
      delay(10);
      break;

    case PURGING:
      cumulatedLoudness -= 400;
      if(cumulatedLoudness < 0) {
        cumulatedLoudness = 0;
        bussMode = MONITORING;
      }

      tone(BUZZER_PIN, 400, 10);
      delay(10);
      break;
  }
}
