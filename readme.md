# GLOBOTA - ESP8266 Remote OTA Firmware Uploader  
### Secure Internet-Based Firmware Updates for Embedded Devices

## Overview

While I was going through ACS (Access Control System) boards, I noticed that most of them require a **physical wired connection** to upload or update firmware.  
This becomes a limitation when the devices are deployed in remote facilities, sensitive locations, or environments where physical access is restricted or expensive.

This project explores whether firmware upgrades can be performed:

- **Securely**
- **Remotely** (even over the public internet)
- **Without physical access**
- **Using a small, low-cost WiFi-enabled microcontroller**

The ESP8266 supports OTA (Over-The-Air) updates, but most examples focus only on **local network OTA**.  
This project extends the idea by enabling **global OTA** using router port forwarding + a password-protected upload portal.

The result is a lightweight, reliable, and secure method to update firmware over the internet — useful for research, IoT experimentation, prototyping security systems, and remote embedded applications.

---

## Features

- **Password-protected OTA update page**
- **Remote access** via port forwarding (WAN → ESP8266)
- **Persistence** — future uploaded firmware must retain OTA functionality
- **Clean template** for future firmware
- Minimal “bootloader-style” first firmware
- Built-in web server for OTA handling
- Easy integration into custom projects

---

## How It Works

1. You first flash the **master.ino** using USB.  
   This firmware:
   - Connects to WiFi  
   - Hosts a password-protected OTA page  
   - Lets you upload future firmware wirelessly  

2. Once installed, you **never need USB again**.

3. To upload firmware the second time (and every future time):

   ### Use the provided **template.ino**
   - Always base your project on `template.ino` (the OTA-safe template).
   - Make sure `template.ino` contains these lines (do **not** remove them):
     ```cpp
     // in setup()
     httpUpdater.setup(&server, "/update", update_username, update_password);

     // in loop()
     server.handleClient();
     ```
   - Put all your project logic inside the marked placeholder area in `template.ino`.  
     This guarantees the OTA webpage and password protection persist after every update.

   ### 🔧 How to generate the `.bin` file in Arduino IDE
   - Open your project (which uses `template.ino`) in Arduino IDE.  
   - Compile it once (Sketch → Verify/Compile).  
   - Then use **Sketch → Export Compiled Binary**.  
   - After compilation Arduino writes the binary to your sketch folder. There will be two `.bin` files:
     - `your_project.ino.bin`  
     - `your_project.ino.with_bootloader.bin`
   - **Use** the normal `.bin` (e.g. `your_project.ino.bin`) — **do not** use the `.with_bootloader.bin`.

   ### Upload the compiled `.bin` via OTA
   - Open the OTA update page in a browser:  
     `http://<ESP_LOCAL_IP>/update`  (or `http://<PUBLIC_IP>:<PORT>/update` for global access)
   - Enter your OTA username & password.
   - Click **Choose File** and select `your_project.ino.bin`.
   - Click **Update**.
   - The ESP8266 will receive the binary, flash it, and reboot automatically.
   - Because you built your project from `template.ino`, the OTA page and password protection remain available after reboot.

4. For global access:
   - Forward an external port (example: 8080) → ESP8266 local port 80.  
   - Access using:  
     `http://<PUBLIC_IP>:8080/update`  
   - Authenticate and upload the `.bin` the same way.


---

## Security Notes (Important)

Using OTA over the public internet introduces risks.  
To maintain safe operation:

- Always use strong OTA credentials  
- Avoid using default usernames  
- Change passwords regularly  
- Use non-standard port numbers for port forwarding  
- Never expose your ESP8266 to WAN without OTA password  
- Prefer using a VPN or Cloudflare Tunnel for higher security

This project is for **learning and experimentation**, not commercial deployments.

---






