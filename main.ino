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
WiFiEspClient client;
float kelembapan, suhu;
String waktu, tanggal;
int status = WL_IDLE_STATUS;
unsigned long waktuTerakhirTulis = 0;
unsigned long waktuTerakhirBaca = 0;
const unsigned long intervalTulis = 20000;
const unsigned long intervalBaca = 5000;

//Deklarasi Variabel ThinkSpeak
unsigned long CHANNEL_ID = 1809385;
const char * WRITE_API_KEY = "42AKO31QXAUWA3TB";
const char * READ_API_KEY = "HK9CI6MW0NBNHJ96";
const int fieldSuhu = 1;
const int fieldKelembapan = 2; 

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
        lcd.print("Mengoneksikan...");
        status = WiFi.begin(SSID,PASS);
        delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Terhubung !");
    lcd.setCursor(0,1);
    lcd.print(SSID);
}

void uploadData()
{
    ThingSpeak.setField(fieldSuhu,suhu);
    ThingSpeak.setField(fieldKelembapan,kelembapan);
    int stats = ThingSpeak.writeFields(CHANNEL_ID,WRITE_API_KEY);
    Serial.println(suhu);
    Serial.println(kelembapan);
    Serial.println(stats);
    if(stats == '-303')
    {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.autoscroll();
        lcd.print("Menulis data Suhu dan Kelembapan!");
    }
}

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
    WiFi.init(&Serial1);
    dht.begin();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Arduino IOT");
    delay(2000);
    lcd.clear();
    ConnectWIFI();
    ThingSpeak.begin(client);
}

void loop()
{
    suhu = dht.readTemperature();
    kelembapan = dht.readHumidity();
    if (millis() - waktuTerakhirTulis > intervalTulis)
    {
        uploadData();
        waktuTerakhirTulis = millis();
    }
    
}