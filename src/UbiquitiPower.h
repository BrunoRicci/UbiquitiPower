#ifndef _UBIQUITIPOWER_H
#define _UBIQUITIPOWER_H


#define SERVER_USERNAME "ubnt"              //Datos de login a la antena
#define SERVER_PASS     "Roberto2410"       


#define HOST_NAME "192.168.1.20"            //IP 
#define HTTP_PORT  443                      //Puerto https por defecto
#define SECURE    true              //true-> usar certificados SSL / false-> no certificados SSL
#define CLIENT_COOKIE       "AIROS_0027223EC2C0=f8f1a0ee4fba58beb9b2ff83474d4af6"      //Cookie fija, no se actualiza.

int leerPotencia(void);     //Devuelve la potencia recibida (dB). En caso de que no haya conexión, devuelve 0.

#endif
