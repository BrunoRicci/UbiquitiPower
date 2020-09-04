#include <UbiquitiPower.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"


//HTTPS fingerprint
const uint8_t fingerprint[20] = {0xF8,0xDD,0xE3,0xA6,0x8A,0x95,0x81,0x6C,0x06,0x6F,0x3E,0x7E,0x67,0x41,0x93,0x1C,0x52,0xEC,0xB7,0x9A};


int leerPotencia(void){
  int signal_level = -10000;
  HTTPSRedirect* client = new HTTPSRedirect(HTTP_PORT);
  client->setCookie(CLIENT_COOKIE);
  // client->setPrintResponseBody(true);

  if(SECURE)
    client->setFingerprint(fingerprint);
  else
    client->setInsecure();
  
  if (client->connect(HOST_NAME, HTTP_PORT) == 1) {
    // Serial.print("\nConnected to server.");

    String body = (String)"username="+SERVER_USERNAME+"&password="+SERVER_PASS;
    client->setContentTypeHeader("application/x-www-form-urlencoded");
    client->POST("/login.cgi?uri=%2Fstatus.cgi", HOST_NAME, body, false );
    delay(2000);

    String response = client->getResponseBody();
    uint16 i = response.indexOf("\"wireless\":");
    response = "{"+response.substring(i , response.indexOf("}",response.indexOf("}",response.indexOf("}",i)+1)+1)+1) ; //-> Entire "wireless" array.

    i = response.indexOf("\"signal\":");
    response = response.substring( i+9, response.indexOf(",", i) );
    // Serial.print("\nResult:\n");
    // Serial.println(response);


    signal_level = response.toInt();  
    if(signal_level == 0) signal_level=-1000;
  }
  else
    Serial.println("Connection failed.");

  delete client;
  client = nullptr;

  return signal_level;
}