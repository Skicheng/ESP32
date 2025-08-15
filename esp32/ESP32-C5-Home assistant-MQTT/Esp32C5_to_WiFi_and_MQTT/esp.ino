#include <WiFi.h>
#include <PubSubClient.h>
#include <dht11.h>
dht11 DHT;

#define DHT11_PIN 2

const char *ssid = "theWayOut3_5G";          // Change this to your WiFi SSID
const char *password = "DFRobot@2017";  // Change this to your WiFi password

// MQTT Broker settings
const char *mqtt_server = "192.168.199.205";  // Home Assistant IP address (or your MQTT broker)
const int mqtt_port = 1883;                    // Default MQTT port
const char *mqtt_user = "yvonne";             // MQTT username
const char *mqtt_password = "DFROBOT0317";    // MQTT password

// Publish and subscribe topics
const char* pub_topic = "esp32c5/data";
const char* sub_topic = "esp32c5/commands";

// MQTT client
WiFiClient espClient;
PubSubClient MQTTclient(espClient);

// WiFi connection function
void setup_wifi() {
  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
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
  
  // Get WiFi channel and band
  uint8_t channel = WiFi.channel();
  Serial.print("Channel: ");
  Serial.println(channel);
  if (channel <= 14) {
    Serial.println("Band: 2.4GHz");
  } else {
    Serial.println("Band: 5GHz");
  }
}

// MQTT message callback
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message [");
  Serial.print(topic);
  Serial.print("]: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Reconnect to MQTT if disconnected
void reconnect() {
  while (!MQTTclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (MQTTclient.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Connected");
      
      // Subscribe to topic after successful connection
      MQTTclient.subscribe(sub_topic);
      Serial.print("Subscribed topic: ");
      Serial.println(sub_topic);
      
    } else {
      Serial.print("Failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" retry in 5 seconds");
      delay(5000);
    }
  }
}

void testServerConnection() {
  WiFiClient testClient;
  Serial.print("Testing server port connectivity...");
  if (testClient.connect(mqtt_server, mqtt_port)) {
    Serial.println("Port reachable!");
    testClient.stop();
  } else {
    Serial.println("Connection failed! Check:");
    Serial.printf("- Address: %s\n", mqtt_server);
    Serial.printf("- Port: %d\n", mqtt_port);
    Serial.println("- Firewall settings");
    Serial.println("- Network isolation policy");
  }
}

// Read and publish DHT11 temperature and humidity
void publishSensorData() {
  int status = DHT.read(DHT11_PIN);
  if (status == 0) { 
    float temperatureC = (float)DHT.temperature;
    float humidityPct = (float)DHT.humidity;

    char payload[160];
    snprintf(payload, sizeof(payload),
             "{\"temperature\":%.1f,\"humidity\":%.1f}",
             temperatureC,
             humidityPct);

    if (MQTTclient.publish(pub_topic, payload)) {
      Serial.print("Published: ");
      Serial.println(payload);
    } else {
      Serial.println("Publish failed!");
    }
  } else {
    Serial.print("DHT11 read failed, code=");
    Serial.println(status);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  MQTTclient.setServer(mqtt_server, mqtt_port);
  MQTTclient.setCallback(callback);
  testServerConnection();
}

void loop() {
  if (!MQTTclient.connected()) {
    reconnect();
  }
  MQTTclient.loop();
  
  // Example: publish data every 2 seconds
  static unsigned long lastMsgTime = 0;
  unsigned long now = millis();
  
  if (now - lastMsgTime > 2000) {
    lastMsgTime = now;
    publishSensorData();
  }
}