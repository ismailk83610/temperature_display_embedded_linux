# Linux Temperature Monitoring System using Raspberry Pi and C

## Overview

This project demonstrates how to interface an I²C temperature sensor with a Raspberry Pi running Linux using the C programming language.

The application communicates with the sensor through the Linux I²C device driver, reads temperature data, displays it on the terminal, and stores the readings in a log file.

---

## Features

* Embedded Linux application
* Written in C
* Uses Linux system calls (`open`, `read`, `write`, `ioctl`)
* I²C communication
* Temperature logging
* Error handling
* Continuous monitoring

---

## Hardware Used

* Raspberry Pi 4
* TMP102 Temperature Sensor
* MicroSD Card
* Raspberry Pi OS

---

## Software Requirements

* Raspberry Pi OS
* GCC Compiler
* Linux I²C Driver
* i2c-tools

Install dependencies:

```bash
sudo apt update
sudo apt install gcc i2c-tools
```

---

## Hardware Connections

| TMP102 | Raspberry Pi |
| ------ | ------------ |
| VCC    | 3.3V         |
| GND    | GND          |
| SDA    | GPIO2 (SDA)  |
| SCL    | GPIO3 (SCL)  |

---

## Build

```bash
gcc src/temperature.c -o temperature_monitor
```

---

## Run

```bash
./temperature_monitor
```

---

## Sample Output

```text
Temperature Monitoring Started

2026-08-01 18:00:02
Temperature : 25.18 °C

2026-08-01 18:00:04
Temperature : 25.31 °C
```

---

## Linux Concepts Used

* Embedded Linux
* Device Files (`/dev/i2c-1`)
* System Calls
* Device Drivers
* File Handling
* Process Management
* I²C Communication
* GCC Compilation

---

## Project Flow

```
Temperature Sensor
        │
        ▼
Linux I²C Driver
        │
        ▼
C Application
        │
 ┌──────┴───────┐
 │              │
 ▼              ▼
Terminal     Log File
```

---

## Learning Outcomes

* Embedded Linux development
* Raspberry Pi setup
* Linux system calls
* Hardware interfacing
* I²C communication
* C programming
* File handling
* Debugging Linux applications

---

## Author

Mohamed Ismail
