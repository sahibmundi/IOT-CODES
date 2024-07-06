#define TOUCHPAD 14

bool touchState = 0;
const int ledPin = 2;


void setup(){
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
}

void loop(){
  Serial.println(touchState);
  if(TouchSens()< 60)
    {
      touchState = !touchState;
      delay(350);
    }

   if (touchState)
   {
    digitalWrite(ledPin,HIGH);
   }
   else
   {
    digitalWrite(ledPin,LOW);
   }
}


int TouchSens()
{
  int sample = 0;
  for(int i=0;i<32;i++)
  sample += touchRead(TOUCHPAD);
  sample = sample / 32;
  
  return sample;
}
