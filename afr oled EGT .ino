#include <SpeedData.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#include "max6675.h" 
// Temperature Sensor1
int thermo1D0 = 4; // so
int thermo1CS = 5; 
int thermo1CLK = 6; // sck
float temp1 = 0; 
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1D0); 
 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//#define Uno   //Descomente essa linha caso utilizar um Arduino UNO
#define Mega   //Descomente essa linha caso utilizar um Arduino Mega

#ifdef Uno
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
#endif

#ifdef Mega
SpeedData SData(&Serial1);    // Serail 1 Mega
#endif

#ifdef Uno
SpeedData SData(&mySerial);   // SoftwareSerial Uno
#endif

void setup() {
  #ifdef Uno
  mySerial.begin(115200); //Serial dedicada ao acesso Can do Speeduino via Serial3
  Serial.begin(115200); 
  #endif

  #ifdef Mega
  Serial.begin(115200); 
  Serial1.begin(115200);  //Deletar essa linha caso esteja usando um ARDUINO UNO ou similar
  #endif
    Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
    display.clearDisplay();
  display.setTextColor(WHITE);
 
}

  
void loop() {

int RPM = SData.getRPM(500);
float AFR = SData.getActualAFR(100);
int MAP = SData.getMAP(200);  
float TAFR = SData.getTargetAFR(100);
  delay(250);


temp1 = thermocouple1.readCelsius(); 
  delay(250);

    //clear display
  display.clearDisplay();


 // display.setTextSize(1);
 // display.setCursor(0,0);
 // display.print("Temp1: ");
  display.setTextSize(3);
  display.setCursor(0,0);
  display.print(AFR);
//  display.setTextSize(1);
//  display.print("C");

 display.display();
  
}
