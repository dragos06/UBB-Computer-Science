<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 6/15/2025
  Time: 4:44 PM
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
    <title>View Creations</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
<h1>My Creations</h1>
<div id="creationContainer"></div>

<script>
    async function loadCreations() {
        const creationContainer = document.getElementById("creationContainer");
        creationContainer.innerHTML = "";

        let document_list = "<%=a.getDocumentList()%>";
        let movie_list = "<%=a.getMovieList()%>";
        let documents = [];
        if (document_list !== "") {
            documents = document_list.split(", ");
        }

        let movies = [];
        if (movie_list !== "") {
            movies = movie_list.split(", ");
        }

        const documents_len = documents.length;
        const movies_len = movies.length;

        let i = 0;
        let j = 0;

        while (i < documents_len || j < movies_len) {
            if (i < documents_len) {
                try {
                    const response = await fetch(`DocumentController?action=getByName&name=\${documents[i]}`);
                    const data = await response.json();

                    const documentDetails = document.createElement("div");
                    documentDetails.innerHTML = `
                        <h2>Name: \${data.name}</h2>
                        <p>Contents: \${data.contents}</p>
                        `
                    creationContainer.appendChild(documentDetails);

                    i++;
                } catch (error) {
                    console.error("Error fetching documents");
                }

            }
            if (j < movies_len) {
                try {
                    const response = await fetch(`MovieController?action=getByName&title=\${movies[j]}`);
                    const data = await response.json();

                    const movieDetails = document.createElement("div");
                    movieDetails.innerHTML = `
                        <h2>Title: \${data.title}</h2>
                        <p>Duration: \${data.duration}</p>
                        <button style="display:block" onclick="deleteMovie(\${data.id})">X</button>
                        `
                    creationContainer.appendChild(movieDetails);
                    j++;
                } catch (error) {
                    console.error("Error fetching movies");
                }

            }
        }
    }

    async function deleteMovie(movie_id) {
        const response = await fetch(`MovieController?id=\${movie_id}`, {
            method: "DELETE"
        })
        if (response.ok) {
            const refreshed = await fetch("AuthorController?action=updateSessionAuthor&id=<%=a.getId()%>");
            if (refreshed.ok) {
                location.reload();
            }
        }
    }

    $(document).ready(function () {
        loadCreations();
    })
</script>
</body>
</html>
