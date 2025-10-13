<%@ page import="webubb.domain.User" %><%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/22/2025
  Time: 10:11 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page session="true" %>
<%
    User user = (User) session.getAttribute("user");
    if (user == null) {
        response.sendRedirect("index.html");
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <title>Homepage</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 10px; border: 1px solid #ccc; text-align: left; }
        button { padding: 5px 10px; }
        input[type="text"] { padding: 5px; width: 300px; }
    </style>
</head>
<body>
<h2>Welcome!</h2>

<div style="display: flex; flex-direction: column; justify-content: space-between">
    <button id="reserveRoom" onclick="reserveRoom()">Reserve Room</button>
    <button id="checkGuests" onclick="checkGuests()">Check Guests</button>
    <button id="viewReservations" onclick="viewReservations()">View Reservations</button>
</div>

<script>
    function reserveRoom(){
        window.location.href="reserve_room.jsp";
    }

    function checkGuests(){
        window.location.href="check_guests.jsp";
    }

    function viewReservations(){
        window.location.href="view_reservations.jsp"
    }
</script>
</body>
</html>

