#include <stdio.h>
#include <KXG03.h>
#include <heartRate.h>
#include <MAX30105.h>
#include <spo2_algorithm.h>

/*
  MAX30105 Breakout: Output all the raw Red/IR/Green readings
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  Outputs all Red/IR/Green values.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;
KXG03 kxg03;

#define debug Serial //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21

void setup()
{
  debug.begin(115200);
  debug.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    debug.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

   byte rc;
  
  Wire.begin();
  
  rc = kxg03.init(KXG03_DEVICE_ADDRESS_4E);
}

void loop()
{
  debug.print(" R[");
  debug.print(particleSensor.getRed());
  debug.print("] IR[");
  debug.print(particleSensor.getIR());
  debug.print("] G[");
  debug.print(particleSensor.getGreen());
  debug.print("]");

  debug.println();

  byte rc;
  float val[6];

  rc = kxg03.get_val(val);
  if (rc == 0) {
    debug.print("X-Gyro: ");
    debug.println(val[0], 2);
    debug.print("Y-Gyro: ");
    debug.println(val[1], 2);
    debug.print("Z-Gyro: ");
    debug.println(val[2], 2);
    debug.print("X-Accelerator: ");
    debug.println(val[3], 2);
    debug.print("Y-Accelerator: ");
    debug.println(val[4], 2);
    debug.print("Z-Accelerator: ");
    debug.println(val[5], 2);
    debug.println(" ");
  }
  delay(100);
}
