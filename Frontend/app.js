// Search food from backend
function searchFood() {
    const query = document.getElementById("searchInput").value;
    const ds = document.getElementById("dsSelect").value;
  
    if (!query) {
      alert("Please enter a food ID or name.");
      return;
    }
  
    fetch(`/search?id=${query}&type=${ds}`)
      .then((response) => {
        if (!response.ok) throw new Error("Food not found");
        return response.json();
      })
      .then((data) => {
        displayResult(data);
      })
      .catch((error) => {
        document.getElementById("resultDisplay").innerHTML =
          `<p style="color:red;">Error: ${error.message}</p>`;
      });
  }
  
  // Display food result
  function displayResult(food) {
    const result = `
      <h3>${food.name}</h3>
      <p><strong>Category:</strong> ${food.category}</p>
      <p><strong>Protein:</strong> ${food.protein}g</p>
      <p><strong>Cholesterol:</strong> ${food.cholesterol}mg</p>
      <p><strong>Fiber:</strong> ${food.fiber}g</p>
      <p><strong>Calories:</strong> ${food.calories}</p>
    `;
  
    document.getElementById("resultDisplay").innerHTML = result;
  }
  
  // Health calculator logic
  function checkHealthiness(event) {
    event.preventDefault();
  
    const form = document.getElementById("healthForm");
    const protein = parseFloat(form.protein.value);
    const cholesterol = parseFloat(form.cholesterol.value);
    const fiber = parseFloat(form.fiber.value);
  
    let score = 0;
    if (protein >= 10) score++;
    if (cholesterol <= 30) score++;
    if (fiber >= 5) score++;
  
    let resultText = "";
    if (score === 3) resultText = "✅ Healthy";
    else if (score === 2) resultText = "⚠️ Unbalanced";
    else resultText = "❌ Unhealthy";
  
    document.getElementById("healthResult").innerText = `Result: ${resultText}`;
  }
  