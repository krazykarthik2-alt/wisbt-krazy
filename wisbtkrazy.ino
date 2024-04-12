#define BLYNK_TEMPLATE_ID "TMPL3xvVcrLq7"
#define BLYNK_TEMPLATE_NAME "WISBTKRAZYTEMPLATE"
#define BLYNK_AUTH_TOKEN "7friNp0LoyTPRDpjE44LXKzquzWMkOJ1"

#include<WiFi.h>
#include<BlynkSimpleEsp32.h>
#define INDICATOR 2
#define relay0 27
#define relay1 14
#define relay2 12
#define relay3 13
#define relay4 19
#define BT_CNCT 15
#define BT_READ 4
BLYNK_CONNECTED() {

  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);


}
BLYNK_WRITE(V0) {
  digitalWrite(relay0, ! param.asInt());
} BLYNK_WRITE(V1) {
  digitalWrite(relay1, ! param.asInt());
} BLYNK_WRITE(V2) {
  digitalWrite(relay2, ! param.asInt());
} BLYNK_WRITE(V3) {
  digitalWrite(relay3, ! param.asInt());
} BLYNK_WRITE(V4) {
  digitalWrite(relay4, !param.asInt());
}


#define WIFI_SSID "sbsp"
#define WIFI_PASS "sbsp@123"



bool blynkOnline = false;
#define declare(a) pinMode(a,OUTPUT);digitalWrite(a,LOW);
#define turnON(a) digitalWrite(a,LOW)
#define turnOFF(a) digitalWrite(a,HIGH)
#define state(a) digitalRead(a)
void setup()
{
  Serial.begin(115200);
  declare(INDICATOR);
  declare(BT_CNCT);
  declare(BT_READ);
  digitalWrite(INDICATOR, HIGH);
  digitalWrite(BT_CNCT, LOW);
  digitalWrite(BT_READ, LOW);
  declare(relay0);
  declare(relay1);
  declare(relay2);
  declare(relay3);
  declare(relay4);
  delay(500);
  digitalWrite(INDICATOR, LOW);
  Serial.println("initialising Blynk");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  for (short i = 0; i < 20; i++) {
    delay(500); 
    if(WiFi.status() == WL_CONNECTED)break;
    Serial.print('.');
  }
  blynkOnline = (WiFi.status() == WL_CONNECTED);
  Serial.println(blynkOnline ?"online":"offline");
  if (blynkOnline)
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  delay(1000);
  digitalWrite(INDICATOR, HIGH);
  delay(300);
  digitalWrite(INDICATOR, LOW);
  Serial.println("Setup finish");
}
#define easyWrite(a,b,c) digitalWrite(a,!c);if(blynkOnline)Blynk.virtualWrite(b,c);
void loop()
{
  if (Serial.available()) {
    digitalWrite(BT_READ, HIGH);
    while (Serial.available()) {

      switch (Serial.read()) {

        case 'a': easyWrite(relay0, V0, LOW); break;
        case 'b': easyWrite(relay1, V1, LOW); break;
        case 'c': easyWrite(relay2, V2, LOW); break;
        case 'd': easyWrite(relay3, V3, LOW); break;
        case 'e': easyWrite(relay4, V4, LOW); break;


        case 'A': easyWrite(relay0, V0, HIGH); break;
        case 'B': easyWrite(relay1, V1, HIGH); break;
        case 'C': easyWrite(relay2, V2, HIGH); break;
        case 'D': easyWrite(relay3, V3, HIGH); break;
        case 'E': easyWrite(relay4, V4, HIGH); break;

      }

    }
    digitalWrite(BT_READ, LOW);
  } 
  digitalWrite(INDICATOR, blynkOnline && (WiFi.status() == WL_CONNECTED) );

  if (blynkOnline && WiFi.status() == WL_CONNECTED)
    Blynk.run() ;

}
