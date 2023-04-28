#define BLYNK_PRINT Serial 
#define BLYNK_TEMPLATE_ID "TMPL33UAiZaTI"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "31QDzKMsGtznN9P5hozAzByTi97VfEw7"
#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#include <Time.h>
#include <TimeLib.h>
#include <BlynkSimpleStream.h>
char auth[] = "31QDzKMsGtznN9P5hozAzByTi97VfEw7";
BlynkTimer timer;
int comin=0;
int comax=0;
int iten=25;
int led=9;
int led2=5;
int led3=11;
int led4=6;
int ir1=2;
int ir2=8;
int ldr=A3;
int s;
int m;
int d=1,mo=2,y=2002;
int man;
void setup()
{

  DebugSerial.begin(9600);
  setTime(0,0,0,d,mo,y);  
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ldr,INPUT);
  digitalWrite(led,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  timer.setInterval(0L,smrt);
}
BLYNK_WRITE(V0){
  iten=param.asInt();
}
BLYNK_WRITE(V2){
  man=param.asInt();
}
   void smrt(){ 
   m=minute();
   s=second();
   char st[5]="DAY";
  
   while((m==3)&&(s==59))
   {
    setTime(0,0,0,d,mo,y);  
    int est=85*comin;
    int us=((25*comin)+(255*comax))/3;
    int cons=(us*100)/est;
    Blynk.virtualWrite(V1, cons);
      }
   if(m<1){
     Blynk.virtualWrite(V3,"DAY");
   }
   else{
     Blynk.virtualWrite(V3,"NIGHT");
   }
   Blynk.virtualWrite(V7, m);
   Blynk.virtualWrite(V8, s); 
  int v=analogRead(ldr);
  Blynk.virtualWrite(V6, v);
  int i=digitalRead(ir1);
  int j=digitalRead(ir2);
  if((v<100)&&(m>=1)&&(man==0))
  {
    comin++;
    analogWrite(led,iten);
    analogWrite(led2,iten);
    analogWrite(led3,iten);
    analogWrite(led4,iten);
    if(i==LOW ){
      digitalWrite(led,HIGH);
      digitalWrite(led2,HIGH);
      delay(500);
      comax++;
    }
    if(j==LOW ){
       digitalWrite(led3,HIGH);
       digitalWrite(led4,HIGH);
       delay(500);
       comax++;
    }
  }
   else{
      digitalWrite(led,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
    }

  if((m<1)&&(v<100))
    {
  Blynk.logEvent("system_alert") ;
    }
  if(man==1)
   {
      analogWrite(led,iten);
      analogWrite(led2,iten);
      analogWrite(led3,iten);
      analogWrite(led4,iten);
   }
   }
void loop()
{
  
  Blynk.run();
  timer.run();
}
