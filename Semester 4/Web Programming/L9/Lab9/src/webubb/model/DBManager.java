package webubb.model;

import webubb.domain.User;
import webubb.domain.Topic;
import webubb.domain.Post;

import java.sql.*;
import java.util.ArrayList;


public class DBManager {
    private Statement stmt;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/forum_app", "root", "");
            stmt = con.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {
        ResultSet rs;
        User u = null;
        System.out.println(username + " " + password);
        try {
            rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                u = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public ArrayList<Topic> getTopics() {
        ArrayList<Topic> topics = new ArrayList<>();
        ResultSet rs;

        try {
            rs = stmt.executeQuery("SELECT * FROM topics");
            while (rs.next()) {
                topics.add(new Topic(rs.getInt("id"), rs.getString("title"), rs.getInt("user_id")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return topics;
    }

    public ArrayList<Post> getTopicPosts(int id) {
        ArrayList<Post> posts = new ArrayList<>();
        ResultSet rs;

        try{
            rs = stmt.executeQuery("SELECT * FROM posts WHERE topic_id=" + id);
            while(rs.next()){
                posts.add(new Post(rs.getInt("id"), rs.getString("content"), rs.getInt("user_id"), rs.getInt("topic_id"), rs.getString("username")));
            }
            rs.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }
        return posts;
    }

    public boolean addTopic(Topic topic) {
        int r = 0;
        try {
            r = stmt.executeUpdate("INSERT INTO topics (title, user_id) VALUES('" + topic.getTitle() + "', '" + topic.getUserId() + "')");
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r > 0;
    }

    public boolean addPost(Post post) {
        int r = 0;
        try {
            r = stmt.executeUpdate("INSERT INTO posts (content, user_id, topic_id, username) VALUES('" + post.getContent() + "', " + post.getUserId() + ", " + post.getTopicId() + ", '" + post.getUsername() + "')");
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r > 0;
    }

    public boolean deletePost(int id) {
        int r = 0;
        try{
            r = stmt.executeUpdate("DELETE FROM posts WHERE id=" + id);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r > 0;
    }

    public Topic getTopicById(int id) {
        Topic topic = null;
        ResultSet rs;

        try{
            rs = stmt.executeQuery("SELECT * FROM topics WHERE id=" + id);
            if (rs.next()){
               topic =  new Topic(rs.getInt("id"), rs.getString("title"), rs.getInt("user_id"));
            }
            rs.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }
        return topic;
    }
}
