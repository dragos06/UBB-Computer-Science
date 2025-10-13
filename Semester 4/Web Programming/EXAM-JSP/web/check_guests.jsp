<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 8:50 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Number Guests</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>Number Guests</h1>
<label>Date: <input type="date" id="dateInput"/></label>
<button id="searchButton">Search</button>
<label id="guestsNumber">Number of guests: </label>

<script>
    document.addEventListener("DOMContentLoaded", async () => {
        const searchButton = document.getElementById("searchButton");
        searchButton.addEventListener("click", async function () {
            const date = document.getElementById("dateInput").value;
            const response = await fetch(`ReservationController?action=getGuestsByDate&date=\${date}`);
            const data = await response.json();
            const guestsNumber = document.getElementById("guestsNumber");
            guestsNumber.textContent = "Number of guests: " + `\${data.guests}`;
        })
    });
</script>
</body>
</html>
