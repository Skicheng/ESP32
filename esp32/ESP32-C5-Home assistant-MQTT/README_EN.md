# ESP32C5 Wi-Fi + MQTT + DHT11 Example

A sample project for ESP32C5 that connects to Home Assistant via MQTT server over Wi-Fi, publishes DHT11 temperature and humidity data periodically, and receives subscribed commands. Core code is in `esp.ino`.

## Features
- **Wi-Fi Connection**: Connects to specified 2.4/5 GHz wireless network and outputs IP, channel, and band information to serial
- **MQTT Client**: Supports username/password authentication, auto-reconnection, and command topic subscription
- **Sensor Reading**: Reads DHT11 temperature and humidity data
- **Data Publishing**: Publishes JSON payload `{ "temperature": x, "humidity": y }` to MQTT topic every 2 seconds
- **Home Assistant Integration**: Designed to work seamlessly with Home Assistant Green

## Hardware Requirements
To follow along with this guide, you'll need the following:

- **Home Assistant Green**: A dedicated Home Assistant hardware device for managing your smart home
- **FireBeetle 2 ESP32-C5**: A low-power IoT development board featuring high performance, multi-protocol wireless connectivity, and smart power management — making it ideal for reliable, flexible, and long-lasting smart home and IoT applications
- **DHT11**: Accurate temperature & humidity sensor with plug-and-play interface


## Development Environment Setup

### Step 1. Download and Install Arduino IDE
Download and install the latest version of Arduino IDE according to your operating system from [arduino.cc](https://www.arduino.cc/en/software)

### Step 2. Launch Arduino IDE
Launch the Arduino application

### Step 3. Add ESP32 Board Package
1. Navigate to **File > Preferences**
2. Fill "Additional Boards Manager URLs" with the URL below:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_dev_index.json
   ```
3. Navigate to **Tools > Board > Boards Manager...**
4. Type the keyword "esp32" in the search box
5. Select the latest v3.3.0-alpha1 branch version of esp32 and install it

### Step 4. Select Your Board and Port
- **Board**: Navigate to **Tools > Board > esp32** and select "ESP32-C5 Dev Module"
- **Port**: Select the appropriate COM port for your FireBeetle 2 ESP32-C5

## Required Libraries
Search and install in Library Manager:
- **PubSubClient** (by Nick O'Leary)
- **DHT11** (library that provides `dht11.h` and `DHT.read(pin)` API)
- **WiFi** (included with ESP32 board package)

## Project Structure
```
Esp32C5_to_WiFi_and_MQTT/
├─ esp.ino          # Main Arduino sketch with Wi-Fi, MQTT, and DHT11 code
└─ README.md        # This documentation file
```

## Key Parameters (modify at the top of `esp.ino`)
- **Wi-Fi**:
  - `ssid`: Wireless network name
  - `password`: Wireless network password
- **MQTT**:
  - `mqtt_server`: MQTT server/gateway address (e.g., Home Assistant host)
  - `mqtt_port`: Port (default 1883)
  - `mqtt_user` / `mqtt_password`: Username and password
- **Topics**:
  - Publish: `esp32c5/data`
  - Subscribe: `esp32c5/commands`

## Quick Start (Arduino IDE)
1. Follow the **Development Environment Setup** steps above to configure Arduino IDE
2. Open the project and connect your FireBeetle 2 ESP32-C5
3. In `esp.ino`, change `ssid`, `password`, `mqtt_server`, `mqtt_user`, `mqtt_password` to your configuration
4. **Tools → Board**: Select "ESP32-C5 Dev Module"
5. **Tools → Port**: Select the appropriate COM port for your FireBeetle 2 ESP32-C5
6. Click **Upload**
7. Open **Serial Monitor**, set baud rate to `115200` to observe logs

## MQTT Topics and Payloads
- **Publish Topic**: `esp32c5/data`
- **Payload Example**:
```json
{"temperature": 23.4, "humidity": 56.0}
```
- **Subscribe Topic**: `esp32c5/commands` (received messages will be printed to serial)

## Serial Log Example
```
Connecting to <your-ssid>
....
WiFi connected
IP address: 192.168.x.x
Channel: 6
Band: 2.4GHz
Testing server port connectivity...Port reachable!
Attempting MQTT connection...Connected
Subscribed topic: esp32c5/commands
Published: {"temperature":23.4,"humidity":56.0}
```

## Troubleshooting
- **Wi-Fi not connecting**: Verify SSID/password is correct, router allows 2.4GHz, or move closer to router
- **MQTT connection failed**: Verify `mqtt_server`/port/credentials are correct, port 1883 is not blocked by firewall
- **No data published**: Check DHT11 wiring and power supply, confirm `DHT11_PIN` matches actual GPIO
- **Band/Channel**: Serial will print current channel and 2.4/5GHz band, confirm it matches your network

## License
Recommended to use MIT License (can be replaced as needed).
## Acknowledgments
- Espressif ESP32 Arduino Core
- PubSubClient by Nick O'Leary
- DHT11 library authors and community contributors

