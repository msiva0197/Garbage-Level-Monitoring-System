# 🚮 Garbage / Tank Level Monitoring System
IoT-based Garbage / Water Tank Level Monitoring System using ESP32, Ultrasonic Sensor (HC-SR04), and Blynk IoT.

📌 Features
📶 Connects to WiFi and Blynk Cloud
📊 Sends Tank Fill Percentage to Blynk (V1)
📝 Shows Tank Status (LOW, MEDIUM, FULL) in Blynk (V2)
⏱ Updates every 5 seconds
🚨 Sends Notification Alert when tank is FULL
🖥 Debug output via Serial Monitor

🛠 Hardware Required
ESP32 Development Board
HC-SR04 Ultrasonic Sensor
Jumper wires
Power Supply

🖥️ Blynk Setup
Create a new Template in Blynk IoT.
Template Name: Garbage Level Monitoring System
Template ID: TMPL3lpqAwNYn
Create a Device using your Auth Token.

Add the following Datastreams:
V0 → Distance (cm) 
V1 → Level % (Integer)
V2 → Status Text (String)

Create Widgets in the Blynk Mobile/Web Dashboard:
Gauge → V1 (Tank Level %)
Label → V2 (Status: LOW / MEDIUM / FULL)
Notification → Event named tank_full

⚙️ Code
The full code is inside garbage_monitor.ino

📷 Project Flow
Ultrasonic sensor measures distance inside the tank.
ESP32 calculates fill percentage.
Sends Level % and Status to Blynk.
If level ≥ 80% → sends Alert Notification 🚨.

🚀 How to Run
Install Arduino IDE + ESP32 board support.
Install Blynk library.
Upload the code to ESP32.
Open Serial Monitor (115200 baud) to debug.
Check your Blynk App / Web Dashboard for live updates.

📚 Future Improvements
Show raw distance in cm on Blynk (V0).
Add multiple bins/tanks support.

Integrate with Telegram / WhatsApp alerts.

Add battery monitoring for portable use.
