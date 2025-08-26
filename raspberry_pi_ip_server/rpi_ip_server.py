import http.server
import socketserver
import socket
import json
import psutil # New import
import os     # New import for path checking

PORT = 6000

def get_ip_address():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))  # Connect to a public DNS server to get local IP
        ip_address = s.getsockname()[0]
        s.close()
        return ip_address
    except Exception as e:
        print(f"Could not get IP address: {e}")
        return "0.0.0.0" # Return a default if IP cannot be obtained

def get_hostname():
    return socket.gethostname()

# New function for CPU load
def get_cpu_load():
    return psutil.cpu_percent(interval=1) # CPU utilization over 1 second

# New function for memory load
def get_memory_load():
    mem = psutil.virtual_memory()
    return {
        "total_mb": round(mem.total / (1024 * 1024), 2),
        "used_mb": round(mem.used / (1024 * 1024), 2),
        "percent": mem.percent
    }

# New function for core temperature (Raspberry Pi specific)
def get_core_temperature():
    temp_path = "/sys/class/thermal/thermal_zone0/temp"
    if os.path.exists(temp_path):
        try:
            with open(temp_path, "r") as f:
                temp_raw = int(f.read().strip())
                return round(temp_raw / 1000.0, 2) # Convert millidegrees Celsius to Celsius
        except Exception as e:
            return f"Error: {e}"
    return "N/A" # Not available or path not found

class IPHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/ip':
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()
            
            ip = get_ip_address()
            hostname = get_hostname()
            cpu_load = get_cpu_load()
            memory_load = get_memory_load()
            core_temp = get_core_temperature()
            
            response_data = {
                "ip_address": ip,
                "hostname": hostname,
                "cpu_load_percent": cpu_load,
                "memory_load": memory_load,
                "core_temperature_celsius": core_temp
            }
            
            self.wfile.write(json.dumps(response_data).encode('utf-8'))
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b"404 Not Found")

if __name__ == "__main__":
    with socketserver.TCPServer(("0.0.0.0", PORT), IPHandler) as httpd:
        print(f"Serving IP, Hostname, CPU, Memory, and Temperature on port {PORT}")
        httpd.serve_forever()