#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

HTTPClient sender;
WiFiClient wifiClient;

// WLAN-Daten
const char* ssid = "ssid";
const char* password = "pw";

int pirPin = D1;

 
void setup() {
 // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pirPin, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("Verbunden!");

}
 
void loop() {
 // put your main code here, to run repeatedly:
 if(digitalRead(pirPin) == HIGH){
  
  Serial.println("MOVEMENT");

  makerequest();
  
 }
 else{
  Serial.println("---");
 }
}

void makerequest(){
  if (sender.begin(wifiClient, "<API URL of your wishes>")) {

    // HTTP-Code der Response speichern
    int httpCode = sender.GET();
   

    if (httpCode > 0) {
      
      // Anfrage wurde gesendet und Server hat geantwortet
      // Info: Der HTTP-Code für 'OK' ist 200
      if (httpCode == HTTP_CODE_OK) {

        // Hier wurden die Daten vom Server empfangen

        // String vom Webseiteninhalt speichern
        String payload = sender.getString();

        // Hier kann mit dem Wert weitergearbeitet werden
       // ist aber nicht unbedingt notwendig
        Serial.println(payload);
      }
      
    }else{
      // Falls HTTP-Error
      Serial.printf("HTTP-Error: ", sender.errorToString(httpCode).c_str());
    }

    // Wenn alles abgeschlossen ist, wird die Verbindung wieder beendet
    sender.end();
    
  }else {
    Serial.printf("HTTP-Verbindung konnte nicht hergestellt werden!");
  }
}
