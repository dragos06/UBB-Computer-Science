<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/22/2025
  Time: 10:11 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page session="true" %>
<%
    String user = (String) session.getAttribute("user");
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
    <button id="addArticle" onclick="addArticle()">Add Article</button>
    <button id="viewArticles" onclick="viewArticles()">View Articles</button>
    <button id="viewMostAuthoredDocument" onclick="viewMostAuthoredDocument()">View Most Authored Document</button>
</div>

<script>
    function addArticle(){
        window.location.href="add_article.jsp";
    }

    function viewArticles(){
        window.location.href="view_articles.jsp";
    }

    function viewMostAuthoredDocument(){
        window.location.href="best_document.jsp"
    }
</script>
</body>
</html>

