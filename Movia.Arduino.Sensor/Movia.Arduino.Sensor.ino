        // ---- PREFACE ---- //

/* For heavens know what reason, the Arduino IDE support splitting a sketch into multiple files,
 * but each and every include and variable must be declared in the 'main' file. Because reasons.
 * .... Fucking Arduino.
 */

        
        // ---- INCLUDES ---- //

#include <WiFi101.h>

        // ---- DEFINES ---- //

          // -- HC-SR04 -- //

#define ECHOPIN_1       0
#define TRIGPIN_1       1
#define ECHOPIN_2       2
#define TRIGPIN_2       3

          // -- WIFI -- //

#define HOST "192.168.10.1"

        // ---- CONSTANTS ---- //

            // -- WIFI -- //
        
const char ssid[] = "Raspberry-Pi-Sensor";
const char password[] = "Pa$$w0rd";
const char server[] = "192.168.10.1";

const int http = 80;
const int timeout = 10000; // Milliseconds.

        // ---- VARIABLES ---- //

            // -- HC-SR04 -- //

int counter = 0; //counter for people inside the bus

long duration1, duration2; // variable for the duration of sound wave travel
int distance2, distance1; // variable for the distance measurement

int currentState = 0, previousState = 0, currentState2 = 0, previousState2 = 0;

            // -- WIFI -- //

int wifiStatus = WL_IDLE_STATUS;
IPAddress ip;

void setup() {
  
    // ---- SERIAL INITIALIZATION ---- //
    
    Serial.begin(9600);             // Initialize serial communications with the PC    

    // ---- HC-SR04 Initialization ---- //

    pinMode(TRIGPIN_1, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(ECHOPIN_1, INPUT); // Sets the echoPin as an INPUT 
  
    pinMode(TRIGPIN_2, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(ECHOPIN_2, INPUT); // Sets the echoPin as an INPUT

    // ---- WIFI INITIALIZATION ---- //

    wifiConnect();

}

void loop() {

  // ---- GET SENSOR READING ---- //
  
  getUltrasoundReading();           // Get ultrasound reading
}
