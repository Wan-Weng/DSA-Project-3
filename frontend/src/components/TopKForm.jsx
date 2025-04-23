import React, { useState } from "react";

function TopKForm() {
  const [formData, setFormData] = useState({
    protein: "",
    sugar: "",
    fiber: "",
    k: "5",
  });

  const [results, setResults] = useState([]);
  const [error, setError] = useState("");

  

  const handleChange = (e) => {
    setFormData({ ...formData, [e.target.id]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError("");
    setResults([]);

    const query = new URLSearchParams({
      protein: formData.protein || "0",
      sugar: formData.sugar || "9999",
      fiber: formData.fiber || "0",
      k: formData.k || "5",
    }).toString();

    try {
      const res = await fetch(`/topk?${query}`);
      const data = await res.json();

      if (!res.ok) {
        setError(data.error || "Server error");
      } else {
        setResults(data.heap_results || []);
      }
    } catch (err) {
      setError("Failed to fetch: " + err.message);
    }
  };



  return (
    <div style={{ maxWidth: "650px", margin: "auto", padding: "1rem" }}>
      <h2>Nutri-Geeks 🥦</h2>
      <form onSubmit={handleSubmit}>
        <input
          id="protein"
          placeholder="Min Protein (g)"
          value={formData.protein}
          onChange={handleChange}
        />
        <input
          id="sugar"
          placeholder="Max Sugar (g)"
          value={formData.sugar}
          onChange={handleChange}
        />
        <input
          id="fiber"
          placeholder="Min Fiber (g)"
          value={formData.fiber}
          onChange={handleChange}
        />
        <input
          id="k"
          type="number"
          min="1"
          placeholder="Top K"
          value={formData.k}
          onChange={handleChange}
        />
        <button type="submit">Find</button>
      </form>

   
      {error && <p style={{ color: "red" }}>{error}</p>}

      {results.map((item, index) => (
        <div key={index} className="result-card">
          <h3>Result {index + 1}</h3>
          <p><strong>ID:</strong> {item.id || "N/A"}</p>
          <p><strong>Category:</strong> {item.category}</p>
          <p><strong>Protein:</strong> {Number(item.protein).toFixed(2)}g</p>
          <p><strong>Fiber:</strong> {Number(item.fiber).toFixed(2)}g</p>
          <p><strong>Sugar:</strong> {Number(item.sugar).toFixed(2)}g</p>
          <p><strong>Fat:</strong> {Number(item.fat).toFixed(2)}g</p>
          <p><strong>Score:</strong> {item.score.toFixed(2)}</p>
        </div>
      ))}
    </div>
  );
}

export default TopKForm;
