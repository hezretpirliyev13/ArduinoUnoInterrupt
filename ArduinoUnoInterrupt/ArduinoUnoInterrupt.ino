#define PD2_HIGH 0b00000100
#define PD2_LOW ~0b00000100
#define PD3_HIGH 0b00001000
#define PD3_LOW ~0b00001000
#define PD4_HIGH 0b00010000
#define PD4_LOW ~0b00010000
#define PD5_HIGH 0b00100000
#define PD5_LOW ~0b00100000
#include <string.h>

static unsigned long pulse_1 = 0, pulse_2 = 0, pulse_3 = 0, pulse_4 = 0;
char pulse[] = "pulse_";
void setup() {
  Serial.begin(115200);
  for (size_t i = 2; i < 6; i++) {
    pinMode(i, INPUT);
  }

  PCICR |= 1 << PCIE2;
  PCIFR |= 1 << PCIF2;
  PCMSK2 |= 1 << PCINT18;
  PCMSK2 |= 1 << PCINT19;
  PCMSK2 |= 1 << PCINT20;
  PCMSK2 |= 1 << PCINT21;
  delay(2000);
  strcpy(pulse, "pulse_1");
  Serial.println(pulse);
  delay(2000);

  // put your setup code here, to run once:
}

void loop() {
  Serial.println(pulse);
  delay(1000);
}
ISR(PCINT2_vect) {
  static unsigned long timer_1 = 0, timer_2 = 0, timer_3 = 0, timer_4 = 0;
  static bool state_1 = 0, state_2 = 0, state_3 = 0, state_4 = 0;
  if (PIND & PD2_HIGH and state_1 == 0) {
    timer_1 = micros();
    state_1 = 1;
  } else if (PIND & PD2_LOW and state_1 == 1) {
    pulse_1 = micros() - timer_1;
    state_1 = 0;
  }
  if (PIND & PD3_HIGH and state_2 == 0) {
    timer_2 = micros();
    state_2 = 1;
  } else if (PIND & PD3_LOW and state_2 == 1) {
    pulse_2 = micros() - timer_2;
    state_2 = 0;
  }
  if (PIND & PD4_HIGH and state_3 == 0) {
    timer_3 = micros();
    state_3 = 1;
  } else if (PIND & PD2_LOW and state_3 == 1) {
    pulse_3 = micros() - timer_3;
    state_3 = 0;
  }

  if (PIND & PD5_HIGH and state_4 == 0) {
    timer_4 = micros();
    state_4 = 1;
  } else if (PIND & PD2_LOW and state_4 == 1) {
    pulse_4 = micros() - timer_4;
    state_4 = 0;
  }
}