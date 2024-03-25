/*
  Arduino client port 3490

  Autores: pcefusaro@gmail.com ariellorusso@gmail.com

 */

#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip[] = {192,168,1,177}; //arduino
IPAddress server(192,168,1,101); // mi ip

int I; //Led de play
const int boton=26;//Pulsador de desconeccion
const int Pote= A15;//Dial de potenciometro
const int Play=29; //boton de play/pause
const int Next=28; //boton de next
const int Prev=27; //boton de prev

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 3490 is the serv port):
EthernetClient client;

void setup() {
  //Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(26,INPUT);
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
  // Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  //Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 3490)) {
      digitalWrite(24, HIGH);
    //Serial.println("connected");
    // Make a HTTP request:
      client.println("A");
  }
  /*else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }*/
}

boolean antirebote(int pin)
{
const int tiempoAntirebote = 15;
int contador=0;
boolean estado, estadoAnterior;
do{
    estado = digitalRead(pin);
    if(estado != estadoAnterior)
    {
        contador = 0;
        estadoAnterior = estado;
    }
    else{contador++;}
    delay(1);
    }while(contador <= tiempoAntirebote);

return estado;
} 

boolean estado_vol(int pote)
{
  int tiempo=0,tiempoMuestra = 10, muestra, muestraSig,dx;
  muestra=analogRead(pote);
  do{
  tiempo++;
  delay(1);
  }while(tiempo<=tiempoMuestra);
  
 muestraSig=analogRead(pote);
 
 dx=muestra-muestraSig;
 if(dx<=0)
   dx=dx*(-1);
  
 if(dx<=2)	//Tolerancia de variación de error
 {
   return false;
 }
 else{ return true;}
}

int volumen(int pote)
{
  int Led, Potenciometro=analogRead(pote);
  Led=(Potenciometro/4)-18;
  analogWrite(3,Led);
  int vol=(Potenciometro);
  if(vol>=0)
   return vol;
}


void loop()
{

 if (client.available())
  {
    if(estado_vol(Pote))
    {
        client.print("V");
	client.print(volumen(Pote));
    }
    if(antirebote(Play))
    {
      digitalWrite(25,HIGH);
      client.print("P");
      delay(500);
      digitalWrite(25,LOW);	   
    }
        
   
    if(antirebote(Next))
    {
      digitalWrite(22,HIGH);
      client.print("n");
      delay(500);
      digitalWrite(22,LOW);      
    }
    if(antirebote(Prev))
    {
      digitalWrite(23,HIGH);
      client.print("p");
      delay(500);
      digitalWrite(23,LOW);
    }

    if(antirebote(boton))
    {
      client.print("x");
      delay(500);
    }
    
  }
 if (!client.connected()) 
 {
   //Serial.println("disconnecting.");
     digitalWrite(24, LOW);
     digitalWrite(25, LOW);
     digitalWrite(23, LOW);
     digitalWrite(22, LOW);
     analogWrite(3, 0);
   client.stop();
   exit(1);
   // do nothing forevermore:
   for(;;)
    ;
 }
}

