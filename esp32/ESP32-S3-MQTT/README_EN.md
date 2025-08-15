
# ESP32-S3-MQTT

## Project Description

### Feature Overview

This ESP32S3 program implements the following functionalities:

1. Connect to a specified WiFi network
2. Connect to a message server using MQTT protocol
3. Read analog values from GPIO1 pin
4. Upload data to a specified MQTT topic every second
5. Receive control commands from the MQTT server
6. Provide detailed system status reports

### Hardware Requirements

- WiFi-enabled ESP32 development board
- Sensor/Analog signal source connected to GPIO1 pin

### Configuration

#### WiFi Configuration
```cpp
const char* ssid = "******";        // WiFi SSID
const char* password = "******";    // WiFi password
```

#### MQTT Configuration
```cpp
const char* mqtt_server = "******"; // MQTT broker address
const int mqtt_port = 1883;         // MQTT port (default: 1883)
const char* mqtt_user = "******";   // MQTT username
const char* mqtt_pass = "******";   // MQTT password
```

#### Additional Configuration
```cpp
const char* pub_topic = "sensors/ESP32S3/analog"; // Data publishing topic
const int PUBLISH_INTERVAL = 5000;  // Data upload interval (milliseconds)
const int ANALOG_PIN = 1;           // Analog input pin
```

### MQTT Data Format

The device publishes JSON-formatted data to the specified topic:

```json
{
  "device": "ESP32S3_Sensor_Node",
  "sensor": "analog",
  "value": 2048,
  "voltage": 1.65,
  "rssi": -65
}
```

- **device**: Device identifier
- **sensor**: Sensor type
- **value**: Raw ADC value (0-4095)
- **voltage**: Converted voltage value (0-3.3V)
- **rssi**: WiFi signal strength (dBm)

### Error Handling

The code includes comprehensive error detection and handling mechanisms:

1. Automatic reboot upon WiFi connection failure
2. Detailed error diagnostics for MQTT connection failures
3. Server-side connection validation
4. Detection and reporting of data publishing failures

## Deployment Instructions

1. Import the project into Arduino IDE
2. Modify configuration parameters according to actual requirements
3. Upload the program to ESP32S3 development board via USB cable
4. Open Serial Monitor (115200 baud rate) to monitor operation status
5. Use MQTT client to subscribe to the specified topic for data reception
