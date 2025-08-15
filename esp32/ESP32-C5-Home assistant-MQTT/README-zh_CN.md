# ESP32C5 Wi-Fi + MQTT + DHT11 示例

一个基于 ESP32C5 通过 Wi-Fi 连接 Home Assistant MQTT 服务器、定时发布 DHT11 温湿度数据，并接收订阅指令的示例工程。核心代码见 `esp.ino`。

## 功能特性
- **Wi-Fi 连接**: 连接到指定的 2.4/5 GHz 无线网络，并在串口输出 IP、信道与频段信息
- **MQTT 客户端**: 支持用户名/密码认证，自动重连，订阅指令主题
- **传感器采集**: 读取 DHT11 温湿度数据
- **数据上报**: 每 2 秒向 MQTT 主题发布 JSON 载荷 `{ "temperature": x, "humidity": y }`
- **Home Assistant 集成**: 专为 Home Assistant Green 设计，无缝集成

## 硬件需求
要完成本指南，您需要以下硬件：

- **Home Assistant Green**: 专用于管理智能家居的 Home Assistant 硬件设备
- **FireBeetle 2 ESP32-C5**: 低功耗物联网开发板，具有高性能、多协议无线连接和智能电源管理功能 — 非常适合可靠、灵活且持久的智能家居和物联网应用
- **DHT11**: 具有即插即用接口的精确温湿度传感器


## 开发环境设置

### 步骤 1. 下载并安装 Arduino IDE
根据您的操作系统从 [arduino.cc](https://www.arduino.cc/en/software) 下载并安装最新版本的 Arduino IDE

### 步骤 2. 启动 Arduino IDE
启动 Arduino 应用程序

### 步骤 3. 添加 ESP32 开发板包
1. 导航至 **文件 > 首选项**
2. 在"附加开发板管理器网址"中填入以下 URL：
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_dev_index.json
   ```
3. 导航至 **工具 > 开发板 > 开发板管理器...**
4. 在搜索框中输入关键词 "esp32"
5. 选择最新版本的 esp32 v3.3.0-alpha1 分支并安装

### 步骤 4. 选择开发板和端口
- **开发板**: 导航至 **工具 > 开发板 > esp32** 并选择 "ESP32-C5 Dev Module"
- **端口**: 为您的 FireBeetle 2 ESP32-C5 选择相应的 COM 端口

## 依赖库
在库管理器中搜索并安装：
- **PubSubClient**（作者 Nick O'Leary）
- **DHT11**（提供 `dht11.h` 和 `DHT.read(pin)` API 的库）
- **WiFi**（随 ESP32 开发板包提供）

## 项目结构
```
Esp32C5_to_WiFi_and_MQTT/
├─ esp.ino          # 包含 Wi-Fi、MQTT 和 DHT11 代码的主 Arduino 程序
├─ README.md        # 英文文档
└─ README_CN.md     # 中文文档
```

## 关键参数（在 `esp.ino` 顶部修改）
- **Wi-Fi**:
  - `ssid`: 无线网络名称
  - `password`: 无线网络密码
- **MQTT**:
  - `mqtt_server`: MQTT 服务器/网关地址（如 Home Assistant 主机）
  - `mqtt_port`: 端口（默认 1883）
  - `mqtt_user` / `mqtt_password`: 用户名和密码
- **主题**:
  - 发布: `esp32c5/data`
  - 订阅: `esp32c5/commands`


## 快速开始（Arduino IDE）
1. 按照上述**开发环境设置**步骤配置 Arduino IDE
2. 打开项目并连接您的 FireBeetle 2 ESP32-C5
3. 在 `esp.ino` 中将 `ssid`、`password`、`mqtt_server`、`mqtt_user`、`mqtt_password` 改为您的配置
4. **工具 → 开发板**: 选择 "ESP32-C5 Dev Module"
5. **工具 → 端口**: 为您的 FireBeetle 2 ESP32-C5 选择相应的 COM 端口
6. 点击**上传**
7. 打开**串口监视器**，波特率设为 `115200` 观察日志

## MQTT 话题与载荷
- **发布主题**: `esp32c5/data`
- **载荷示例**:
```json
{"temperature": 23.4, "humidity": 56.0}
```
- **订阅主题**: `esp32c5/commands`（收到的消息会打印到串口）

## 串口日志示例
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

## 故障排查
- **Wi-Fi 未连接**: 确认 SSID/密码正确、路由器允许 2.4GHz，或靠近路由器
- **MQTT 连接失败**: 确认 `mqtt_server`/端口/账号密码正确、1883 端口未被防火墙拦截
- **无数据发布**: 检查 DHT11 接线与供电，确认 `DHT11_PIN` 与实际 GPIO 一致
- **带宽/频段**: 串口会打印当前信道与 2.4/5GHz 频段，确认与您的网络匹配

## 许可证
建议使用 MIT 许可证（可按需替换）。

## 致谢
- Espressif ESP32 Arduino Core
- PubSubClient by Nick O'Leary
- DHT11 库作者与社区贡献者
