#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t Task1;
TaskHandle_t Task2;

void TaskCore1(void *classparameter)
{ 
  while (1) {
    Serial.println("task 1");
    delay(500);
  }
}

void TaskCore2(void *classparameter)
{
  while (1) {
    Serial.println("task 2");
    delay(3000);
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println("task 1");
  xTaskCreatePinnedToCore(
    TaskCore1, /* Task function. */
    "Task1",   /* name of task. */
    2000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */
  delay(1500);
  xTaskCreatePinnedToCore(
    TaskCore2, /* Task function. */
    "Task1",   /* name of task. */
    2000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);
}

void loop() {
}
