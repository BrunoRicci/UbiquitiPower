#include <ESP8266WiFi.h>
#include <UbiquitiPower.h>


// Fill ssid and password with your network credentials
const char* ssid = "DATALOGGER SERVER";
const char* password = "!UBA12345!";





void setup() {
  Serial.begin(115200);
  Serial.flush();

  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);

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

  Serial.printf("\n Signal level: %d", leerPotencia());

}


void loop() {

}


