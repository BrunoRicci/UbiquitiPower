#include <UbiquitiPower.h>
#include <ESP8266WiFi.h>


//HTTPS fingerprint
const char fingerprint[20] = {0xF8,0xDD,0xE3,0xA6,0x8A,0x95,0x81,0x6C,0x06,0x6F,0x3E,0x7E,0x67,0x41,0x93,0x1C,0x52,0xEC,0xB7,0x9A};


int leerPotencia(void){

  int signal_level = -10000;
  String response = "";
  WiFiClientSecure *client = new WiFiClientSecure;
  if(SECURE)
    client->setFingerprint(fingerprint);
  else
    client->setInsecure();


  //put no cookies.
    // if(client->connect(HOST_NAME,HTTP_PORT)){
    if(client->connect(HOST_NAME,HTTP_PORT)){
    //If connected...
    Serial.print("\n Connected to server.\n");
    // send HTTP request header

    String pd = (String)"username="+SERVER_USERNAME+"&password="+SERVER_PASS;
    String request = "";
    request += (String)"POST " + "/login.cgi?uri=%2Fstatus.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: text/html, text/plain, application/json" + (String)"\r\n";
    request += "Accept-Encoding: gzip, deflate, br" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    request += "User-Agent: ESP8266" + (String)"\r\n";
    request += "Content-Type: application/x-www-form-urlencoded" + (String)"\r\n";
    request += "Cookie: "+ (String)CLIENT_COOKIE +"\r\n";
    request += "Content-Length: " + (String)(pd.length()) + (String)"\r\n\r\n";   //1 empry line  before data body is compulsory.
    request += pd;
    request += (String)"\r\n\r\n";  //Last line feed is put by println method.

    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client->println(request);

    delay(2000);
    Serial.print("\nServer response:\n");
    response = "";
    while(client->available()){
      response += (client->readStringUntil('\r'));
    }
    Serial.println(response);

    
    request = "";
    request += (String)"GET" + " " + "/status.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: */*" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    request += "Cookie: "+ (String)CLIENT_COOKIE +"\r\n";
    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client->println(request);
    Serial.print("\nServer response:\n");
    delay(500);
    while(client->available()){
      Serial.println(client->readStringUntil('\r'));
    }

   
    if(!client->connected()){
      // if the server's disconnected, stop the client:
      Serial.println("client disconnected");
      client->stop();
    }

 





    delay(1000);

    // response = client->getResponseBody();
    // uint16 i = response.indexOf("\"wireless\":");
    // response = "{"+response.substring(i , response.indexOf("}",response.indexOf("}",response.indexOf("}",i)+1)+1)+1) ; //-> Entire "wireless" array.

    // i = response.indexOf("\"signal\":");
    // response = response.substring( i+9, response.indexOf(",", i) );
    // // Serial.print("\nResult:\n");
    // // Serial.println(response);


    // signal_level = response.toInt();  
    // if(signal_level == 0) signal_level=-1000;
  }
  else
    Serial.println("Connection failed.");

  delete client;
  client = nullptr;

  return signal_level;
}