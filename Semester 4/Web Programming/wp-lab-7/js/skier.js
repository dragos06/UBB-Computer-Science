document.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("addSkierForm");
  const list = document.getElementById("skierList");
  const backButton = document.getElementById("backButton");
  const modal = document.getElementById("editModal");
  const closeModal = document.getElementById("closeModal");
  const editForm = document.getElementById("editSkierForm");

  function showModal(skier) {
    modal.style.display = "block";
    editForm.id.value = skier.id;
    editForm.name.value = skier.name;
    editForm.email.value = skier.email;
  }

  function loadSkiers() {
    fetch("../api/skier.php")
      .then((res) => res.json())
      .then((data) => {
        list.innerHTML = "";
        data.forEach((skier) => {
          const listItemDiv = document.createElement("div");
          listItemDiv.className = "listItemDiv";

          const li = document.createElement("li");
          li.textContent = `${skier.name} (${skier.email})`;

          const edit = document.createElement("button");
          edit.textContent = "✏️";
          edit.onclick = () => showModal(skier);

          const del = document.createElement("button");
          del.textContent = "❌";
          del.onclick = () => {
            if (confirm("Delete this skier?")) {
              fetch("../api/skier.php", {
                method: "DELETE",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ id: skier.id }),
              }).then(loadSkiers);
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
    fetch("../api/skier.php", {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    }).then(() => {
      modal.style.display = "none";
      loadSkiers();
    });
  };

  form.onsubmit = (e) => {
    e.preventDefault();
    const data = Object.fromEntries(new FormData(form));
    fetch("../api/skier.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    }).then(() => {
      form.reset();
      loadSkiers();
    });
  };

  backButton.onclick = () => {
    window.location.replace("../pages/index.php");
  };

  loadSkiers();
});
