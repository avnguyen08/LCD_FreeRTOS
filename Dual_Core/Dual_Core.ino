/*
* Description: Program that utilizes both cores on the LILYGO T-Display S3. 
* Core 0 prints to serial and core 1 displays shapes on the LCD screen
* 
* Author: Aaron Nguyen
* Date: 12/19/23
* 
* 
* 
*/

#include "my_graphics_lib.hpp"

// Core definitions (assuming you have dual-core ESP32)
static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;

// Settings
static const uint32_t task_0_delay = 500;  // Time (ms) Task 0 blocks itself

// Pins
static const int pin_1 = 38;  // LED pin

// Globals
static SemaphoreHandle_t bin_sem;

//*****************************************************************************
// Tasks

// Task in Core 0
void doTask0(void *parameters) {

  // Configure pin
  pinMode(pin_1, OUTPUT);

  // Do forever
  while (1) {

    // Notify other task
    // xSemaphoreGive(bin_sem);
    
  Serial.println("Hi I'm core 0 doing the important job of filler text!");
    // Yield processor for a while
    vTaskDelay(task_0_delay / portTICK_PERIOD_MS);
  }
}

// Task in Core 1
void doTask1(void *parameters) {

  // Do forever
  while (1) {

    // Wait for semaphore
    // xSemaphoreTake(bin_sem, portMAX_DELAY);

  testRoundRects();
  delay(1000);
  testTriangles();
  delay(1000);
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  Serial.begin(115200);

  Serial.println(F("LILYGO T-Display S3 Test"));

  tft.init();  // initialize LCD
  // Create binary semaphore before starting tasks
  bin_sem = xSemaphoreCreateBinary();
  
  // Start Task 0 (in Core 0)
  xTaskCreatePinnedToCore(doTask0,
                          "Task 0",
                          1024,
                          NULL,
                          1,
                          NULL,
                          pro_cpu);

  // Start Task 1 (in Core 1)
  xTaskCreatePinnedToCore(doTask1,
                          "Task 1",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  
}