let projectNames = [];

async function addDevToProjects() {
  const projectInput = document.getElementById("projectInput");
  const projectName = projectInput.value;
  const projectList = document.getElementById("projectList");

  const liItem = document.createElement("li");
  liItem.innerText = projectName;
  projectList.appendChild(liItem);

  projectNames.push(projectName);
}

async function saveDevToProjects() {
  const developerInput = document.getElementById("developerInput");
  const developerName = developerInput.value;
  const data = {
    dev: developerName,
    projects: projectNames,
  };

  await fetch("../api/projects.php", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });

  alert("User added succesfully!");
  

  window.location.href = window.history.back();
}

document.addEventListener("DOMContentLoaded", () => {
  const addToProject = document.getElementById("addToProject");
  addToProject.onclick = addDevToProjects;

  const saveButton = document.getElementById("saveButton");
  saveButton.onclick = saveDevToProjects;
});
