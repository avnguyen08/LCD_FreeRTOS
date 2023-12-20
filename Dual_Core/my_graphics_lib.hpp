/*
* Description: Header file that initializes LILYGO T-Display S3 LCD library
* 
* Author: Aaron Nguyen
* Date: 12/19/23
* 
*
* 
*/

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
// function imported from TFT_eSPI example library TFT_graphicstest_PDQ3
extern TFT_eSPI tft;     // Invoke custom library

static uint32_t micros_start();

uint32_t testRoundRects(); //produces varying sizes of red round rectangles
uint32_t testTriangles(); //produces varying sizes of blue triangles