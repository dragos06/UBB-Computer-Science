async function loginFunc() {
  const form = document.getElementById("loginForm");

  form.addEventListener("submit", async (event) => {
    event.preventDefault();

    const formData = new FormData(form);
    console.log(formData);
    const name = formData.get("name");

    const dataJson ={
        name: name
    }

    const response = await fetch("../api/login.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(dataJson),
    });

    const data = await response.json();

    if (data.success) {
      window.location.href = `home.php?name=${name}`;
      sessionStorage.setItem("moves", 0);
    }
  });
}

document.addEventListener("DOMContentLoaded", () => {
  loginFunc();
});
