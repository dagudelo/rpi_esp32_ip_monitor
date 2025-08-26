# Use a slim Python image suitable for Raspberry Pi (ARM64 architecture)
FROM arm64v8/python:3.9-slim-buster

WORKDIR /app

# Copy the Python script into the container
COPY rpi_ip_server.py .

# Install psutil dependency
RUN pip install psutil

# Expose the port the server will run on
EXPOSE 5000

# Command to run the Python script when the container starts
CMD ["python3", "rpi_ip_server.py"]