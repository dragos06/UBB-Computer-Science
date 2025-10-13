<%@ page import="webubb.domain.User" %><%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 3:31 PM
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
    <title>Reserve Room</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>Reserve Room</h1>
<label>Check-In Date: <input type="date" id="checkinDate"/></label>
<label>Check-Out Date: <input type="date" id="checkoutDate"/></label>
<button id="searchButton" onclick="searchRooms()">searchButton</button>
<div id="roomDiv"></div>


<script>
    function searchRooms() {
        const checkinDate = document.getElementById("checkinDate").value;
        const checkoutDate = document.getElementById("checkoutDate").value;

        $.ajax({
            url: "RoomController",
            method: "POST",
            data: {
                action: "getRoomsByDate",
                checkin: checkinDate,
                checkout: checkoutDate
            },
            success: function (data) {
                const roomDiv = document.getElementById("roomDiv");
                roomDiv.innerHTML = "";
                data.forEach((room) => {
                    const element = document.createElement("div");
                    element.innerHTML = `
                        <h2>Room Number: \${room.number}</h2>
                        <p>Capacity: \${room.capacity}</p>
                        <p>Price: \${room.price}</p>
                        <input type="number" id="guestsInput" placeholder="Number of guests..."/>
                        <button data-id=\${room.id} onclick="reserve(this)">Reserve</button>
                    `
                    roomDiv.appendChild(element);
                })
            },
            error: function () {
                alert("Failed to add article.");
            }
        })
    }

    function reserve(button) {
        const roomId = button.dataset.id;
        const userId = <%=user.getId()%>;
        const checkinDate = document.getElementById("checkinDate").value;
        const checkoutDate = document.getElementById("checkoutDate").value;
        const guests = button.previousElementSibling.value;

        $.ajax({
            url: "ReservationController",
            method: "POST",
            data: {
                action: "reserveRoom",
                user_id: userId,
                room_id: roomId,
                checkin: checkinDate,
                checkout: checkoutDate,
                guests: guests
            },
            success: function (response) {
                if (response.success === "false") {
                    alert("You already have an overlapping reservation.");
                } else {
                    alert("Reservation added!");
                    window.location.href = "success.jsp";
                }
            }
        })
    }
</script>
</body>
</html>
