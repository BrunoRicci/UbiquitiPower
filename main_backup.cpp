#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
// #include <WiFiClientSecure.h>


// #define HTTP_PORT     80
// #define HTTP_METHOD   "GET"
// #define HOST_NAME[]   "example.phpoc.com"  // hostname of web server:
// #define PATH_NAME     ""


// const char* ssid     = "Fibertel WiFi866 2.4GHz";
// const char* password = "01416592736";
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

/*   // String url = "https://192.168.1.20/login.cgi";
  // String url = "https://192.168.1.20/login.cgi?uri=%2Fstatus.cgi";
  String url = "http://192.168.1.20/login.cgi?uri=%2Fstatus.cgi";
  
  HTTPClient http;
  http.writeToStream(&Serial);
  http.setFollowRedirects(true);
  char fingerprint[] = {0xF8,0xDD,0xE3,0xA6,0x8A,0x95,0x81,0x6C,0x06,0x6F,0x3E,0x7E,0x67,0x41,0x93,0x1C,0x52,0xEC,0xB7,0x9A};
  if (http.begin("https://192.168.1.20", 80, "/login.cgi?uri=%2Fstatus.cgi",fingerprint)){
    Serial.print("\nConnected to server.");
    Serial.print("\n");

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Accept", "application/json");
    http.addHeader("Connection", "keep-alive");
    Serial.printf("\nResponse code: %d",http.POST((String)"username=ubnt&password=Roberto2410"));
    Serial.printf("\nResponse code: %d",http.GET());
    Serial.print("\nLocation:");
    Serial.println(http.getLocation());
    Serial.print("\n");
    
    delay(1000);
    Serial.println(http.getString());
  }
  else{
    Serial.print("\nCouldn't connect");
  }

  http.end();
   */

  // HTTPClient http;  
  // WiFiClientSecure client;
  // client.setFingerprint(fingerprint);
  // client.setInsecure();

  // http.begin(client, url);
  
  // http.setFollowRedirects(false);
  // http.setRedirectLimit(3);

//WiFiClient
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  // client.setTrustAnchors(&cert);
  // client.setInsecure();

  int    HTTP_PORT   = 443;
  String HTTP_METHOD = "POST"; // or "POST"
  const char*   HOST_NAME = "192.168.1.20"; // hostname of web server:
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
    request += HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: text/html, text/plain, application/json" + (String)"\r\n";
    request += "Accept-Encoding: gzip, deflate, br" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    request += "User-Agent: ESP8266" + (String)"\r\n";
    request += "Content-Type: application/x-www-form-urlencoded" + (String)"\r\n";
    request += "Content-Length: " + (String)(pd.length()) + (String)"\r\n\r\n";   //1 empry line  before data body is compulsory.
    request += "username=ubnt&password=Roberto2410";  //Last line feed is put by println method.

    //Always returning 302 because server redirects to https version.
    // see: https://www.youtube.com/watch?v=Wm1xKj4bKsY
    //  https://github.com/electronicsguy/ESP8266/tree/master/HTTPSRedirect#sec-ii-httpsredirect-library-api

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

    // Serial.print("\nLocation:");
    // int i = response.indexOf("Location: ");
    // Serial.printf(" index = %d \nvalue: ", i);
    // Serial.println(response.substring(i));
    // char buf[50];
    // response.toCharArray(buf, sizeof(buf));
    // __getline(buf,);
    
    //trim Location value.
    
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

    request = "";
    request += (String)"GET" + " " + "/cookiechecker?uri=/status.cgi" + " HTTP/1.1\r\n";
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

    request = "";
    request += (String)"GET" + " " + "/nocookies.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: */*" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client.println(request);
    Serial.print("\nServer response:\n");
    delay(1000);
    while(client.available()){
      Serial.println(client.readStringUntil('\r'));
    }

    request = "";
    request += (String)"GET" + " " + "/cookiechecker?uri=/nocookies.cgi" + " HTTP/1.1\r\n";
    request += "Host: "+ (String)HOST_NAME + "\r\n";
    request += "Accept: */*" + (String)"\r\n";
    request += "Connection: keep-alive" + (String)"\r\n";
    Serial.print("\nHTTP request:\n\n");
    Serial.println(request);
    client.println(request);
    Serial.print("\nServer response:\n");
    delay(1000);
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




  /* http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,;q=0.8");
  http.addHeader("Connection", "keep-alive");

  Serial.printf("\n Response code: %d \n",http.sendRequest("POST","username=ubnt&password=Roberto2410"));
  Serial.printf("\n Payload size: %d\n",http.getSize());
  Serial.println(http.getString());
  http.setURL(http.getLocation());
  http.GET();
  Serial.println(http.getString());
  Serial.print("\nReditection location: [ ");
  Serial.println(http.getLocation()+" ]");
  // http.end();
  http.setURL(http.getLocation());
  http.GET();
  Serial.println(http.getString());
  Serial.print("\nReditection location: [ ");
  Serial.println(http.getLocation()+" ]");

  http.setURL(http.getLocation());
  http.GET();
  Serial.println(http.getString());
  Serial.print("\nReditection location: [ ");
  Serial.println(http.getLocation()+" ]");

  //////////////////////////////////////////////  Redirection
  String redir;
  redir = "https://192.168.1.20"+http.getLocation();
  // redir = "https://192.168.1.20"+(String)"/status.cgi";
  
  Serial.print("\nHeaders:\n");
  for (int i = 0; i < http.headers(); i++)
  {
    Serial.printf("%d: ",i);
    Serial.println(http.headerName(i));
  }
  http.end();
  

  Serial.print("Redirecting to: ");
  Serial.println(redir);
  // http.begin(client, redir);
  http.setURL(redir);      //-> Test
  Serial.printf("\n http connected: %d", http.connected());

  http.addHeader("Accept", "application/json");
  http.addHeader("Accept", "application/json");
  // https://192.168.1.20/status.cgi
  http.addHeader("Connection", "keep-alive");  
  ////////////////////////////////////////////////
  Serial.println();
  Serial.printf("\n Redirection response code: %d \n",http.sendRequest("GET"));
  Serial.print("\nReditection location: [ ");
  Serial.println(http.getLocation()+" ]");
  Serial.println(http.getString());

 */




  /* Serial.print("\n\n\nStarting HTTP...");

  http.begin("https://192.168.1.20/login.cgi");
  http.setFollowRedirects(true);
  http.addHeader("Content-Type", "text/html");
  Serial.print("\nHeaders:");
  Serial.println(http.header(1));
  // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  // http.sendRequest("GET","");

  delay(3000);
  Serial.println(http.GET());   //Print HTTP return code
  String httpcontent = http.getString();

  int len = httpcontent.length();
  Serial.printf("\nPage size: %d",len);   
  Serial.println(httpcontent);
  
  String redirect = http.getLocation();
  Serial.printf("\nRedirect: %d",len);   
  
  http.end();  //Close connection

  Serial.print("\nPOST REQUEST");   
  http.begin("https://192.168.1.20/login.cgi");
  http.setFollowRedirects(true);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postdata = "username=ubnt&password=Roberto2410";
  Serial.println(http.POST(postdata));
  delay(2000);
  httpcontent = http.getString();
  Serial.println(httpcontent); *

  http.end();
  Serial.print("\n------HTTP END."); */
}

void loop() {
  
  
}