# Circuit and Wiring

```text
ESP32 DevKit                 BME680 breakout
3V3 ------------------------ VIN/3V*
GND ------------------------ GND
GPIO 21 (SDA) --------------- SDA
GPIO 22 (SCL) --------------- SCL
        |                     |
        +---------------------+------ SGP30 breakout
                               VIN/3V* <- 3V3 rail
                               GND     <- common GND
                               SDA     <- GPIO 21
                               SCL     <- GPIO 22
```

| ESP32 pin | Connect to both modules | Purpose |
|---|---|---|
| 3V3 | VIN/3V, only if supported by breakout | Power |
| GND | GND | Common ground |
| GPIO 21 | SDA | I2C data |
| GPIO 22 | SCL | I2C clock |

*Board voltage requirements vary. Follow the exact breakout documentation; do not power a 3.3 V-only board from 5 V. Typical addresses: BME680 0x76/0x77, SGP30 0x58. Power off before changing wiring. This is a wiring guide, not a PCB schematic.
