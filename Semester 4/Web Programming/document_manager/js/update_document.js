const modal = document.getElementById("editModal");
const closeModal = document.getElementById("closeModal");
const editForm = document.getElementById("editDocumentForm");

function showModal(document) {
  modal.style.display = "block";
  editForm.id.value = document.id;
  editForm.author.value = document.author;
  editForm.title.value = document.title;
  editForm.pages.value = document.pages;
  editForm.type.value = document.type;
  editForm.format.value = document.format;
}

function loadDocuments() {
  fetch(`../api/document.php`)
    .then((res) => res.json())
    .then((data) => {
      const list = document.getElementById("docList");
      list.innerHTML = "";
      data.forEach((doc) => {
        const listItemDiv = document.createElement("div");
        listItemDiv.className = "listItemDiv";

        const li = document.createElement("li");
        li.textContent = `${doc.title} by ${doc.author} (${doc.pages} Pages, Type: ${doc.type}, Format: ${doc.format})`;

        const edit = document.createElement("button");
        edit.textContent = "✏️";
        edit.onclick = () => showModal(doc);

        listItemDiv.appendChild(li);
        listItemDiv.appendChild(edit);

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
  fetch("../api/document.php", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  }).then(() => {
    modal.style.display = "none";
    loadDocuments();
  });
};

document.addEventListener("DOMContentLoaded", () => {
  loadDocuments();
});
