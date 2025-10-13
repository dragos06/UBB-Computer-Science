<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/22/2025
  Time: 1:23 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="java.util.*" %>
<%@ page import="webubb.domain.User" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    User user = (User) session.getAttribute("user");
    int topicId = Integer.parseInt(request.getParameter("id"));
%>
<!DOCTYPE html>
<html>
<head>
    <title>Posts - </title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f8f9fa;
            margin: 0;
            padding: 20px;
            color: #343a40;
        }

        h2 {
            color: #495057;
        }

        button {
            background-color: #007bff;
            border: none;
            padding: 10px 20px;
            color: white;
            font-size: 14px;
            border-radius: 4px;
            cursor: pointer;
            margin-bottom: 15px;
        }

        button:hover {
            background-color: #0056b3;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            background-color: white;
            box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
        }

        th, td {
            padding: 12px;
            border-bottom: 1px solid #dee2e6;
            text-align: left;
        }

        th {
            background-color: #f1f3f5;
            font-weight: bold;
        }

        tr:hover {
            background-color: #f8f9fa;
        }

        .delete-btn {
            background-color: #dc3545;
            color: white;
            padding: 5px 10px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }

        .delete-btn:hover {
            background-color: #c82333;
        }
    </style>
</head>
<body>
<h2 id="topicTitle">Topic: </h2>

<button onclick="addPost()">Add Post</button>

<table border="1" id="postsTable">
    <thead>
    <tr>
        <th>User</th>
        <th>Content</th>
        <th></th>
    </tr>
    </thead>
    <tbody>
    <!-- Posts will be loaded here -->
    </tbody>
</table>

<script>
    const topicId = <%= topicId %>;

    function loadPosts() {
        $.ajax({
            url: 'PostController',
            method: 'GET',
            data: { topic_id: topicId },
            dataType: 'json',
            success: function (data) {
                const tbody = $("#postsTable tbody");
                tbody.empty();

                data.forEach((post) => {
                    const row = $("<tr>")
                    row.append($("<td>").text(post.username));
                    row.append($("<td>").text(post.content))
                    if (post.user_id === <%= user.getId() %>) {
                        row.append($("<td>").append($("<button>").text("Delete").on("click", function(){
                            deletePost(post.id);
                        })))
                    }
                    tbody.append(row);
                });
            },
            error: function () {
                alert("Failed to load posts.");
            }
        });
    }

    function addPost() {
        const content = prompt("Enter your post:");
        if (content) {
            $.ajax({
                url: 'PostController',
                method: 'POST',
                data: {
                    content: content,
                    user_id: <%= user.getId() %>,
                    topic_id: topicId,
                    username: "<%= user.getUsername() %>",
                },
                success: function () {
                    loadPosts();
                },
                error: function () {
                    alert("Failed to add post.");
                }
            });
        }
    }

    function deletePost(postId) {
        if (confirm("Are you sure you want to delete this post?")) {
            $.ajax({
                url: 'PostController?id=' + postId,
                method: 'DELETE',
                success: function () {
                    loadPosts();
                },
                error: function () {
                    alert("Failed to delete post.");
                }
            });
        }
    }

    function loadTopicTitle(){
        $.ajax({
            url: 'TopicController',
            method: 'GET',
            data:{
                action: 'getById',
                id: topicId,
            },
            success: function (data) {
                document.title = "Posts - " + data.title;
                $("#topicTitle").text("Topic: " + data.title);
            },
            error: function () {
                alert("Failed to load topic title.");
            }
        })
    }

    $(document).ready(function () {
        loadTopicTitle();
        loadPosts();
    });
</script>
</body>
</html>

