LCD Screen = 16x2
DHT11 = Temperature & Humidity Sensor (Budget)
ARDUINO MEGA 2560 (Specifically: ELEGOO Developer Board)

PINOUT = As required, follow or edit code according to your own project needs.

A simple consol application to see how hard it would be to hook up an Arduino Developer board to my PC, turns out 
it's not all that involved at all really...

Format of the Output string loaded into the Arduino board is as follows:

//The Text below is the format of sent data in the arduino app.
/*
  Serial.print("Humidity: "); // print the humidity
  Serial.print(h);
  Serial.print("%\t ");
  Serial.print("Temperature: "); // print the temperature
  Serial.print(t); //Adjusted to match more acccurate temperature in the room
  Serial.println("*C ");
*/

As far as i know there is currently no way to create the degree symbol for the LCD screen so i used an asterix instead.

However on the Windows consol app to create this symbol type 'Alt 0176' in your code and it will display ° suitable for 
the Degrees sysmbol, however when trying this with my Win32 API ive noticed some formatting issues on displaying the 
data, though maybe unrelated - this is an entirely different project i will make avaliable at a later date - It is 
currently going well 01/04/2024.

I kept the whole project code including the Arduino project code really simple:

See file name 'ArdTempHum.cpp' please note this files content will need copying into your arduino IDE for uploading you 
can name that project anything you like.