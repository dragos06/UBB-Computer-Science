document.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("addHousingForm");
  const list = document.getElementById("housingList");
  const backButton = document.getElementById("backButton");
  const modal = document.getElementById("editModal");
  const closeModal = document.getElementById("closeModal");
  const editForm = document.getElementById("editHousingForm");

  function showModal(housing) {
    modal.style.display = "block";
    editForm.id.value = housing.id;
    editForm.name.value = housing.name;
    editForm.location.value = housing.location;
    editForm.capacity.value = housing.capacity;
  }

  function loadHousings() {
    fetch("../api/housing.php")
      .then((res) => res.json())
      .then((data) => {
        list.innerHTML = "";
        data.forEach((housing) => {
          const listItemDiv = document.createElement("div");
          listItemDiv.className = "listItemDiv";

          const li = document.createElement("li");
          li.textContent = `${housing.name} - ${housing.location}: ${housing.capacity}`;

          const edit = document.createElement("button");
          edit.textContent = "✏️";
          edit.onclick = () => showModal(housing);

          const del = document.createElement("button");
          del.textContent = "❌";
          del.onclick = () => {
            if (confirm("Delete this housing?")) {
              fetch("../api/housing.api", {
                method: "DELETE",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ id: housing.id }),
              }).then(loadHousings);
            }
          };

          listItemDiv.appendChild(li);
          listItemDiv.appendChild(edit);
          listItemDiv.appendChild(del);

          list.appendChild(listItemDiv);
        });
      });
  }

  closeModal.onclick = () => {
    modal.style.display = "none";
  };
  window.onclick = (e) => {
    if (e.target === modal) modal.style.display = "none";
  };

  editForm.onsubmit = (e) => {
    e.preventDefault();
    const data = Object.fromEntries(new FormData(editForm));
    fetch("../api/housing.php", {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    }).then(() => {
      modal.style.display = "none";
      loadHousings();
    });
  };

  form.onsubmit = (e) => {
    e.preventDefault();
    const data = Object.fromEntries(new FormData(form));
    fetch("../api/housing.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    }).then(() => {
      form.reset();
      loadHousings();
    });
  };

  backButton.onclick = () => {
    window.location.replace("../pages/index.php");
  };

  loadHousings();
});
