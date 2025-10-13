<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/22/2025
  Time: 10:11 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="webubb.domain.User" %>
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
    <title>Forum Topics</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 10px; border: 1px solid #ccc; text-align: left; }
        button { padding: 5px 10px; }
        #logout { float: right; }
        #addTopicForm { margin-top: 20px; }
        input[type="text"] { padding: 5px; width: 300px; }
    </style>
</head>
<body>
<h2>Welcome, <%= user.getUsername() %>!</h2>
<a id="logout" href="LogoutController">Logout</a>

<h3>Topics</h3>

<form id="addTopicForm">
    <label for="title">New Topic Title:</label>
    <input type="text" id="title" name="title" required />
    <button type="submit">Add Topic</button>
</form>

<table id="topicsTable">
    <thead>
    <tr>
        <th>Title</th>
        <th>Actions</th>
    </tr>
    </thead>
    <tbody>
    <!-- Topics will be loaded here -->
    </tbody>
</table>

<script>
    const userId = <%= user.getId() %>;

    function loadTopics() {
        $.ajax({
            url: 'TopicController',
            data: { action: 'getAll' },
            method: 'GET',
            success: function (data) {
                const tbody = $("#topicsTable tbody");
                tbody.empty();
                data.forEach((topic) => {
                    const row = $("<tr>");
                    row.append($("<td>").text(topic.title));
                    row.append($("<td>").append($("<button>").text("Enter").on("click", function() {
                        enterTopic(topic.id);
                    })));
                    tbody.append(row);
                });
            },
            error: function () {
                alert("Failed to load topics.");
            }
        });
    }

    function enterTopic(topicId) {
        window.location.href = "posts.jsp?id=" + topicId;
    }

    $(document).ready(function () {
        loadTopics();

        $("#addTopicForm").submit(function (e) {
            e.preventDefault();
            const title = $("#title").val().trim();
            if (title === "") {
                alert("Please enter a topic title.");
                return;
            }

            $.ajax({
                url: "TopicController",
                method: "GET",
                data: {
                    action: "add",
                    title: title,
                    userid: userId
                },
                success: function (response) {
                    alert(response.trim());
                    $("#title").val("");
                    loadTopics();
                },
                error: function () {
                    alert("Failed to add topic.");
                }
            });
        });
    });
</script>
</body>
</html>

