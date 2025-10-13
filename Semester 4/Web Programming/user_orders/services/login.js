function loginFunc() {
    const form = document.getElementById("loginForm");
    
    form.addEventListener('submit', async (event) => {
        event.preventDefault();
        
        const formData = new FormData(form);
        console.log(formData);
        const name = formData.get("name");

        sessionStorage.setItem("username", name);

        if(name){
            window.location.href = "home.php";
        }
        else{
            alert("Please enter a name!");
        }
    })    
}

document.addEventListener("DOMContentLoaded", () => {
    loginFunc();
})