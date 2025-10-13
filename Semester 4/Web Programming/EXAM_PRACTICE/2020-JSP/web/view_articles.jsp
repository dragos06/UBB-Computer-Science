<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 4:44 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
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
    <title>View My Articles</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>My Creations</h1>
<label>Journal name: <input type="text" id="journalInput" placeholder="Journal name..."/></label>
<button id="searchArticles">Search</button>
<div id="articlesContainer"></div>

<script>
    async function loadArticles() {
        const articlesContainer = document.getElementById("articlesContainer");
        articlesContainer.innerHTML = "";

        const journal = document.getElementById("journalInput").value;
        const user = "<%= user%>";
        const response = await fetch(`ArticleController?action=getByUserAndJournal&user=\${user}&journal=\${journal}`);
        const data = await response.json();

        data.forEach((journal) => {
            const articleDiv = document.createElement("div");
            articleDiv.innerHTML = `
                <h2>ID: \${journal.id}</h2>
                <p>User: \${journal.user}</p>
                <p>Summary: \${journal.summary}</p>
                <p>Date: \${journal.date}</p>
            `
            articlesContainer.appendChild(articleDiv);
        })
    }

    $(document).ready(function () {
        const searchArticles = document.getElementById("searchArticles");
        searchArticles.addEventListener("click", loadArticles);
    })
</script>
</body>
</html>
