<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 3:31 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="webubb.domain.Author" %>
<%@ page session="true" %>
<%
    Author a = (Author) session.getAttribute("author");
    if (a == null) {
        response.sendRedirect("index.html");
        return;
    }
%>
<html>
<head>
    <title>Add Document</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>Add Document</h1>
<label>Document Name: <input type="text" id="nameInput"/></label>
<label>Document Contents: <input type="text" id="contentsInput"/></label>
<button id="submitDocument" onclick="submitDocument()">Submit Document</button>

<script>
    function submitDocument() {
        const nameInput = document.getElementById("nameInput").value;
        const contentsInput = document.getElementById("contentsInput").value;

        $.ajax({
            url: "DocumentController",
            method: "POST",
            data: {
                name: nameInput,
                contents: contentsInput,
                id: <%=a.getId()%>,
                author_name: "<%=a.getName()%>",
                document_list: "<%=a.getDocumentList()%>",
                movie_list: "<%=a.getMovieList()%>"
            },
            success: function () {
                alert("Document Added!");
                window.location.href = "success.jsp";
            },
            error: function () {
                alert("Failed to add document.");
            }
        })
    }
</script>
</body>
</html>
