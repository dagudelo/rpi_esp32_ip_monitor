# Raspberry Pi & ESP32 IP Monitor

This project allows an ESP32 device to fetch and display the IP address, hostname, CPU load, memory usage, and core temperature of multiple Raspberry Pi devices over Wi-Fi.

## Project Structure

*   `raspberry_pi_ip_server/`: Contains the Python web server and Dockerfile for Raspberry Pi.
*   `examples/WiFi_IP_Display/`: Contains the PlatformIO project for the ESP32 client.

## Setup Instructions

### 1. Raspberry Pi Server Setup

Each Raspberry Pi you want to monitor needs to run the server.

1.  **Enable Host Network Mode:** Ensure your Docker daemon allows host network mode.
2.  **Build Docker Image:**
    ```bash
    cd raspberry_pi_ip_server/
    docker build -t rpi-ip-server .
    ```
3.  **Run Docker Container:**
    ```bash
    docker stop rpi_ip_server || true
    docker rm rpi_ip_server || true
    docker run -d --restart=always --network=host --name rpi_ip_server rpi-ip-server
    ```
    *   **Note:** If external connections fail, check your Raspberry Pi's firewall (e.g., `sudo ufw allow 5000/tcp`).

### 2. ESP32 Client Setup (PlatformIO)

1.  **PlatformIO Project:**
    *   Ensure you have PlatformIO Core installed.
    *   This repository is a self-contained PlatformIO project.
    *   **Copy Board File:** If you haven't already, copy your board definition:
        `cp /path/to/your/original/T-QT/board/esp32-s3-t-qt-pro.json board/`
2.  **Configure Wi-Fi & IPs:**
    *   Open `examples/WiFi_IP_Display/WiFi_IP_Display.ino`.
    *   Update `ssid` and `password` with your Wi-Fi credentials.
    *   Update the `raspberryPiIPs` array with the actual IP addresses of your Raspberry Pis.
3.  **Build and Upload:**
    ```bash
    cd examples/WiFi_IP_Display/ # Or just from project root if PlatformIO is configured
    platformio run -t upload
    ```

## Verification

*   **Raspberry Pi Server:** Access `http://<Raspberry_Pi_IP_Address>:5000/ip` in a browser or with `curl`. You should see a JSON response with IP, hostname, CPU, memory, and temperature.
*   **ESP32 Client:** After uploading, the ESP32 screen should cycle through the data from each configured Raspberry Pi. 
