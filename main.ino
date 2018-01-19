
/*
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
 
 //warning you cannot use pin 4, 11, 12, 13

// vars 


String HTTP_req;          // stores the HTTP request

int pin3 = 3; 
int pin7 = 7;

File file; 

void ButtonState(); 

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
0x09,0xA2,0xDA,0x00,0x01,0x26
};
IPAddress ip(192,168,1,54);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  pinMode(pin3, OUTPUT);
  pinMode(pin7, INPUT);
 
   // working with sd card slot 

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    
    return;
  }

  Serial.println("initialization done.");



}


void loop() {
    
    // check button state

  // listen for incoming clients
  EthernetClient client = server.available();
   
   ButtonState();

  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();



    if (SD.exists("index.htm")){
        
       Serial.println("file exists");  
       
          file = SD.open("index.htm"); 

          if (file) {
               
               while (file.available()){
                   
                   client.write(file.read());
                  
               }
             
                file.close();
          }
          

          
    } else if (!SD.exists("index.htm")) {

       Serial.println("file not exists");

    }

           Serial.print(HTTP_req);
           HTTP_req = ""; 
           break;
    
         
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}



void ButtonState() {

   if (digitalRead(pin7) == HIGH) {

      digitalWrite(pin3,LOW);

   }


  else if (digitalRead(pin7) == LOW) {

      digitalWrite(pin3,HIGH);

   }

}

*/


#include <SPI.h>
#include <Ethernet.h>

 int StateOfBell = 0; 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x09,0xA2,0xDA,0x00,0x01,0x26 };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "http://homedoorbell.atwebpages.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,54);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.write("please wait ....");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println(client.connect(server, 80));
    Serial.println("connected");

    // Make a HTTP request:
    client.println("GET / index.php?value=");
    client.println(StateOfBell);
    client.println(" HTTP/1.1");
    client.println("Host: http://homedoorbell.atwebpages.com");
    client.println("Connection: close");
    Serial.println("Yea man mi connected fine man");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}



void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    Serial.print("found data to read");
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}