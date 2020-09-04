#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <UbiquitiPower.h>


// Fill ssid and password with your network credentials
const char* ssid = "Fibertel WiFi866 2.4GHz";
const char* password = "01416592736";


void setup() {
  Serial.begin(115200);
  Serial.flush();

  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
leerPotencia();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // String pd = "username_login=admin&password_login=cisco&LanguageSelect=en&login=Log+In";

}


void loop() {

  if(WiFi.isConnected()){
    Serial.printf("\n Signal level: %d", leerPotencia());
  }
  else Serial.print("\nNot connected.");
  delay(500);
}


