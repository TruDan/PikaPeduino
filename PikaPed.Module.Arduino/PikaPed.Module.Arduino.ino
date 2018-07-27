// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
Name:       PikaPed_ArduinoUno.ino
Created:	09/06/2018 22:44:11
Author:     PIKACHU\trudan
*/

// Define User Types below here or use a .h file
//
#include "Configuration.h"

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

#include "Color.h"
#include <dht.h>
#include <Wire.h>
#include <RTClib.h>
#include <UTFT.h>


// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t PikaPed_S[];
extern uint8_t Sinclair_M[];

//UTFT myGLCD(Model,SDA,SCL,CS,RST,RS)
//QD220A is for QDtech 2.2inch SPI LCD Module,Driver IC:ILI9225
UTFT pikaLcd(QD220A, LCD_SDI_PIN, LCD_CLK_PIN, LCD_CS_PIN, LCD_RST_PIN, LCD_RS_PIN);

dht DHT;
RTC_DS1307 RTC;

// ---------------------------------------------------------------------

Color statusBar_bg(47, 47, 47);
Color statusbar_text(255, 255, 255);

Color text_color(0x00, 0xd9, 0xd8); // #00d9d8
Color error_color(0xff, 0x40, 0x4a); //ff404a

void setColor(Color color)
{
	pikaLcd.setColor(color.R, color.G, color.B);
}


// #region StatusBar

unsigned long lastTempStatusMillis;
unsigned long currentMillis;

void draw_statusbar_temp() {
	if (currentMillis - lastTempStatusMillis >= 5000)
	{
		lastTempStatusMillis = currentMillis;

		int chk = DHT.read11(DHT11_PIN);
		pikaLcd.setFont(Sinclair_M);

		if (DHT.temperature != DHTLIB_INVALID_VALUE)
		{
			setColor(statusbar_text);
			pikaLcd.print(String(int(DHT.temperature)) + "C", 1, 1, 0);
		}
		else
		{
			setColor(error_color);
			pikaLcd.print("--C", 1, 1, 0);
		}

		if (DHT.humidity != DHTLIB_INVALID_VALUE)
		{
			setColor(statusbar_text);
			pikaLcd.print(String(int(DHT.humidity)) + "%", 80, 1, 0);
		}
		else
		{
			setColor(error_color);
			pikaLcd.print("--%", 80, 1, 0);
		}
	}
}

void draw_statusbar_time()
{
	DateTime now = RTC.now();
	String nowStr = "";
	nowStr += String(int(now.hour()));
	nowStr += ":";
	nowStr += String(int(now.minute()));
	nowStr += ":";
	nowStr += String(int(now.second()));

	pikaLcd.setFont(Sinclair_M);
	pikaLcd.print(nowStr, 20, 20, 0);
}

void draw_statusbar() {

	pikaLcd.setBackColor(47, 47, 47);
	pikaLcd.setColor(255, 255, 255);

	draw_statusbar_temp();
	draw_statusbar_time();
}


void do_test() {
	float val = (analogRead(TEMP0_PIN)) * (5.0 / 1023.0);
	
	setColor(text_color);
	pikaLcd.setFont(SevenSegNumFont);

	pikaLcd.print(String(val), 20, 50);
}

// #endregion


// The setup() function runs once each time the micro-controller starts
void setup()
{
	pikaLcd.InitLCD(LANDSCAPE);
	pikaLcd.clrScr();
	pikaLcd.setFont(BigFont);
	pikaLcd.setBackColor(0, 0, 0);

	Wire.begin();
	RTC.begin();

	if(!RTC.isrunning())
	{
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}

	setColor(statusBar_bg);
	pikaLcd.fillRect(0, 0, 220, 16);

	draw_statusbar();

	pinMode(BTN0_PIN, INPUT);
	pinMode(BTN1_PIN, INPUT);
	pinMode(BTN2_PIN, INPUT);

	pinMode(TEMP0_PIN, INPUT);

	pinMode(BUZZER_PIN, OUTPUT);
}

// Add the main program code into the continuous loop() function
void loop()
{

	while (true)
	{
		currentMillis = millis();

		draw_statusbar();

		do_test();

		delay(20);
	}

}
