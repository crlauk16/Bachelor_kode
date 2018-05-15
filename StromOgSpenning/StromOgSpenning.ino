#define numSamples 25          // number of analog samples to take per reading

int sumVolt = 0;                // sum of samples taken
unsigned char sampleCount = 0; // current sample number
float voltage = 0.0;            // calculated voltage
const int analogVolt = A2;

const int analogAmp = A0;
const int mVperAmp = 100;       // use 100 for 20A Module and 66 for 30A Module
int valueAmp= 0;
const int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
int sumAmp = 0;

float watt = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // take a number of analog samples and add them up
  while (sampleCount < numSamples) 
  {
    sumVolt += analogRead(analogVolt);
    sumAmp += analogRead(analogAmp);
    sampleCount++;
    delay(1000);
  }
  
  // Calculates mV meassures at A0
  valueAmp = ((float)sumAmp / (float)numSamples * 5000) / 1024.0;
  // Calculate the current
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  
  // Calculate the voltage
  // Use 5.0 for a 5.0V ADC reference voltage
  // 4.985V is the calibrated reference voltage
  voltage = ((float)sumVolt / (float)numSamples * 4.985) / 1024.0;
  // 10.09090909 is the calibrated voltage divide value

  watt = voltage * Amps;
  
  Serial.print("Current: ");
  Serial.print(Amps);
  Serial.print("A, Voltage: ");
  Serial.print(voltage * 10.09090909);
  Serial.print("V, Watt: ");
  Serial.print(watt);
  Serial.println("W");

  // Reset the values for the next sample
  sampleCount = 0;
  sumAmp = 0;
  sumVolt = 0;
}
