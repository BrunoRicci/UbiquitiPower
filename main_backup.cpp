#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <UbiquitiPower.h>
// #include <WiFiClientSecure.h>




const char* ssid     = "DATALOGGER SERVER";
const char* password = "!UBA12345!";
const uint8_t fingerprint[20] = {0xF8,0xDD,0xE3,0xA6,0x8A,0x95,0x81,0x6C,0x06,0x6F,0x3E,0x7E,0x67,0x41,0x93,0x1C,0x52,0xEC,0xB7,0x9A};


void setup(){
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  

  WiFi.mode(WIFI_STA);
  // WiFi.config(IPAddress(192,168,0,44), IPAddress(192,168,0,1), IPAddress(255,255,255,0));

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//WiFiClient
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  // client.setTrustAnchors(&cert);
  // client.setInsecure();


  String HTTP_METHOD = "POST"; // or "POST"
  String PATH_NAME   = "/login.cgi?uri=%2Fstatus.cgi";
  // https://www.youtube.com/watch?v=ibfZKmth6jY




  //put no cookies.
  
    if(client.connect(HOST_NAME,HTTP_PORT)){
    //If connected...
    Serial.print("\n Connected to server.\n");
    // send HTTP request header

    String pd = "username=ubnt&password=Roberto2410";
    String request = "";
    String response = "";
    request += (String)"POST " + "/login.cgi?uri=%2Fstatus.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: text/html, text/plain, application/json" + (String)"\r\n";
    request += "Accept-Encoding: gzip, deflate, br" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    request += "User-Agent: ESP8266" + (String)"\r\n";
    request += "Content-Type: application/x-www-form-urlencoded" + (String)"\r\n";
    request += "Cookie: "+ (String)CLIENT_COOKIE +"\r\n";
    request += "Content-Length: " + (String)(pd.length()) + (String)"\r\n\r\n";   //1 empry line  before data body is compulsory.
    request += "username=ubnt&password=Roberto2410";  //Last line feed is put by println method.

    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client.println(request);

    delay(500);
    Serial.print("\nServer response:\n");
    response = "";
    while(client.available()){
      response += (client.readStringUntil('\r'));
    }
    Serial.println(response);

    
    request = "";
    request += (String)"GET" + " " + "/status.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: */*" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client.println(request);
    Serial.print("\nServer response:\n");
    delay(500);
    while(client.available()){
      Serial.println(client.readStringUntil('\r'));
    }

   
    if(!client.connected()){
      // if the server's disconnected, stop the client:
      Serial.println("client disconnected");
      client.stop();
    }

  }
  else{
    Serial.print("\nCould not connect.");
  }
}

void loop() {
  
  
}

