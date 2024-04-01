/*SEE README.txt
// Please note this is the source code for the Arduino board you may copy and paste this into your
// Arduino IDE and upload it to your board, see the code for PINOUT or adjust to your own project needs.
*/

#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN A0 // the pin where the DHT11 sensor is connected
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
#define DHTTYPE DHT11 // the type of the sensor
DHT dht(DHTPIN, DHTTYPE); // create a DHT object
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
    lcd.begin(16, 2);
    lcd.print("  Welcome!");
    delay(1500);
    Serial.begin(9600); // initialize the serial port
    dht.begin(); // initialize the sensor
}

void loop() {
    float h = dht.readHumidity(); // read the humidity
    float t = dht.readTemperature(); // read the temperature
    if (isnan(h) || isnan(t)) { // check if the readings are valid
        lcd.print("Fatal Error!");
        Serial.println("Failed to read from DHT sensor!");
    }
    else {
        lcd.setCursor(0, 0);//Set the lcd cursor to the first top left line
        Serial.print("Humidity: "); // print the humidity
        Serial.print(h);
        Serial.print("%\t ");

        Serial.print("Temperature: "); // print the temperature
        Serial.print(t); //Adjusted to match more acccurate temperature in the room
        Serial.println("*C ");


        lcd.print("Humi: ");
        lcd.print(h);
        lcd.print("% ");

        lcd.setCursor(0, 2);//Set lcd cursor to the new left line
        lcd.print("Temp: ");
        lcd.print(t - 2.5); //Adjusted the output to compensate for innacuracy adjust yours as required
        lcd.print("*C ");
        lcd.print(millis() / 1000);
    }
    delay(2000); // wait for 2 seconds (DHT11 is limited to 2 seconds)
}
