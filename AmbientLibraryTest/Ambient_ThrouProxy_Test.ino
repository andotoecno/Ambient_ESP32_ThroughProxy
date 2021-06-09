#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Ambient_ESP32_ThroughProxy.h>

char ssid[] = "";
char password[] = "";
String ChannelID = "";
String WriteKey = "";
String ProxyHost = "proxy.asahikawa-nct.ac.jp";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to wifi");

  AmbientInitialize(ChannelID, WriteKey, ProxyHost);
}

void loop() {

  // put your main code here, to run repeatedly:
  
  Serial.print("ResponseCode: ");
  long StartTime = millis();
//  int Res = AmbientUpload(2, 20);
    int Res = AmbientUploadProxy(2, 20);
  long EndTime = millis();
  Serial.println(Res);

  Serial.print("ResTime: ");
  Serial.println(EndTime - StartTime);

  delay(5000);
}
