async function loadAllProjects() {
  await fetch("../api/projects.php")
    .then((res) => res.json())
    .then((data) => {
      const container = document.getElementById("container");
      container.innerHTML = "";
      data.forEach((doc) => {
        const projectDetails = document.createElement("div");
        projectDetails.innerHTML = `
                    <h2>Name: ${doc.name}</h2>
                    <p>Project Manager: ${doc.ProjectManagerID}</p>
                    <p>Description: ${doc.description}</p>
                    <p>Members: ${doc.members}</p>
                `;
        container.appendChild(projectDetails);
      });
    });
}

async function loadMyProjects(developerName) {
  await fetch("../api/projects.php")
    .then((res) => res.json())
    .then((data) => {
      const container = document.getElementById("container");
      container.innerHTML = "";
      data.forEach((doc) => {
        if (doc.members.toLowerCase().includes(developerName.toLowerCase())) {
          const projectDetails = document.createElement("div");
          projectDetails.innerHTML = `
                    <h2>Name: ${doc.name}</h2>
                `;
          container.appendChild(projectDetails);
        }
      });
    });
}

async function loadFilteredDevelopers() {
  await fetch("../api/software_developers.php")
    .then((res) => res.json())
    .then((data) => {
      const container = document.getElementById("container");
      container.innerHTML = `
        <label>Filter by: <input type="text" id="filterInput" /></label>
        <div id="results"></div>
        `;

      const inputField = document.getElementById("filterInput");
      const resultsContainer = document.getElementById("results");

      inputField.addEventListener("input", () => {
        resultsContainer.innerHTML = "";
        const filterValue = inputField.value.toLowerCase();

        const filtered = data.filter(
          (dev) =>
            dev.skills.toLowerCase().includes(filterValue) || filterValue === ""
        );

        filtered.forEach((dev) => {
          const devDetails = document.createElement("div");
          devDetails.innerHTML = `
                    <h2>Name: ${dev.name}</h2>
                    <p>Age: ${dev.age}</p>
                    <p>Skills: ${dev.skills}</p>
                `;
          resultsContainer.appendChild(devDetails);
        });
      });
    });
}

function loadProducts() {
  const productsContainer = document.getElementById("productsContainer");

  fetch("../api/products.php")
    .then((response) => response.json())
    .then((data) => {
      if (!Array.isArray(data)) {
        productsContainer.innerHTML = "<p>Error loading products.</p>";
        return;
      }

      data.forEach((product) => {
        const label = document.createElement("label");
        label.innerHTML = `
                    <input type="checkbox" name="products[]" value="${product.id}">
                    ${product.name} - Price: ${product.price}
                `;
        productsContainer.appendChild(label);
      });
    })
    .catch((error) => {
      console.error("Failed to load products:", error);
      container.innerHTML = "<p>Error loading products.</p>";
    });
}

document.addEventListener("DOMContentLoaded", () => {
  loadProducts();

  const addProductsForm = document.getElementById("addProductsForm");

  addProductsForm.addEventListener("submit", async (event) => {
    event.preventDefault(); // prevent default form submission

    const formData = new FormData(addProductsForm);
    const products = [];

    document
      .querySelectorAll('input[name="products[]"]:checked')
      .forEach((input) => {
        products.push(input.value);
      });

    const data = {
      username: sessionStorage.getItem("username"),
      products: products,
    };

    try {
      const response = await fetch("../api/products.php", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(data),
      });

      const result = await response.json();

      if (response.ok) {
        addProductsForm.reset();
        alert(`Order added! Total Price before discount: ${result.totalPrice}`);
      } else {
        alert(result.error || "Failed to add recipe.");
      }
    } catch (error) {
      console.error("Error:", error);
      alert("Network error while adding recipe.");
    }
  });
});
