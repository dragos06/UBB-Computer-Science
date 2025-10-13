function loginFunc() {
    const form = document.getElementById("loginForm");
    
    form.addEventListener('submit', async (event) => {
        event.preventDefault();
        
        const formData = new FormData(form);
        console.log(formData);
        const name = formData.get("name");

        if(name){
            window.location.href = `home.php?name=${name}`;
        }
        else{
            alert("Please enter a name!");
        }
    })    
}

document.addEventListener("DOMContentLoaded", () => {
    loginFunc();
})