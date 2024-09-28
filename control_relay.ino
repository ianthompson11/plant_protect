/**********************************************************************************
 *  TITLE: Blynk + Manual Button control Relays using ESP32 (Real time feedback + no WiFi control + Web control)
 *  by Tech StudyCell (adapted for HTML control)
 **********************************************************************************/

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL22D-jte5M"
#define BLYNK_TEMPLATE_NAME "Smart Switch"
#define BLYNK_AUTH_TOKEN "e04arHaz1V4umQn2jiFyoTZeFymP7Y7O"

// Your WiFi credentials.
char ssid[] = "nombre de la red";
char pass[] = "Contraseña de su red";

// Flag to indicate if Blynk state should be fetched
bool fetch_blynk_state = true;

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AceButton.h>
#include <WebServer.h> // Library for the web server

using namespace ace_button;

// Define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27

#define wifiLed   2   //D2

// Change the virtual pins according to the rooms
#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4

// Relay State
bool toggleState_1 = LOW; 
bool toggleState_2 = LOW;
bool toggleState_3 = LOW;
bool toggleState_4 = LOW;

int wifiFlag = 0;

char auth[] = BLYNK_AUTH_TOKEN;

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);

BlynkTimer timer;
WebServer server(80); // Create a web server on port 80

// HTML page content
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
  <h1>ESP32 Relay Control</h1>
  <p>Relay 1: <button onclick="toggleRelay(1)">Toggle</button></p>
  <p>Relay 2: <button onclick="toggleRelay(2)">Toggle</button></p>
  <p>Relay 3: <button onclick="toggleRelay(3)">Toggle</button></p>
  <p>Relay 4: <button onclick="toggleRelay(4)">Toggle</button></p>

  <script>
    function toggleRelay(relay) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/relay?number=" + relay, true);
      xhr.send();
    }
  </script>
</body>
</html>
)=====";

// Function to handle web requests for toggling relays
void handleRelay() {
  String relayNum = server.arg("number");
  if (relayNum == "1") {
    toggleState_1 = !toggleState_1;
    digitalWrite(RelayPin1, toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
  else if (relayNum == "2") {
    toggleState_2 = !toggleState_2;
    digitalWrite(RelayPin2, toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
  else if (relayNum == "3") {
    toggleState_3 = !toggleState_3;
    digitalWrite(RelayPin3, toggleState_3);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  }
  else if (relayNum == "4") {
    toggleState_4 = !toggleState_4;
    digitalWrite(RelayPin4, toggleState_4);
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  }
  server.send(200, "text/html", "Relay Toggled");
}

// Web server setup
void setupWebServer() {
  server.on("/", []() {
    server.send(200, "text/html", MAIN_page);
  });
  server.on("/relay", handleRelay);
  server.begin();
}

// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, !toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, !toggleState_4);
}

void checkBlynkStatus() { // called every 3 seconds
  bool isconnected = Blynk.connected();
  if (!isconnected) {
    wifiFlag = 1;
    Serial.println("Blynk Not Connected");
    digitalWrite(wifiLed, LOW);
  } else {
    wifiFlag = 0;
    if (!fetch_blynk_state) {
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
    }
    digitalWrite(wifiLed, HIGH);
    Serial.println("Blynk Connected");
  }
}

BLYNK_CONNECTED() {
  if (fetch_blynk_state) {
    Blynk.syncVirtual(VPIN_BUTTON_1);
    Blynk.syncVirtual(VPIN_BUTTON_2);
    Blynk.syncVirtual(VPIN_BUTTON_3);
    Blynk.syncVirtual(VPIN_BUTTON_4);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);

  digitalWrite(wifiLed, LOW);

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);

  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  button3.init(SwitchPin3);
  button4.init(SwitchPin4);

  // Conectar al Wi-Fi
  WiFi.begin(ssid, pass);
  Serial.println("Conectando a WiFi...");
  
  // Esperar hasta que se conecte al Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  
  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP del ESP32: ");
  Serial.println(WiFi.localIP());  // Imprime la IP del ESP32

  timer.setInterval(2000L, checkBlynkStatus); 
  Blynk.config(auth);
  delay(1000);

  if (!fetch_blynk_state) {
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  }

  setupWebServer(); // Iniciar el servidor web
}


void loop() {
  Blynk.run();
  timer.run();
  button1.check();
  button2.check();
  button3.check();
  button4.check();
  server.handleClient(); // Handle incoming web requests
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventReleased) {
    digitalWrite(RelayPin1, toggleState_1);
    toggleState_1 = !toggleState_1;
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventReleased) {
    digitalWrite(RelayPin2, toggleState_2);
    toggleState_2 = !toggleState_2;
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventReleased) {
    digitalWrite(RelayPin3, toggleState_3);
    toggleState_3 = !toggleState_3;
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (eventType == AceButton::kEventReleased) {
    digitalWrite(RelayPin4, toggleState_4);
    toggleState_4 = !toggleState_4;
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  }
}
