<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 3:31 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<
<%@ page session="true" %>
<%
    String user = (String) session.getAttribute("user");
    if (user == null) {
        response.sendRedirect("index.html");
        return;
    }
%>
<html>
<head>
    <title>Add Article</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>Add Article</h1>
<label>Journal Name: <input type="text" id="journalInput"/></label>
<label>Summary: <input type="text" id="summaryInput"/></label>
<button id="submitArticle" onclick="submitArticle()">Submit Article</button>

<script>
    function submitArticle() {
        const journalInput = document.getElementById("journalInput").value;
        const summaryInput = document.getElementById("summaryInput").value;

        $.ajax({
            url: "ArticleController",
            method: "POST",
            data: {
                journal: journalInput,
                user: "<%=user%>",
                summary: summaryInput
            },
            success: function () {
                alert("Article Added!");
                window.location.href = "success.jsp";
            },
            error: function () {
                alert("Failed to add article.");
            }
        })
    }
</script>
</body>
</html>
