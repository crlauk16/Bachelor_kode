

void setup() 
{
  Serial.begin(115200);
  
  float verdi1;
  float verdi2;
  float verdi3;
  
  verdi1 = 5.12;
  verdi2 = 7.98;
  verdi3 = 2.62;

  float arr[3] = {
    verdi1, verdi2, verdi3
  };

for(int i = 0; i < 3; i++)
  {
    Serial.print(arr[i]);
  }
}

void loop() 
{
  
}
