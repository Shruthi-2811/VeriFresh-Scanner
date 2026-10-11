# VeriFresh Scanner
**ESP32 + BME680 + SGP30 banana ripening-pattern research prototype**

This partially assembled prototype collects gas-sensor responses around banana samples. The ESP32 reads a BME680 and SGP30 over I2C and outputs CSV over USB serial for later analysis.

> **Limitation:** BME680 gas resistance and SGP30 TVOC/eCO2 are broad, cross-sensitive sensor outputs. They do not identify or quantify calcium carbide, pesticides, or specific residues. Such claims require suitable validated analytical methods and laboratory confirmation.
>
> The data files here are blank templates, not fabricated measurements. Add only readings and photos collected from your real prototype.

## Files
- `docs/architecture.md` — system architecture
- `docs/wiring.md` — I2C wiring and pin table
- `docs/bom.md` — bill of materials
- `docs/test_plan.md` — test procedures and results recording
- `firmware/verifresh_bme680_sgp30.ino` — ESP32 firmware
- `data/real_readings_template.csv` — blank real-data template
- `data/test_results_template.csv` — blank test results template
- `evidence/` — folders for genuine prototype photos/videos

## Hardware
ESP32 DevKit, BME680 I2C breakout, SGP30 I2C breakout, jumper wires, breadboard, USB data cable, and a sample chamber. Optional battery/enclosure should be added only after checking electrical requirements.

## Wiring summary
| ESP32 | Both sensor breakouts |
|---|---|
| 3V3 | VIN/3V, only if board supports 3.3 V |
| GND | GND |
| GPIO 21 | SDA |
| GPIO 22 | SCL |

Typical addresses: BME680 `0x76` or `0x77`; SGP30 `0x58`. Check your exact breakout documentation and pin labels before powering on.

## Firmware setup
1. Install Arduino IDE 2.x and ESP32 board support.
2. In Library Manager install `Adafruit BME680 Library` and `Adafruit SGP30 Sensor`; install dependencies if prompted.
3. Open `firmware/verifresh_bme680_sgp30.ino`.
4. Select the matching ESP32 board and COM port; upload.
5. Open Serial Monitor at **115200 baud**. Rows contain elapsed time, BME680 readings, and SGP30 TVOC/eCO2.
6. If a sensor fails, power off and recheck power, ground, SDA/SCL, and I2C address.

The SGP30 eCO2 is an equivalent estimate, not a direct CO2 measurement. TVOC is not proof of a named compound.

## Python setup (for later data analysis)
Python 3.10–3.12 recommended:
```bash
python -m venv .venv
```
Windows PowerShell: `\.venv\Scripts\Activate.ps1`
macOS/Linux: `source .venv/bin/activate`
Then run: `pip install -r requirements.txt` and `pytest`.

No environment variables are required in the current version. Never commit passwords or API keys if cloud features are added later.

## Real data collection
1. Assign a unique sample ID and document how the ripening label was verified.
2. Keep sample mass, chamber, sensor position, warm-up, exposure time, and ambient conditions consistent.
3. Record empty-chamber baseline readings and allow sensor recovery between samples.
4. Save serial output and fill `data/real_readings_template.csv`.
5. Split model evaluation by independent banana/sample batch, not random rows from the same banana.
6. Record actual results in `data/test_results_template.csv`; attach logs in `evidence/test-results/`.

## Evidence
Add genuine photos of the whole device, wiring, sensor/chamber placement, and serial readings to `evidence/photos/`. Add a short real demonstration video to `evidence/videos/`. Do not use generated images as proof of a physical build.

## License
MIT License; see `LICENSE`.
