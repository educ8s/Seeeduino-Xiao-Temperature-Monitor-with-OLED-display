// In this sketch the temperature is displayed in degrees Celcius
//
//

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>  //https://github.com/adafruit/Adafruit-GFX-Library
#include <OneWire.h>
#include <DallasTemperature.h>   //https://github.com/milesburton/Arduino-Temperature-Control-Library
#define ONE_WIRE_BUS 10

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float previousTemp = -100.0;
float tempC = 0;

#define UI_BMPWIDTH  128

const unsigned char bitmap_ui[] PROGMEM = {
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // ################################################################################################################################
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // ################################################################################################################################
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x03, // ##.......................########...............................................##............................................##
  0xC0,0x00,0x00,0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x03, // ##.......................########...............................................##............................................##
  0xC0,0x00,0x00,0x0C,0x1E,0x7D,0xC7,0xC3,0xCF,0x3D,0xF6,0x6F,0x3C,0x00,0x00,0x03, // ##..........................##.....####..#####.###...#####....####..####..####.#####.##..##.####..####........................##
  0xC0,0x00,0x00,0x0C,0x3F,0x7F,0xE7,0xE7,0xEF,0x7E,0xC6,0x6F,0x7E,0x00,0x00,0x03, // ##..........................##....######.##########..######..######.####.######.##...##..##.####.######.......................##
  0xC0,0x00,0x00,0x0C,0x33,0x66,0x66,0x66,0x6C,0x06,0xC6,0x6C,0x66,0x00,0x00,0x03, // ##..........................##....##..##.##..##..##..##..##..##..##.##.......##.##...##..##.##...##..##.......................##
  0xC0,0x00,0x00,0x0C,0x3F,0x66,0x66,0x67,0xEC,0x3E,0xC6,0x6C,0x7E,0x00,0x00,0x03, // ##..........................##....######.##..##..##..##..##..######.##....#####.##...##..##.##...######.......................##
  0xC0,0x00,0x00,0x0C,0x30,0x66,0x66,0x66,0x0C,0x66,0xC6,0x6C,0x60,0x00,0x00,0x03, // ##..........................##....##.....##..##..##..##..##..##.....##...##..##.##...##..##.##...##...........................##
  0xC0,0x00,0x00,0x0C,0x31,0x66,0x66,0x66,0x2C,0xE6,0xC6,0x6C,0x62,0x00,0x00,0x03, // ##..........................##....##...#.##..##..##..##..##..##...#.##..###..##.##...##..##.##...##...#.......................##
  0xC0,0x00,0x00,0x0C,0x3F,0x66,0x67,0xE7,0xEC,0x7E,0xF7,0xEC,0x7E,0x00,0x00,0x03, // ##..........................##....######.##..##..##..######..######.##...######.####.######.##...######.......................##
  0xC0,0x00,0x00,0x0C,0x1E,0x66,0x67,0xC3,0xCC,0x7E,0x73,0xEC,0x3C,0x00,0x00,0x03, // ##..........................##.....####..##..##..##..#####....####..##...######..###..#####.##....####........................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##...................................................##.......................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##...................................................##.......................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##...................................................##.......................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03, // ##............................................................................................................................##
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // ################################################################################################################################
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF  // ################################################################################################################################
};

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up ...");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  sensors.begin();
  display.clearDisplay();
  display.drawBitmap(0,0,bitmap_ui, 128,64, SSD1306_WHITE);
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(80,30);             // Start at top-left corner
  display.println((char)247 );
  display.setCursor(95,30); 
  display.println("C");
  display.display();
}

void loop() {
    delay(1000);
    previousTemp = tempC;
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0); 
    Serial.println(tempC);
    if(previousTemp!=tempC)
    {
       deletePreviousTemperature();
       printTemperature();
    }
}

void printTemperature()
{
  display.setTextSize(2);             
  display.setCursor(25,30);  
  display.setTextColor(SSD1306_WHITE);         
  display.println(tempC,1);
  display.display();
}

void deletePreviousTemperature()
{
  display.setTextSize(2);             
  display.setCursor(25,30); 
  display.setTextColor(SSD1306_BLACK);                     
  display.println(previousTemp,1);
  display.display();
}
