<%@ page import="webubb.domain.User" %><%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 4:44 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page session="true" %>
<%
    User user = (User) session.getAttribute("user");
    if (user == null) {
        response.sendRedirect("index.html");
        return;
    }
%>
<html>
<head>
    <title>View My Reservations</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>My Reservations</h1>
<div id="reservationContainer"></div>

<script>
    async function loadReservations() {
        const reservationContainer = document.getElementById("reservationContainer");
        reservationContainer.innerHTML = "";


        const user_id = "<%= user.getId()%>";
        const response = await fetch(`ReservationController?action=getReservations&user_id=\${user_id}`);
        const data = await response.json();

        data.forEach((reservation) => {
            const reservationDiv = document.createElement("div");
            reservationDiv.innerHTML = `
                <h2>ID: \${reservation.id}, User ID: \${reservation.user_id}, Room ID: \${reservation.room_id}</h2>
                <p>Checkin: \${reservation.checkin}</p>
                <p>Checkout: \${reservation.checkout}</p>
                <p>Guests: \${reservation.guests}</p>
                <p>Price: \${reservation.price}</p>
            `
            reservationContainer.appendChild(reservationDiv);
        })
    }

    $(document).ready(function () {
        loadReservations();
    })
</script>
</body>
</html>
