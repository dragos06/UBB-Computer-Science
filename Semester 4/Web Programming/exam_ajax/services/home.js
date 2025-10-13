async function loadAllTasks() {
  await fetch("../api/task.php")
    .then((res) => res.json())
    .then((data) => {
      const movesLabel = document.getElementById("movesLabel");
      movesLabel.innerText = "Moves done: " + sessionStorage.getItem("moves");

      const todoContainer = document.getElementById("todoContainer");
      const inprogressContainer = document.getElementById(
        "inprogressContainer"
      );
      const doneContainer = document.getElementById("doneContainer");

      todoContainer.innerHTML = "To Do: ";
      inprogressContainer.innerHTML = "In Progress: ";
      doneContainer.innerHTML = "Done: ";

      data.forEach((task) => {
        const taskDetails = document.createElement("div");

        taskDetails.innerHTML = `
                    <h2>Title: ${task.title}</h2>
                    <p>Status: ${task.status}</p>
                    <p>Assigned To: ${task.assignedTo}</p>
                    <p>Last Updated: ${task.lastUpdated}</p>
                    <button id='moveTodo' onclick='moveTodo(${task.id})'>Move to ToDo</button>
                    <button id='moveInprogress' onclick='moveInprogress(${task.id})'>Move In Progress</button>
                    <button id='moveDone' onclick='moveDone(${task.id})'>Move Done</button>
                `;
        if (task.status === "todo") {
          todoContainer.appendChild(taskDetails);
        } else if (task.status === "in_progress") {
          inprogressContainer.appendChild(taskDetails);
        } else if (task.status === "done") {
          doneContainer.appendChild(taskDetails);
        }
      });
    });
}

async function moveTodo(id) {
  const moves = sessionStorage.getItem("moves");
  sessionStorage.setItem("moves", parseInt(moves) + 1);

  task_status = "todo";
  const data = {
    id: id,
    status: task_status,
  };
  const response = await fetch("../api/task.php", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });

  await loadAllTasks();

  const lastChanged = document.getElementById("lastChanged");
  const urlParams = new URLSearchParams(window.location.search);
  let developerName = urlParams.get("name");
  lastChanged.innerText = "Last updated by: " + developerName;
}

async function moveInprogress(id) {
  const moves = sessionStorage.getItem("moves");
  sessionStorage.setItem("moves", parseInt(moves) + 1);

  task_status = "in_progress";
  const data = {
    id: id,
    status: task_status,
  };
  const response = await fetch("../api/task.php", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });

  await loadAllTasks();

  const lastChanged = document.getElementById("lastChanged");
  const urlParams = new URLSearchParams(window.location.search);
  let developerName = urlParams.get("name");
  lastChanged.innerText = "Last updated by: " + developerName;
}

async function moveDone(id) {
  const moves = sessionStorage.getItem("moves");
  sessionStorage.setItem("moves", parseInt(moves) + 1);

  task_status = "done";
  const data = {
    id: id,
    status: task_status,
  };
  const response = await fetch("../api/task.php", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });

  await loadAllTasks();

  const lastChanged = document.getElementById("lastChanged");
  const urlParams = new URLSearchParams(window.location.search);
  let developerName = urlParams.get("name");
  lastChanged.innerText = "Last updated by: " + developerName;
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

document.addEventListener("DOMContentLoaded", () => {
  const urlParams = new URLSearchParams(window.location.search);
  let developerName = urlParams.get("name");

  if (!developerName) {
    window.location.href = "index.php";
  }

  loadAllTasks();
  setInterval(loadAllTasks, 1000);

  // const viewAllProjects = document.getElementById("viewAllProjects");
  // viewAllProjects.onclick = loadAllProjects;

  // const viewMyProjects = document.getElementById("viewMyProjects");
  // viewMyProjects.onclick = () => loadMyProjects(developerName);

  // const viewAllSDE = document.getElementById("viewAllSDE");
  // viewAllSDE.onclick = () => loadFilteredDevelopers();

  // const addSDE = document.getElementById("addSDE");
  // addSDE.onclick = () => {
  //   window.location.href = "add_dev.php";
  // };
});
