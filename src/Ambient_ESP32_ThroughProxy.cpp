#include "WiFiClient.h"
#include "Arduino.h"
#include "Ambient_ESP32_ThroughProxy.h"

String channelID = "";
String writeKey = "";
String proxyHost = "";

void AmbientInitialize(String ID, String key, String proxy) {
  channelID = ID;
  writeKey = key;
  proxyHost = proxy;
}

int AmbientUpload(int dNum, long dValue) {
  WiFiClient http;

  char URL[100] = {}, body[40] = {};
  String value = String(dValue), num = String(dNum), buf, buf2, res;

  sprintf(URL, "/api/v2/channels/%s/data", channelID.c_str());
  buf = URL;
  sprintf(body, "{\"writeKey\":\"%s\",\"d%s\":\"%s\"}", writeKey.c_str(), num.c_str(), value.c_str());
  buf2 = body;

  if (http.connect("ambidata.io", 80)) {
    http.println("POST " + buf + " HTTP/1.1");
    http.println("Host: ambidata.io");
    http.println("Content-Type: application/json");
    http.println("Content-Length: " + String(buf2.length()));
    http.println();
    http.print(buf2);

    unsigned int timeOut = millis();
    while (!http.available()) {
      if ((millis() - timeOut) > 5000)return 0;
    }
    while (http.available()) {
      res = http.readString();
    }
    int EndPosition = res.indexOf(" ", 10);
    String StatesCode = res.substring(9, EndPosition);
    //    Serial.println(res);
    return StatesCode.toInt();
  } else {
    //    Serial.println("Server connection failed");
    return -1;
  }
}

int AmbientUploadProxy(int dNum, long dValue) {
  WiFiClient http;

  char URL[100] = {}, body[40] = {};
  String value = String(dValue), num = String(dNum), buf, buf2, res;

  sprintf(URL, "http://ambidata.io/api/v2/channels/%s/data", channelID.c_str());
  buf = URL;
  sprintf(body, "{\"writeKey\":\"%s\",\"d%s\":\"%s\"}", writeKey.c_str(), num.c_str(), value.c_str());
  buf2 = body;

  if (http.connect(proxyHost.c_str(), 8080)) {
   http.println("POST " + buf + " HTTP/1.1");
   http.println("Host: ambidata.io");
   http.println("Content-Type: application/json");
   http.println("Content-Length: " + String(buf2.length()));
   http.println();
   http.print(buf2);

    unsigned int timeOut = millis();
    while (!http.available()) {
      if ((millis() - timeOut) > 5000)return 0;
    }
    while (http.available()) {
      res = http.readString();
    }
    int EndPosition = res.indexOf(" ", 10);
    String StatesCode = res.substring(9, EndPosition);
    //    Serial.println(res);
    return StatesCode.toInt();
  } else {
    //    Serial.println("Server connection failed");
    return -1;
  }
}

/*WiFiClientじゃなくてHTTPClientを使った方法*/
/*WiFiClientに不具合がありそうなら使った方がいいが、プロキシは通せない*/

//#include <HTTPClient.h>

//String AmbientUpload(String deviceID, long dValue) {
//  HTTPClient http;
//
//  char URL[100] = {}, body[40] = {};
//  String value = String(dValue), buf;
//
//  sprintf(URL, "http://api-Ambient.att.com/v2/devices/%s/streams/%s/value", channelID.c_str(), deviceID.c_str());
//  sprintf(body, "{ \"value\": \"%s\" }", value.c_str());
//  buf = body;
//
//  http.begin(URL);
//  http.addHeader("Host", "ambidata.io");
//  http.addHeader("X-Ambient-KEY", writeKey);
//  http.addHeader("Content-Type", "application/json");
//  http.addHeader("Content-Length", String(buf.length()));
//
//  int HttpResCode = http.PUT(body);
//
//  if (HttpResCode > 0) {
//    String response = http.getString();
//    //Serial.println(HttpResCode);
//    //Serial.println(response);
//  } else {
//   // Serial.print("Error on sending PUT Request: ");
//   // Serial.println(HttpResCode);
//return HttpResCode
//  }
//  http.end();
//
//}
