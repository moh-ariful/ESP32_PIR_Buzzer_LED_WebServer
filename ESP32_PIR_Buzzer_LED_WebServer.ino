#include <WiFi.h>
#include <WiFiManager.h> // Library WiFiManager
// Buzzer sifatnya High Active
// Skema Pemasangan LED:
// 1.Sambungkan kaki positif (anoda) LED ke pin nomor 25 pada ESP32
// 2.Sambungkan kaki negatif (katoda) LED ke resistor (220 ohm)
// 3.Sambungkan ujung lain resistor ke ground (GND) pada ESP32

WiFiServer server(80);

String header;

const int pirPin = 33; // Pin sensor PIR di pin 33
const int buzzerPin = 27; // Pin buzzer di pin 27
const int ledPin = 25; // Pin LED di pin 25
bool motionDetected = false;
unsigned long motionStartMillis = 0;
bool buzzerOn = false;
bool ledOn = false;
unsigned long ledStartMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT); // Set pirPin sebagai input
  pinMode(buzzerPin, OUTPUT); // Set buzzerPin sebagai output
  pinMode(ledPin, OUTPUT); // Set ledPin sebagai output
  digitalWrite(buzzerPin, LOW); // Pastikan buzzer mati saat memulai
  digitalWrite(ledPin, LOW); // Pastikan LED mati saat memulai
  Serial.println();
  Serial.println("Mulai Konfigurasi");

  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP32_AP");

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Memulai Server");
}

void loop() {
  WiFiClient client = server.available();
  motionDetected = digitalRead(pirPin); // Baca status sensor PIR

  if (motionDetected && !buzzerOn) {
    buzzerOn = true;
    ledOn = true;
    motionStartMillis = millis();
    ledStartMillis = millis();
    digitalWrite(buzzerPin, LOW); // Nyalakan buzzer (aktif rendah)
    digitalWrite(ledPin, HIGH); // Nyalakan LED
  }

  if (buzzerOn && (millis() - motionStartMillis >= 1000)) { // Matikan buzzer setelah 1 detik
    buzzerOn = false;
    digitalWrite(buzzerPin, HIGH); // Matikan buzzer (aktif rendah)
  }

  if (ledOn && (millis() - ledStartMillis >= 3000)) { // Matikan LED setelah 3 detik
    ledOn = false;
    digitalWrite(ledPin, LOW); // Matikan LED
  }

  if (client) {
    Serial.println("Client Baru");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            Serial.println();

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=UTF-8");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta http-equiv=\"refresh\" content=\"5\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; padding-top: 10px;}");
            client.println("body { margin-top: 0.5cm; }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".header-text { color: #00008B; }");
            client.println(".esp-text { color: #D10069; }");
            client.println(".data-text { font-size: 2em; margin: 10px 0; }");
            client.println(".motion { background-color: red; color: white; padding: 20px; font-size: 2em; animation: blink 1s infinite; }");
            client.println("@keyframes blink { 50% { opacity: 0; } }</style></head>");

            client.println("<body><h1 class='header-text'>Next Koding Enterprise</h1>");
            client.println("<h1 class='esp-text'>ESP32 Web Server</h1>");

            if (motionDetected) {
              client.println("<div class='motion'>Ada obyek terdeteksi</div>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Terputus");
    header = "";
  }
}
