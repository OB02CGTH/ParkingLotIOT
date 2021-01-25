#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <NewPing.h>

char auth[] = "qRVf-KlKTmbgVQh6jtfwTk0A2XRLes3W";
char ssid[] = "KORSAK";
char pass[] = "0994541990";

#define TRIGGER_PIN_1 23
#define ECHO_PIN_1 22
#define TRIGGER_PIN_2 19
#define ECHO_PIN_2 18
#define TRIGGER_PIN_3 4
#define ECHO_PIN_3 2
#define LED_PIN_1 21
#define LED_PIN_2 5 
#define LED_PIN_3 15
String SLOT1="???";
String SLOT2="???";
String SLOT3="???";

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  Blynk.notify("Connect!!");
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}

void loop(){
  Blynk.run();
  Sensor(TRIGGER_PIN_1,ECHO_PIN_1,LED_PIN_1)==1 ? SLOT1="ว่าง" : SLOT1="ไม่ว่าง"; Serial.print(SLOT1);
  Sensor(TRIGGER_PIN_2,ECHO_PIN_2,LED_PIN_2)==1 ? SLOT2="ว่าง" : SLOT2="ไม่ว่าง"; Serial.print(SLOT2);
  Sensor(TRIGGER_PIN_3,ECHO_PIN_3,LED_PIN_3)==1 ? SLOT3="ว่าง" : SLOT3="ไม่ว่าง"; Serial.print(SLOT3);
  Serial.println();
}

BLYNK_WRITE(V0){
  Sensor(TRIGGER_PIN_1,ECHO_PIN_1,LED_PIN_1)==1 ? SLOT1="ว่าง" : SLOT1="ไม่ว่าง"; Serial.print(SLOT1);
  Sensor(TRIGGER_PIN_2,ECHO_PIN_2,LED_PIN_2)==1 ? SLOT2="ว่าง" : SLOT2="ไม่ว่าง"; Serial.print(SLOT2);
  Sensor(TRIGGER_PIN_3,ECHO_PIN_3,LED_PIN_3)==1 ? SLOT3="ว่าง" : SLOT3="ไม่ว่าง"; Serial.print(SLOT3);
  Serial.println();
  Blynk.notify("ช่องที่ 1 : "+SLOT1+"\n"+"ช่องที่ 2 : "+SLOT2+"\n"+"ช่องที่ 3 : "+SLOT3);
}

int Sensor(int Trig,int Echo,int Led){
  NewPing sonar(Trig, Echo);
  delay(50);
  Serial.print("    Ping:");
  Serial.print(sonar.ping_cm());
  Serial.print("cm ");
  if(sonar.ping_cm() <= 10){
    digitalWrite(Led,LOW);
    return(0);
  }
  else{
    digitalWrite(Led,HIGH);
    return(1);
  }
}
