<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/22/2025
  Time: 10:11 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="webubb.domain.Author" %>
<%@ page session="true" %>
<%
    Author a = (Author) session.getAttribute("author");
    if (a == null) {
        response.sendRedirect("index.html");
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <title>Author Creations</title>
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
<h2>Welcome, <%= a.getName() %>!</h2>

<div style="display: flex; flex-direction: column; justify-content: space-between">
    <button id="addDocument" onclick="addDocument()">Add Document</button>
    <button id="viewMyCreations" onclick="viewMyCreations()">View My Creations</button>
    <button id="viewMostAuthoredDocument" onclick="viewMostAuthoredDocument()">View Most Authored Document</button>
</div>

<script>
    function addDocument(){
        window.location.href="add_document.jsp";
    }

    function viewMyCreations(){
        window.location.href="view_creations.jsp";
    }

    function viewMostAuthoredDocument(){
        window.location.href="best_document.jsp"
    }
</script>
</body>
</html>

