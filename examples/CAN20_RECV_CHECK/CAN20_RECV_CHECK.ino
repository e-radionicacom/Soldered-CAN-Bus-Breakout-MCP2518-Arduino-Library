/**
 **************************************************
 *
 * @file        CAN20_RECV_CHECK.ino
 * @brief       Example for receiving data through CAN
 *              communication using CAN 2.0 protocol
 *
 *              Product used is www.solde.red/333020
 * 
 *              Modified By Soldered
 * 
 * @authors     Longan Labs
 ***************************************************/

//Connecting diagram
//Breakout      Arduino
//|-------------|
//NCS-----------10
//SDI-----------MOSI(11 on Dasduino Core)
//SDO-----------MISO(12 on Dasduino Core)
//SCK-----------SCK(13 on Dasduino Core)
//GND-----------GND
//VCC-----------5V
//CLKO----------NOT CONNECTED
//INT-----------2
//INT0----------NOT CONNECTED
//INT1----------NOT CONNECTED

#include "CANBus-SOLDERED.h"

// Change pins accordingly
const int SPI_CS_PIN = 10;

CANBus CAN(SPI_CS_PIN); //Set CS pin

void setup()
{
    Serial.begin(115200); //Begin serial communication with PC

    while (CAN_OK != CAN.begin(CAN_125KBPS))  // Initialize CAN BUS with baud rate of 125 kbps
                                              // This should be in while loop because MCP2518 
                                              // needs some time to initialize and start function
                                              // properly.
    { 
        Serial.println("CAN init fail, retry..."); // Print information message
        delay(100);
    }
    Serial.println("CAN init ok!");
}


void loop()
{
    unsigned char len = 0; // Variable to store length of incoming data
    unsigned char buf[8];  // Buffer to store incoming data

    if (CAN_MSGAVAIL == CAN.checkReceive()) // Check if data coming
    {

        CAN.readMsgBuf(&len, buf);  // You should call readMsgBuff before getCanId
                                    // This function saves incoming data into buffer buf
                                    // It saves len nuber of bytes
        unsigned long id = CAN.getCanId(); // Get ID of transmitter
        Serial.print("Get Data From id: "); // Print ifnormatio message
        Serial.println(id); // Print ID of transmitter
        Serial.print("Len = ");
        Serial.println(len);// Print length of the data
        for (int i = 0; i < len; i++)
        {
            Serial.print(buf[i]); // Print array with received data
            Serial.print("\t"); // Print tabulator to format printing
        }
        Serial.println(); // Print new line at the end
    }
}

// END FILE
