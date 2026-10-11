from pathlib import Path
import csv
ROOT = Path(__file__).resolve().parents[1]

def test_real_data_template():
    with (ROOT / "data/real_readings_template.csv").open(newline="", encoding="utf-8") as f:
        headers = next(csv.reader(f))
    assert "sample_id" in headers
    assert "sgp_tvoc_ppb" in headers
    assert "bme_gas_ohms" in headers

def test_docs_exist():
    for path in ["README.md", "LICENSE", "docs/architecture.md", "docs/wiring.md", "docs/bom.md", "docs/test_plan.md"]:
        assert (ROOT / path).exists()

def test_evidence_folders_exist():
    assert (ROOT / "evidence/photos").is_dir()
    assert (ROOT / "evidence/videos").is_dir()
