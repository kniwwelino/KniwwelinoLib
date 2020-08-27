/***************************************************

 KniwwelinoLIB

 Copyright (C) 2017 Luxembourg Institute of Science and Technology.
 This program is free software: you can redistribute it and/or modify
 it under the terms of the Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License.

 Derived from Adafruit_LED_Backpack_Library library
 Written by Limor Fried/Ladyada for Adafruit Industries.
 ****************************************************/
#ifndef Kniwwelino_h
#define Kniwwelino_h

#include "Arduino.h"

#include "KniwwelinoIcons.h"
#include "KniwwelinoTones.h"

#include <Ticker.h>
#include <Wire.h>
#include <EEPROM.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <TimeLib.h>
#include <Timezone.h>
#include <WiFiUdp.h>

#include <FS.h>
#include <MQTTClient.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

// comment to disable debugging output via serial port.
#define DEBUG

#define LIB_VERSION "kniwwelinoLIB_1.3.3"
#define FW_VERSION 	"kniwwelino_133"

#define DEF_TYPE    "Kniwwelino"
#define NAME_PREFIX "Kniwwelino"

#define TICK_FREQ 0.05

// definitions for the HT16K33 LED Matrix Driver
#define HT16K33_ADDRESS         0x70
#define HT16K33_BLINK_CMD       0x80
#define HT16K33_CMD_BRIGHTNESS  0xE0
#define HT16K33_DISP_REGISTER   0x00
#define HT16K33_KEYS_REGISTER   0x40
#define HT16K33_KEYINT_REGISTER 0x60
#define HT16K33_BLINK_DISPLAYON 0x01

#define MATRIX_STATIC 			0
#define MATRIX_BLINK_2HZ  		1
#define MATRIX_BLINK_1HZ  		2
#define MATRIX_BLINK_HALFHZ 	3
#define MATRIX_MIN_BRIGHTNESS 0
#define MATRIX_MAX_BRIGHTNESS 15
#define MATRIX_DEFAULT_BRIGHTNESS 10
#define MATRIX_SPEED			10
#define MATRIX_FOREVER			-1
#define MATRIX_SCROLL_DIV		3

#define EEPROM_ADR_UPDATE	510
#define EEPROM_ADR_NUM		511

#define RGB_PIN 			15
#define RGB_BRIGHTNESS		100
#define RGB_FOREVER			-1

#define RGB_ON				10
#define RGB_BLINK			5
#define RGB_FLASH			1
#define RGB_OFF				0
#define RGB_UNUSED			-1
#define RGB_SPARK			20
#define RGB_GLOW			21

#define PIN_ON				10
#define PIN_BLINK			5
#define PIN_FLASH			1
#define PIN_OFF				0
#define PIN_UNUSED			-1
#define PIN_INPUT			-2

#define RGB_COLOR_RED 		0xFF0000
#define RGB_COLOR_GREEN		0x00FF00
#define RGB_COLOR_BLUE 		0x0000FF
#define RGB_COLOR_ORANGE	0xC93B03
#define RGB_COLOR_CYAN		0x00FFFF

#define STATE_WIFI      0x000022
#define STATE_WIFIMGR   0x110022
#define STATE_ON      0x000100
#define STATE_OFF     0x000000
#define STATE_NONE    0x000000
#define STATE_SLEEPL  0x000100
#define STATE_SLEEPD  0x000000
#define STATE_ERR     0x220000
#define STATE_MQTT    0x010001
#define STATE_CONF    0x000101
#define STATE_UPDATE  RGB_COLOR_ORANGE

#define FILE_WIFI "/wifi.conf"
#define FILE_FORCED_WIFI "/forcwifi.conf"
#define FILE_CONF "/conf.json"

#define DEF_UPDATESERVER		"broker.kniwwelino.lu"
#define DEF_MQTTSERVER		 	"broker.kniwwelino.lu"
#define DEF_MQTTPORT			1883
#define DEF_MQTTUSER			"kniwwelino"
#define DEF_MQTTPW		        "esp8266"
#define DEF_MQTTPUBLICDELAY		300
#define DEF_MQTTBASETOPIC		"kniwwelino/"
#define DEF_FWUPDATEURL      	"/updateFW"
#define DEF_CONFUPDATEURL       "/updateConf"

#define MQTT_RGB 			  	"RGB"
#define MQTT_RGBCOLOR         	"RGB/COLOR"
#define MQTT_MATRIX			  	"MATRIX"
#define MQTT_MATRIXICON	      	"MATRIX/ICON"
#define MQTT_MATRIXTEXT	      	"MATRIX/TEXT"

#define SERIAL_RESET			"RESET"
#define SERIAL_WIFI_CLEAR	    "WIFI_CLEAR"
#define SERIAL_WIFI_ADD	      	"WIFI_ADD"
#define SERIAL_WIFI_LIST	      "WIFI_LIST"
#define SERIAL_UPDATING	      	"UPDATING"

#define NTP_SERVER			  	"lu.pool.ntp.org"
#define NTP_PORT			  	8888
#define NTP_TIMEZONE			1
#define NTP_PACKET_SIZE			48 // NTP time is in the first 48 bytes of message

static uint32_t _tick = 0;
static boolean mqttLogEnabled = false;

typedef void (*BGTask) ();
static BGTask bgTask;

class KniwwelinoLib: public Adafruit_GFX {
public:

	KniwwelinoLib();

	void begin();
	void begin(boolean enableWifi, boolean fast);
	void begin(boolean enableWifi, boolean fast, boolean mqttLog);
	void begin(const char nameStr[], boolean enableWifi, boolean fast, boolean mqttLog);
	void setSilent();

//==== Kniwwelino functions===================================================

		String getID();
		String getName();
		String getIP();
		String getMAC();
		void sleep(unsigned long millis);
		void loop();
		boolean isConnected();
		void bgI2CStop();
		void bgI2CStart();
		void setBGTask(BGTask task);

//====  logging  =============================================================

		void log(const String s);
		void logln(const String s);
		void log(const char s[]);
		void logln(const char s[]);

//====  IO Functions =========================================================

		void PINsetEffect(uint8_t pin, int effect);
		void PINclear(uint8_t pin);
		void PINenableButton(uint8_t pin);
		boolean PINbuttonClicked(uint8_t pin);
		boolean PINbuttonDown(uint8_t pin);

//==== RGB LED  functions ====================================================

		void RGBsetColor(String color);
		void RGBsetEffect(uint8_t effect, int count);
		void RGBsetColorEffect(String color, uint8_t effect, int count);
		void RGBsetColor(unsigned long color);
		void RGBsetColorEffect(unsigned long color, uint8_t effect, int count);
		void RGBsetColor(uint8_t red, uint8_t green, uint8_t blue);
		void RGBsetColorEffect(uint8_t red, uint8_t green, uint8_t blue,
				uint8_t effect, int count);
		void RGBsetColorEffect(String colorEffect);
		void RGBclear();
		void RGBsetBrightness(uint8_t b);
		uint32_t RGBgetColor();
		unsigned long RGBhex2int(String col);
		unsigned long RGBhue2int(uint8_t hue);
		String RGBcolor2Hex(unsigned long color);
		String RGBcolor2Hex(uint8_t r, uint8_t g, uint8_t b);
		String RGBhue2Hex(uint8_t hue);
		String RGB82Hex(uint8_t c);


//==== LED MATRIX functions ==================================================

		void MATRIXwrite(String text);
		void MATRIXwriteOnce(String text);
		void MATRIXwriteAndWait(String text);
		void MATRIXwrite(String text, int count, boolean wait);
		void MATRIXdrawIcon(String iconString);
		void MATRIXdrawIcon(uint32_t iconLong);
		void MATRIXsetPixel(uint8_t x, uint8_t y, boolean on);
		boolean MATRIXgetPixel(uint8_t x, uint8_t y);
		void MATRIXsetBrightness(uint8_t brightness);
		void MATRIXsetBlinkRate(uint8_t rate);
		void MATRIXsetScrollSpeed(uint8_t b);
		void MATRIXclear();
		void MATRIXshowID();
		boolean MATRIXtextDone();
		void MATRIXsetPixels(uint8_t p);
		void MATRIXsetStatus(uint8_t p);
		void MATRIXsetRotation(uint8_t rotation);

//==== Onboard Button functions ==============================================

		boolean BUTTONAclicked();
		boolean BUTTONBclicked();
		boolean BUTTONABclicked();
		boolean BUTTONAdown();
		boolean BUTTONBdown();

//==== IOT functions ==============================================

		boolean WIFIsetup(boolean wifiMgr, boolean fast, boolean reconnecting);

		MQTTClient mqtt;
		MQTTClient mqtt2;
		boolean MQTTUserSetup(const char broker[], int port, const char user[],	const char password[]);
		boolean MQTTconnect();
		boolean MQTTSystemConnect(boolean silent);
		boolean MQTTUserConnect(boolean silent);
		boolean MQTTpublish(const char topic[], String message);
		boolean MQTTpublish(String topic, String message);
		boolean MQTTsubscribe(const char topic[]);
		boolean MQTTsubscribe(String topic);
		boolean MQTTunsubscribe(const char topic[]);
		boolean MQTTsubscribepublic(const char topic[]);
		boolean MQTTsubscribepublic(String topic);
		boolean MQTTunsubscribepublic(const char topic[]);
		void MQTTsetGroup(String group);
		void MQTTonMessage(void (*)(String &topic, String &message));
		void MQTTconnectRGB();
		void MQTTconnectMATRIX();

		void PLATFORMprintConf();

//==== FS functions ==============================================

		String FILEread(String fileName);
		void FILEwrite(String fileName, String content);

//==== Serial functions ============================================

		void serialEvent();

//==== Tone functions ==============================================

		void playNote(uint8_t pin, unsigned int note, uint8_t noteDuration);
		void playTone(uint8_t pin, unsigned int note);
		void toneOff(uint8_t pin);

//==== Date Time functions ==============================================
		String getTime();

//==== Private functions =====================================================

	private:
		static void _baseTick();
		void _PINhandle();
		void _RGBblink();
		void drawPixel(int16_t x, int16_t y, uint16_t color); // Draw a specific pixel
		void _MATRIXupdate();
		void _Buttonsread();
		static void _MQTTMessageReceived(String &topic, String &payload);
		void _MQTTupdateStatus(boolean force);
		boolean PLATFORMcheckFWUpdate();
		boolean wpsConnect();

		void _initNTP();
	    time_t _getNtpTime();
		static KniwwelinoLib *getNTPTimeObject;
		static time_t _globalGetNTPTime() {
		                  return getNTPTimeObject->_getNtpTime();
		}

//==== Private Members =====================================================

		// general
		char fwVersion[20];
		char nodename[40];

		// always updateable - for now...
		boolean updateMode = true;
		// silent mode
		boolean silent = false;
		// background i2c operations active
		boolean bgI2C = true;

		// IO
		byte ioPinNumers[4] = { D0, D5, D6, D7 };
		int ioPinStatus[4] = { PIN_UNUSED, PIN_UNUSED, PIN_UNUSED, PIN_UNUSED };
		boolean ioPinclicked[4] = { false, false, false, false };
		int pinBlinkCount = 1;

		// MATRIX
		boolean redrawMatrix = true;
		String matrixText;
		int matrixCount = -1;
		int matrixPos = 0;
		int iconcount = 0;
		int iconnum = 0;
		uint8_t displaybuffer[8];
		uint8_t rotation = 0;
		boolean idShowing = false;
		uint8_t matrixScrollDiv = MATRIX_SCROLL_DIV;

		// RGB
		Adafruit_NeoPixel RGB;
		uint32_t rgbColor = 0;
		int rgbEffect = RGB_ON;
		int rgbEffectCount = -1;
		int rgbEffectBrightness = RGB_BRIGHTNESS;
		int rgbEffectModifier = 1;
		int rgbBlinkCount = 1;
		int rgbBrightness = RGB_BRIGHTNESS;

		// BUTTONS
		boolean buttonsPressed;
		boolean buttonA;
		boolean buttonB;
		boolean buttonAClicked;
		boolean buttonBClicked;
		boolean buttonABClicked;

		// TICKER
		Ticker baseTicker;

		// Wifi
		WiFiManager wifiManager;
		boolean wifiManagerRunning = false;
		boolean runWPS = false;
		boolean wifiEnabled = true;
		WiFiClient wifi;
		WiFiClient wifi2;
		// mqtt
		boolean mqttEnabled = false;

		char mqtt2User[20];
		char mqtt2PW[20];
		boolean mqtt2Enabled = false;

		int mqttPublishDelay = DEF_MQTTPUBLICDELAY;

		String mqttSubscriptions[10] = { "", "", "", "", "", "", "", "", "", "" };
		String mqttTopicUpdate = "/management/to/";
		String mqttTopicLogEnabled = "/management/to/";
		String mqttTopicStatus = "/management/from/";
		String mqttGroup = "";

		uint32_t mqttLastPublished = 0;
		boolean mqttRGB = false;
		boolean mqttMATRIX = false;

		// DateTime / NTP Stuff
		WiFiUDP ntpUdp;
		byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
		TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     //Central European Summer Time
		TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};       //Central European Standard Time
		Timezone timeZone = Timezone(CEST, CET);
	};

	extern KniwwelinoLib Kniwwelino;

#endif
