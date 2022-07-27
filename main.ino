#include "DHT.h"
#include "virtuabotixRTC.h"
#include "LiquidCrystal_I2C.h"
#include "ThingSpeak.h"
#include "WiFiEsp.h"
#include "Arduino.h"

//Definisi PIN Sensor dan Modul
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(2,DHT11);
virtuabotixRTC Myrtc(3,4,5);

//Definisi SSID dan PASSWORD
char SSID[] = "RizalNet-Brobot";
char PASS[] = "blackbird16111992";

//Deklarasi Variabel
float kelembapan, suhu;
String waktu, tanggal;
int status = WL_IDLE_STATUS;

//Deklarasi Variabel ThinkSpeak
unsigned long CHANNEL_ID = 1809385;
const char * API_KEY = "42AKO31QXAUWA3TB";

void ConnectWIFI()
{
    
    if (WiFi.status() == WL_NO_SHIELD)
    {
        lcd.setCursor(0,0);
        lcd.print("Modul Tidak Terdeteksi");
        while (true);
    } 
    while (status != WL_CONNECTED)
    {
        lcd.clear();
        lcd.print("Modul Terdeteksi!");
        delay(1000);
        lcd.setCursor(0,1);
        lcd.print("Mengoneksikan ")+SSID;
        status = WiFi.begin(SSID,PASS);
        delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Terhubung !");
    lcd.setCursor(0,1);
    lcd.print(SSID);
}



void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
    WiFi.init(&Serial1);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Arduino IOT");
    delay(2000);
    lcd.clear();
    ConnectWIFI();
}

void loop()
{
    
}