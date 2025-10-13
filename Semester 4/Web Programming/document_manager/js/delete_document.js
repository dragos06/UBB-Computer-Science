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

        const del = document.createElement("button");
        del.textContent = "❌";
        del.onclick = () => {
          if (confirm("Delete this document?")) {
            fetch("../api/document.php", {
              method: "DELETE",
              headers: { "Content-Type": "application/json" },
              body: JSON.stringify({ id: doc.id }),
            }).then(loadDocuments);
          }
        };

        listItemDiv.appendChild(li);
        listItemDiv.appendChild(del);

        list.appendChild(listItemDiv);
      });
    });
}

document.addEventListener("DOMContentLoaded", () => {
  loadDocuments();
});
