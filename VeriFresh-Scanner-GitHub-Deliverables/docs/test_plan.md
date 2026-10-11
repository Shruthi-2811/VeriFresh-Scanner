# Test Plan and Results

| Test ID | Test | Procedure | Expected result | Actual result |
|---|---|---|---|---|
| HW-01 | Power-up | Connect USB and power on | ESP32 starts normally | Fill after test |
| HW-02 | BME680 detection | Start firmware | Initialized message | Fill after test |
| HW-03 | SGP30 detection | Start firmware | Initialized message | Fill after test |
| HW-04 | CSV output | Serial Monitor at 115200 | Header and rows appear | Fill after test |
| HW-05 | Sensor unavailable | Power off, disconnect sensor, restart | Error message; no false valid data | Fill after test |
| HW-06 | Baseline repeatability | Repeat empty-chamber runs | Variation documented | Fill after test |
| HW-07 | Sample repeatability | Repeat controlled sample procedure | Variation documented | Fill after test |
| DATA-01 | Data completeness | Inspect CSV | Required fields present | Fill after test |
| ML-01 | Independent evaluation | Test on different bananas/batches | Report metrics and sample split | Pending |

For each sample record unique sample/replicate ID, label source, sample mass, date/time, duration, chamber, sensor models, ambient conditions, baseline/recovery procedure, and notes. Do not invent pass/fail results or thresholds. A successful sensor read does not validate chemical detection.
