//A0接收光敏訊號大小 A1接收麥克風訊號
//遮光能夠亮LED(13接腳)並數五秒歸零
//彈手指 拍手能讓LED燈(13接腳)亮起來一秒
const byte LED = 13;
const byte CdS = A0;
const byte dataPin=2;
const byte latchPin=3;
const byte clockPin=4;
byte index=0;
int micPin=A1;
int micVal=0;
boolean toggle=false;
int ledPin=13;
const byte LEDs[10]=
{
  0b1111110,
  0b0110000,
  0b1101101,
  0b1111001,
  0b0110011,
  0b1011011,
  0b1011111,
  0b1110000,
  0b1111111,
  0b1110011
};

void setup() {
  pinMode(LED, OUTPUT) ;
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int val;
  micVal=analogRead(micPin);
  val = analogRead(A0) ;
  if(micVal>300)
  {
    Serial.println(micVal);  
    toggle=!toggle;
    if(toggle)
    {
      digitalWrite(ledPin,HIGH);  
      Serial.println(micVal); 
    }
    else
    {
    digitalWrite(ledPin,LOW);  
    }
    delay(500);
  }     
  if (val > 700) 
  {
    digitalWrite(13, HIGH) ;
    while(index<5)
    {
     digitalWrite(latchPin,LOW);
     shiftOut(dataPin,clockPin,LSBFIRST,LEDs[index]);
     digitalWrite(latchPin,HIGH);
     delay(1000);
     index++;
     if(index==5)
     {
        index=0; 
     digitalWrite(latchPin,LOW);
     shiftOut(dataPin,clockPin,LSBFIRST,LEDs[index]);
     digitalWrite(latchPin,HIGH);
      index=5;   
     }
   }
  } 
  else if (val < 600)
  {  // 設定低於600時，再關閉燈光。
    digitalWrite(13, LOW) ;
  }
  index=0; 
}
