/*
 * This sketch monitors the volt connected to A2
 * The sketch also measuring current through a current sensor connected to A0.
 * The current sensor is also connected to 5V and GND on the Arduino
 * This sketch uses PXL-DAQ for logging the values in Excel
 */
 
#define NUM_SAMPLES 64

unsigned long int milli_time;    // Variable used to hold the time
float voltage = 0.0;             // Variable used to hold the volt measured meassured in A2
int sum = 0;
unsigned char sample_count = 0;

// Variables used for the current sensor
const int analogIn = A0;
int mVperAmp = 100;
int RawValue = 0;
int ACSoffset = 2500;
double cVoltage = 0;
double Amps;

void setup() 
{
  Serial.begin(128000);         // Fastes Baud Rate the PXL-DAQ can handle.
  Serial.println("CLEARDATA");  // Commando used to clear rows and columns in Excel
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt,Current");  // Declares which variables we want to track in Excel and in what order
}

void loop() 
{
  // While loop uses 64 measurements collects 64 meassurement to calculate the average
  while (sample_count < NUM_SAMPLES) 
  {
    sum += analogRead(A2);
    RawValue = RawValue + analogRead(analogIn);
    sample_count++;
  }

  cVoltage = ((RawValue / NUM_SAMPLES) / 1024.0) * 5000; // Calculate the mV meassured
  Amps = ((cVoltage - ACSoffset) / mVperAmp);  // Calculate the Ampere 
  
  milli_time = millis();
  voltage = ((float)sum / (float)NUM_SAMPLES * 4.985) / 1024.0;
  Serial.print("DATA,TIME,");
  Serial.print(milli_time); 
  Serial.print(",");
  Serial.print(voltage * 10.09090909);  // Ratio between Vin and Vout is 10.09090909
  Serial.print(",");
  Serial.println(Amps,3);

  // Resets all the values
  sample_count = 0;
  sum = 0;
  RawValue = 0;
  
  delay(25000);                 // Sampling every 25 seconds
}
