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

        const filtered = data.filter((dev) =>
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

document.addEventListener("DOMContentLoaded", () => {
  const urlParams = new URLSearchParams(window.location.search);
  const developerName = urlParams.get("name");

  if (!developerName) {
    window.location.href = "index.php";
  }

  const viewAllProjects = document.getElementById("viewAllProjects");
  viewAllProjects.onclick = loadAllProjects;

  const viewMyProjects = document.getElementById("viewMyProjects");
  viewMyProjects.onclick = () => loadMyProjects(developerName);

  const viewAllSDE = document.getElementById("viewAllSDE");
  viewAllSDE.onclick = () => loadFilteredDevelopers();

  const addSDE = document.getElementById("addSDE");
  addSDE.onclick = () => {
    window.location.href = "add_dev.php"
  }
});
