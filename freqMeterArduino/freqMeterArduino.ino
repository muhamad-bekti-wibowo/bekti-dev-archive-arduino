/*  Frequency Counter With LCD Display - by arduinoaleman - May 2015


    For analog signals have a look at my preamplifier circuit (arduino forum / look for "frequency counter amplifier"

    Pin D5 of Arduino must be used for frequency input. The LCD uses pins 8 thru 13.

    Counter1 : 16 bits / used to count the frequency impules
    Counter2 : 8 bits / used to genarate a 1000ms or 100ms gate time for measurement

    I use "bitClear(TIMSK0,TOIEO)" instead of "TIMSK0 &=~(1<<TOIE0)"
    I use "bitSet(TIMSK0,TOIEO)"   instead of "TIMSK0 |=~(1<<TOIE0)"

    The serial monitor will also show some (unformatted) results.


*/


#include <avr/interrupt.h>
#include <LiquidCrystal.h>

bool leds;
volatile unsigned long frequency = 0;
volatile boolean       measurement_ready;
volatile unsigned char overflow_counter;     // number of overflows within gate_time
volatile unsigned int  time_so_far;              // number of ISR calls
volatile unsigned int  gate_time;

void measurement(int ms) {

  bitClear(TIMSK0, TOIE0);    // disable counter0 in order to disable millis() and delay()
  // this will prevent extra interrupts that disturb the measurement
  delayMicroseconds(66);      // wait for other interrupts to finish
  gate_time = ms;                // usually 1000 (ms)

  // setup of counter 1 which will be used for counting the signal impulses

  TCCR1A = 0;                // reset timer/counter1 control register A
  TCCR1B = 0;                // reset timer/counter1 control register B
  TCCR2A = 0;                // reset timer/counter1 control register A
  TCCR2B = 0;                // reset timer/counter2 control register A

  // setup of counter2 which will be used to create an interrupt every millisecond (used for gate time)

  TCCR2B |= B00000101;        // set prescale factor of counter2 to 128 (16MHz/128 = 125000Hz)
  // by setting CS22=1, CS21=0, CS20=1

  bitSet(TCCR2A, WGM21) ;     // set counter2 to CTC mode
  // WGM22=0, WGM21=1, WGM20=0
  OCR2A = 124;                      // CTC divider will divide 125Kz by 125

  measurement_ready = 0;      // reset
  time_so_far = 0;                  // reset
  bitSet(GTCCR, PSRASY);       // reset the prescaler
  TCNT1 = 0;                         // set frequency counter1 to 0
  TCNT2 = 0;                         // set gate time counter2 to 0

  bitSet(TIMSK2, OCIE2A);       // enable counter2 interrupts
  TCCR1B |= B00000111;        // set CS12, CS11 and CS10 to "1" which starts counting
  // on T1 pin (Arduino pin D5)
}


ISR(TIMER2_COMPA_vect) {

  if (time_so_far >= gate_time) {          // end of gate time, measurement is ready
    TCCR1B &= B11111000;                 // stop counter1 by setting CS12, CS11 and CS10 to "0"
    bitClear(TIMSK2, OCIE2A);             // disable counter2 interrupts
    bitSet(TIMSK0, TOIE0);      // enable Timer0 again // millis and delay
    measurement_ready = true;              // set global flag for end count period
    // calculate now frequeny value
    frequency = 0x10000 * overflow_counter; // mult #overflows by 65636 (0x10000)
    frequency += TCNT1;                 // add counter1 contents for final value
    overflow_counter = 0;                       // reset overflow counter
  }
  else {
    time_so_far++;                            // count number of interrupt events
    if bitRead(TIFR1, TOV1)  {              // if Timer/Counter 1 overflow flag = "1" then ...
      overflow_counter++;                  // increase number of counter1 overflows
      bitSet(TIFR1, TOV1);              // reset counter1 overflow flag
    }
  };
}


void setup() {
  pinMode(13, OUTPUT);
  pinMode(5, INPUT);

  Serial.begin(115200);
}


void loop() {
  leds = !leds;
  digitalWrite(13, leds);
  float period;
  float floatfrq;
  int range;
  long frq;

  measurement(1000);       // 1000ms standard gate time

  while (measurement_ready == false);
  frq = frequency;

  floatfrq = frq;                  // type conversion (required!!)
  period = (1 / floatfrq);            // period = 1/Frequenz -


  Serial.print("Frequency (Hz): ~");
  Serial.print(frq);
  Serial.print("~     Period (sec): ~");
  Serial.println(period, 7);

}
