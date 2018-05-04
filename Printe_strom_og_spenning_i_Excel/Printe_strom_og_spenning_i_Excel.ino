/*
 * I denne sketsjen logger vi spenning som er koblet på A2.
 * Så måler vi strøm fra 3 strømmålere som er koblet på A0.
 * Strømmåleren er i tillegg koblet på 5V og GND på Arduino
 * Denne sketsjen bruker PXL-DAQ for å logge verdiene i Excel
 */
 
#define NUM_SAMPLES 10

unsigned long int milli_time;    //Variable for å holde tiden
float voltage = 0.0;         //Variabel for å holde volten i A2
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
  Serial.begin(128000);         //Raskeste Baudraten som PXL-DAQ kan håndtere
  Serial.println("CLEARDATA");  //Kommando som brukes for å fjerne rader og kolonner i Excel
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt,Current");  
  //LABEL bestemmer hvor mange og hvilke data vi vil logge og lager oversikter i Excel
}
void loop() {
   //Loop som samler 64 målinger for å regne gjennomsnitt
  while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        RawValue = RawValue + analogRead(analogIn);
        sample_count++;
    }

  cVoltage = ((RawValue / NUM_SAMPLES) / 1024.0) * 5000; // Regner om til mV
  Amps = ((cVoltage - ACSoffset) / mVperAmp); //Regner om til Ampere  
  
  milli_time = millis();
  voltage = ((float)sum / (float)NUM_SAMPLES * 4.985) / 1024.0;
  Serial.print("DATA,TIME,");
  Serial.print(milli_time); 
  Serial.print(",");
  Serial.print(voltage * 10.09090909);  //Forholdet mellom Vin og Vout er 10.09090909
  Serial.print(",");
  Serial.println(Amps,3);

  //Resetter alle verdiene
  sample_count = 0;
  sum = 0;
  RawValue = 0;
  
  delay(25000);                 //Sampler hver 25 sekund
}
