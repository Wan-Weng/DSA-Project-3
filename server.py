from flask import Flask, request, jsonify
import subprocess
import json
import os

app = Flask(__name__)

@app.route("/topk", methods=["GET"])
def topk():
    args = {
        "protein": request.args.get("protein", "0"),
        "sugar": request.args.get("sugar", "9999"),
        "fiber": request.args.get("fiber", "0"),
        "k": request.args.get("k", "5")
    }

    try:
        result = subprocess.run(
            ["./nutrigeeks", args["protein"], args["sugar"], args["fiber"], args["k"]],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8",
            errors="replace",
            env={**os.environ, "LOOKUP_MODE": "1"}  # ✅ suppress logs during lookup
        )

        print("🟡 STDOUT from C++:", result.stdout)
        print("🔴 STDERR from C++:", result.stderr)

        if result.returncode != 0:
            return jsonify({"error": "C++ error", "details": result.stderr}), 500

        clean_output = result.stdout.strip().splitlines()[-1]
        data = json.loads(clean_output)
        return jsonify(data)

    except Exception as e:
        return jsonify({"error": f"Server error: {str(e)}"}), 500

@app.route("/lookup", methods=["GET"])
def lookup():
    food_id = request.args.get("id", "")
    try:
        result = subprocess.run(
            ["./nutrigeeks", "--lookup", food_id],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8"
            # no env change here → stderr logging stays off
        )

        stdout_lines = result.stdout.strip().splitlines()
        stderr_lines = result.stderr.strip().splitlines()

        category_line = ""
        for line in reversed(stdout_lines):
            if line.strip() and "Loaded" not in line:
                category_line = line.strip()
                break

        if result.returncode != 0 or not category_line:
            return jsonify({"error": result.stderr.strip() or "Category not found"}), 404

        return jsonify({"id": food_id, "category": category_line})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run(port=8080, debug=False)
