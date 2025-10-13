document.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("reservationForm");
  const list = document.getElementById("reservationList");

  const skierSelect = document.querySelector("select[name='skier_id']");
  const housingSelect = document.querySelector("select[name='housing_id']");

  function populateSelects() {
    fetch("../api/skier.php")
      .then((res) => res.json())
      .then((data) => {
        skierSelect.innerHTML = data
          .map((s) => `<option value="${s.id}">${s.name}</option>`)
          .join("");
      });

    fetch("../api/housing.php")
      .then((res) => res.json())
      .then((data) => {
        housingSelect.innerHTML = data
          .map((h) => `<option value="${h.id}">${h.name}</option>`)
          .join("");
      });
  }

  function loadReservations() {
    if (!list) return;
    fetch("../api/reservation.php")
      .then((res) => res.json())
      .then((data) => {
        list.innerHTML = "";
        data.forEach((r) => {
          const listItemDiv = document.createElement("div");
          listItemDiv.className = "listItemDiv";

          const li = document.createElement("li");
          li.textContent = `${r.skier_name} reserved ${r.housing_name} from ${r.start_date} to ${r.end_date}`;

          const del = document.createElement("button");
          del.textContent = "❌";
          del.onclick = () => {
            if (confirm("Delete this reservation?")) {
              fetch("../api/reservation.php", {
                method: "DELETE",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ id: r.id }),
              }).then(loadReservations);
            }
          };

          listItemDiv.appendChild(li);
          listItemDiv.appendChild(del);

          list.appendChild(listItemDiv);
        });
      });
  }

  if (form) {
    form.onsubmit = (e) => {
      e.preventDefault();
      const data = Object.fromEntries(new FormData(form));
      const startDate = new Date(data.start_date);
      const endDate = new Date(data.end_date);
      const today = new Date();
      today.setHours(0, 0, 0, 0);

      if (startDate < today) {
        alert("Start date cannot be in the past.");
        return;
      }

      if (endDate <= startDate) {
        alert("End date must be after the start date.");
        return;
      }

      fetch("../api/reservation.php", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(data),
      }).then(() => {
        alert("Reservation added.");
        form.reset();
        loadReservations();
      });
    };
  }

  backButton.onclick = () => {
    window.location.replace("../pages/index.php");
  };

  populateSelects();
  loadReservations();
});
