// Im using the freeRtos library instead of Delay,mills() and micros
#include <Arduino_FreeRTOS.h>
//-------------------DEFINING  THE PINS-------------
const int lm35Pin = A0;//LM35 sensor pin
const int ledPin = 13;//LED pin

// temperature thresholds low=lTemp and high=hTemp
const int lTemp = 30;
const int hTemp = 31;

// -----------------------------------------it handles the task in the program  temperatureTaskHandle=tempTaH and ledTaskHandle=ledTaH
TaskHandle_t tempTaH;
TaskHandle_t ledTaH;

// -----------------------------Function prototypes of a program---------------------------
void tempTask(void *pvParameters);
void ledTask(void *pvParameters);

void setup() {
  Serial.begin(9600); // this is for  serial communication 

  //-------------------------------- Create tasks according to the requirement
  xTaskCreate(tempTask, "TempTask", 128, NULL, 1, &tempTaH);
  xTaskCreate(ledTask, "LEDTask", 128, NULL, 2, &ledTaH);
}

void loop() {  //==this is  Not used in FreeRTOS
}

void tempTask(void *pvParameters) {
  while (true) {
    
    int temp = analogRead(lm35Pin);// Read temperature from LM35 sensor
    temp = (temp * 5.0 * 100.0) / 1024.0;// we are Converting the  temperature into Celsius using the formula  
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 milliseconds // we are giving  Delay for 1 second
  }
}

void ledTask(void *pvParameters) {
  while (true) {
    digitalWrite(ledPin, !digitalRead(ledPin));

    
    int temp = analogRead(lm35Pin);// Delay based on temperature thresholds
    temp = (temp * 5.0 * 100.0) / 1024.0;
    if (temp < lTemp) {
      vTaskDelay(pdMS_TO_TICKS(250)); // Delay for 250 milliseconds
    } else if (temp > hTemp) {
      vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
    }
  }
}
