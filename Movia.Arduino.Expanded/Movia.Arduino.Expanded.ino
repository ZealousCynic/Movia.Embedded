        // ---- PREFACE ---- //

/* For heavens know what reason, the Arduino IDE support splitting a sketch into multiple files,
 * but each and every include and variable must be declared in the 'main' file. Because reasons.
 * .... Fucking Arduino.
 */

        
        // ---- INCLUDES ---- //
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi101.h>
#include <TinyGPS.h>

        // ---- DEFINES ---- //

           // -- MFRC -- //

#define RST_PIN         6           // Configurable -- Pins chosen arbitrarily
#define SS_PIN          7           // Based on MKR1000 layout

          // -- HC-SR04 -- //

#define ECHOPIN_1       0
#define TRIGPIN_1       1
#define ECHOPIN_2       2
#define TRIGPIN_2       3

          // -- WIFI -- //

#define HOST "192.168.4.1"

        // ---- CONSTANTS ---- //

            // -- MFRC  -- //
        
const byte sector = 1;
const byte blockaddress = 4;

            // -- WIFI -- //
        
const char ssid[] = "Raspberry-Pi-Sensor-Network";
const char password[] = "Pa$$w0rd";
const char server[] = "192.168.4.1";

const int http = 80;
const int timeout = 10000; // Milliseconds.

        // ---- VARIABLES ---- //

            // -- MFRC -- //

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;            // Presuppose identical keys
MFRC522::StatusCode status;
byte mf_buffer[18];
byte mf_buf_size = sizeof(mf_buffer);
char charbuf[30];


            // -- GPS -- //

float lat, lon;

            // -- HC-SR04 -- //

int counter = 0; //counter for people inside the bus

long duration1, duration2; // variable for the duration of sound wave travel
int distance2, distance1; // variable for the distance measurement

int currentState = 0, previousState = 0, currentState2 = 0, previousState2 = 0;

            // -- WIFI -- //

int wifiStatus = WL_IDLE_STATUS;
IPAddress ip;

        // -- GPS & SERIAL2 VARIABLES -- //

TinyGPS gps;

void setup() {
  
    // ---- SERIAL INITIALIZATION ---- //
    
    Serial.begin(9600);             // Initialize serial communications with the PC
    Serial1.begin(9600);            // Initialize serial communications with connected module on pins 13 and 14
    while (!Serial);                // Pause until a serial monitor is opened. PREVENTS FURTHER PROGRAM EXECUTION
    
    // ---- SPI & MFRC522 INITIALIZATION ---- //
    
    SPI.begin();                    // Initialize SPI bus
    mfrc522.PCD_Init();             // Initialize MFRC522 card

         for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;      // Initialize key to first default value: 0xFFFFFF
        Serial.print(key.keyByte[i], HEX);
    }
    Serial.println();

    // ---- HC-SR04 Initialization ---- //

    pinMode(TRIGPIN_1, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(ECHOPIN_1, INPUT); // Sets the echoPin as an INPUT 
  
    pinMode(TRIGPIN_2, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(ECHOPIN_2, INPUT); // Sets the echoPin as an INPUT

    // ---- WIFI INITIALIZATION ---- //

    wifiConnect();

}

void loop() {


  // ---- CHECK FOR RFID TAG ---- //
    if (mfrc522.PICC_IsNewCardPresent())
      read_rfid();                  // Call routine to handle it

  // ---- GET SENSOR READING ---- //
  
  getUltrasoundReading();           // Get ultrasound reading

  // ---- GET GPS READING ---- //

  getGPSReading();                  // Get GPS reading
}
