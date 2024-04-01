///BACK UP BEFORE CHANGING!!!!!
//
//
///


#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <format>

using namespace std;

HWND Msg_hWnd; //Just for message boxes
//#define COM_PORT "COM3" // the name of the serial port
const char* COM_PORT = "COM3"; //Serial port name/number

#define BAUD_RATE 9600 // the baud rate of the serial port
#define DATA_BITS 8 // the number of data bits
#define STOP_BITS ONESTOPBIT // the number of stop bits
#define PARITY NOPARITY // the parity mode

HANDLE hSerial; // the handle of the serial port
DCB dcbSerialParams = { }; // the serial port parameters
DWORD dwBytesRead = 0; // the number of bytes read from the serial port
char szBuffer[50]; // the buffer to store the data from the serial port

// a function to open the serial port
bool openSerialPort() {
    // open the serial port
    hSerial = CreateFileA(COM_PORT, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening serial port %s\n", COM_PORT);
        MessageBox(Msg_hWnd, L"Error: have you connected the sensor device? \nPlease check the connections then restart the application.",
            L"Connection failed!", NULL);
        return false;
    }
    // get the current serial port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting serial port state\n");
        return false;
    }
    // set the serial port parameters
    dcbSerialParams.BaudRate = BAUD_RATE;
    dcbSerialParams.ByteSize = DATA_BITS;
    dcbSerialParams.StopBits = STOP_BITS;
    dcbSerialParams.Parity = PARITY;

    std::cout << "Welcome to my simple application\n\n";
    std::cout << "Setting the serial port parameters...\n";
    string str_serial_param = format("BAUD_RATE: {}\nDATA_BITS: {}\nSTOP_BITS : {}\nPARITY : {}\n",
        BAUD_RATE, DATA_BITS, STOP_BITS, PARITY);
    
    std::cout << "\n" << str_serial_param << "\n\n";

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting serial port state\n");
        return false;
    }
    // set the serial port timeouts
    COMMTIMEOUTS timeouts = { };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting serial port timeouts\n");
        return false;
    }
    return true;
}

// a function to close the serial port
void closeSerialPort() {
    CloseHandle(hSerial);
}


//The Text below is the format of sent data in the arduino app.
/*

  Serial.print("Humidity: "); // print the humidity
  Serial.print(h);
  Serial.print("%\t ");
  Serial.print("Temperature: "); // print the temperature
  Serial.print(t); //Adjusted to match more acccurate temperature in the room
  Serial.println("*C ");

*/
// a function to read data from the serial port
bool readSerialPort() {
    // read data from the serial port
    if (!ReadFile(hSerial, szBuffer, sizeof(szBuffer), &dwBytesRead, NULL)) {
        MessageBox(Msg_hWnd, L"Fatal Error! Please check that the device connection \nthen restart the application.",
            L"FATAL ERROR!", MB_ICONERROR);
        printf("Error reading from serial port\n");
        return false;
    }
    
    Sleep(2000);// wait 2 seconds 
    float temperature, humidity;
    
        sscanf_s(szBuffer, "Humidity:%f%% \tTemperature:%f°C ", &humidity, &temperature);
        /*MessageBox(Msg_hWnd, L"Data not clear? \nPlease consult the software developer for advice.\n"
                                "Quote Line : 110 Main.cpp\nbool readSerialPort()",
                                    L"DATA READ ERROR!", MB_ICONERROR);
                                    */
        ///std::cerr << "Error parsing data from serial port " << COM_PORT << "\n\nExiting Program...\n\n";
        
        //std::cout << "Retrying...\n";
        //sscanf_s(szBuffer, "Humidity:%f%% \tTemperature:%f°C ", &humidity, &temperature);
        //return true; //exit program
        
   

    // print the data to the console
    //this may handle the unhandled exception now.
    if (dwBytesRead < sizeof(szBuffer)) {

        szBuffer[dwBytesRead] = '\0'; //Check for the end of memory?
        //printf("%s", szBuffer); // display the full string of data in one hit.

        //attempting to display the szBuffer in seperate details this is so i can 
        //later display in a GUI app list with columns
        printf("Temperature: %.1f°C\n", temperature);//'Alt 0176' for the degree symbol
        printf("Humidity: %.1f%%\n", humidity);
    }
    else
    {
        szBuffer[sizeof(szBuffer) - 1] = '\0'; 
    }
    return true; // Close serial port is handled in the int main() function
}

// a function to write data to the serial port - not needed(Not yet!)
bool writeSerialPort(const char* data) {
    DWORD dwBytesWritten = 0; // the number of bytes written to the serial port
    // write data to the serial port

    printf(data);
    if (!WriteFile(hSerial, data, strlen(data), &dwBytesWritten, NULL)) {

        printf("Error writing to serial port\n");
        return false;
    }
    return true;
}

int main() {
    // open the serial port
    if (!openSerialPort()) {
        // Flush serial buffer
        //PurgeComm(hSerial, PURGE_RXCLEAR);
        //Delay before reading data
        //Sleep(1000);
        return 1;
    }
    else { printf("Connected...\n\n"); }
    
    // read data from the serial port in a loop
    while (true) {
        
        if (!readSerialPort()) {
            break;
        }
    }
    // close the serial port
    closeSerialPort();
    return 0;
}
