# Distributed Automotive Dashboard System using CAN Protocol on STM32F429ZIT6

## Project Overview

This project implements a **distributed automotive dashboard system using the CAN (Controller Area Network) protocol** on the **STM32F429ZIT6 microcontroller**.

The system simulates a real vehicle environment where multiple **Electronic Control Units (ECUs)** communicate over a CAN bus, and a central node receives the data and displays real-time vehicle information.

## System Architecture

The system consists of **three CAN nodes** connected through a CAN bus.

### Node 1 – Vehicle Status Transmitter

This node sends basic vehicle status information:

* Indicator status
* Vehicle speed
* Engine temperature

### Node 2 – Engine & Time Transmitter

This node provides engine-related and time data:

* Gear position
* Engine RPM (measured using ADC)
* Real-Time Clock (RTC) time in HH:MM:SS format

### Node 3 – Central Dashboard Receiver

This node acts as the **dashboard controller**:

* Receives CAN messages from all nodes
* Applies hardware CAN filtering
* Displays formatted vehicle data using UART on **TERA TERM**

## Hardware Used

* STM32F429ZIT6 Microcontroller Boards (3)
* CAN Transceiver (MCP2551 / TJA1050)
* UART Terminal (TERA TERM)
* On-board LEDs for debugging
* Potentiometer (for RPM input via ADC)
* Push buttons / switches
* LEDs
* DHT11 Sensor

## Communication Protocol

* CAN Mode: Normal Mode
* Identifier Type: Standard Identifier (11-bit)
* Interrupt-based CAN reception
* Hardware CAN filter configuration
* Multi-node distributed communication architecture

## CAN Message IDs

| Parameter   | CAN ID |
| ----------- | ------ |
| Indicator   | 0x101  |
| Speed       | 0x201  |
| Temperature | 0x301  |
| Gear        | 0x401  |
| RPM         | 0x501  |
| Time        | 0x601  |

## Key Features

* Interrupt-driven CAN communication
* Hardware-based CAN message filtering
* ADC-based RPM measurement
* RTC peripheral integration for time display
* Real-time dashboard data output via UART
* Efficient ISR-safe architecture
* Multi-node automotive embedded system simulation

## Software Architecture

The firmware is designed using a modular embedded structure:

* STM32 HAL Drivers (generated using STM32CubeMX)
* CAN RX interrupt callback for message reception
* Flag-based processing in the main loop
* Structured embedded C implementation
* Use of volatile variables for safe ISR communication


## Learning Outcomes

Through this project, the following concepts were implemented and understood:

* CAN Bus architecture and communication
* CAN filter configuration using ID mask mode
* Interrupt handling in embedded systems
* Design of distributed ECU-based systems
* Real-time embedded communication
* Automotive embedded software design principles

## Future Improvements

* Integrate FreeRTOS for task-based architecture
* Implement CAN error detection and handling
* Add watchdog timer for system reliability
* Integrate OLED/LCD for graphical dashboard display
* Implement CAN diagnostic messages (UDS simulation)


