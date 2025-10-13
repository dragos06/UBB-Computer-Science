function loadDocuments() {
  const type = document.getElementById("typeFilter").value;
  const format = document.getElementById("formatFilter").value;

  const params = new URLSearchParams();
  if (type) params.append("type", type);
  if (format) params.append("format", format);

  fetch(`../api/document.php?${params.toString()}`)
    .then((res) => res.json())
    .then((data) => {
      const list = document.getElementById("docList");
      list.innerHTML = "";
      data.forEach((doc) => {
        const li = document.createElement("li");
        li.innerHTML = `${doc.title} by ${doc.author} (${doc.pages} Pages, Type: ${doc.type}, Format: ${doc.format})`;
        list.appendChild(li);
      });

      const filterText = `Type: ${type || "Any"}, Format: ${format || "Any"}`;
      localStorage.setItem("lastFilter", filterText);
      localStorage.setItem("filterType", type);
      localStorage.setItem("filterFormat", format);
      document.getElementById("lastFilter").textContent =
        "Last filter: " + filterText;
    });
}

document.addEventListener("DOMContentLoaded", () => {
  const storedType = localStorage.getItem("filterType");
  const storedFormat = localStorage.getItem("filterFormat");
  if (storedType) document.getElementById("typeFilter").value = storedType;

  if (storedFormat)
    document.getElementById("formatFilter").value = storedFormat;

  const last = localStorage.getItem("lastFilter");
  if (last)
    document.getElementById("lastFilter").textContent = "Last filter: " + last;

  loadDocuments();
});
