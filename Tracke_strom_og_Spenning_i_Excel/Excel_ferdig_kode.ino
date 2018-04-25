#define NUM_SAMPLES 10

unsigned long int milli_time;    //variable to hold the time
float voltage = 0.0;         //variable to hold the voltage form A2
int sum = 0;
unsigned char sample_count = 0;

//Definisjoner til strommaleren
const int analogIn = A0;
int mVperAmp = 100;
int RawValue = 0;
int ACSoffset = 2500;
double cVoltage = 0;
double Amps;



void setup() {
  Serial.begin(128000);               //Fastest baudrate
  Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt,Current");  
                                      //LABEL command creates label for 
                                      // columns in the first row with bold font
}
void loop() {
  RawValue = analogRead(analogIn);
  cVoltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((cVoltage - ACSoffset) / mVperAmp);
  
  while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
    }
  milli_time = millis();
  voltage = ((float)sum / (float)NUM_SAMPLES * 4.985) / 1024.0;
  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print(voltage * 10.09090909);
  Serial.print(",");
  Serial.println(Amps,3);
  sample_count = 0;
  sum = 0;
  delay(1000);                    //Take samples every one second
}
