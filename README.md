
---

## ▶️ How It Works

1. Each PIC microcontroller is configured as a **CAN node**  
2. Sensor data (ADC values, key presses, etc.) is collected  
3. Data is transmitted using **CAN frames**  
4. Receiving node decodes the message and updates peripherals  
5. Diagnostic commands allow verification of communication  

---

## ▶️ How to Run

1. Open the project in **MPLAB X IDE**  
2. Select the correct **PIC microcontroller** and configuration bits  
3. Build the project using **XC8 compiler**  
4. Program the hex file into both CAN nodes  
5. Connect nodes via **CAN transceivers (MCP2551 or equivalent)**  
6. Power on and observe data exchange on peripherals  

---

## 📥📤 Sample Operation

- Rotate potentiometer → ADC value transmitted via CAN  
- Receiving node displays value on **LCD / SSD**  
- Press keypad switch → Indicator status sent to other node  
- LEDs reflect left/right/off indicator states  

---

## 🎯 Learning Outcomes

- Strong understanding of **CAN bus architecture and frame structure**  
- Hands-on experience with **automotive embedded systems**  
- Improved skills in **real-time communication and debugging**  
- Practical exposure to **ECU-to-ECU communication**  
- Experience working with **peripheral interfacing and diagnostics**  

---

## 🔮 Future Enhancements

- Add multiple CAN nodes (multi-ECU network)  
- Implement CAN error states and bus-off recovery  
- Support CAN filtering and extended identifiers  
- Integrate UART-based PC monitoring  
- Port to ARM-based automotive controllers  

---

## 👤 Author

**Pasam Likitha**  
Embedded Systems & Software Enthusiast  

---

## ⭐ Support

If you found this project useful, don’t forget to **star ⭐ the repository**!
