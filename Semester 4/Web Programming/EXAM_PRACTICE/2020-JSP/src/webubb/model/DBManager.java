package webubb.model;

import webubb.domain.Article;
import webubb.domain.Author;
import webubb.domain.Document;
import webubb.domain.Movie;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;


public class DBManager {
    private Statement stmt;
    private Connection con;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/journals_db", "root", "");
            stmt = con.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public List<Article> getArticlesByUserAndJournal(String user, String journal) {
        ArrayList<Article> articles = new ArrayList<>();
        ResultSet rs;
        String query = "SELECT a.id, a.user, a.j_id, a.summary, a.date FROM articles a INNER JOIN journals j ON a.j_id = j.id WHERE a.user = ? AND j.name = ?";
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setString(1, user);
            ps.setString(2, journal);
            rs = ps.executeQuery();
            while (rs.next()) {
                articles.add(new Article(rs.getInt("id"), rs.getString("user"), rs.getInt("j_id"), rs.getString("summary"), rs.getDate("date")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return articles;
    }

    public Article addArticle(String journal, String user, String summary) {
        int r = 0;
        String select_journal = "SELECT id FROM journals WHERE name = ?";
        String insert_journal = "INSERT INTO journals(name) VALUES (?)";
        String insert_article = "INSERT INTO articles(user, j_id, summary) VALUES (?, ?, ?)";
        String select_article = "SELECT * FROM articles WHERE id = ?";
        Article article = null;
        ResultSet key_a = null;
        try {
            PreparedStatement ps1 = con.prepareStatement(select_journal);
            ps1.setString(1, journal);

            ResultSet rs1 = ps1.executeQuery();
            int j_id;
            if (rs1.next()) {
                j_id = rs1.getInt("id");
                PreparedStatement ps2 = con.prepareStatement(insert_article, Statement.RETURN_GENERATED_KEYS);
                ps2.setString(1, user);
                ps2.setInt(2, j_id);
                ps2.setString(3, summary);

                r = ps2.executeUpdate();
                key_a = ps2.getGeneratedKeys();
            } else {
                PreparedStatement ps2 = con.prepareStatement(insert_journal, Statement.RETURN_GENERATED_KEYS);
                ps2.setString(1, journal);
                int res = ps2.executeUpdate();
                if (res > 0) {
                    ResultSet keys = ps2.getGeneratedKeys();
                    if (keys.next()) {
                        j_id = keys.getInt(1);
                        PreparedStatement ps3 = con.prepareStatement(insert_article, Statement.RETURN_GENERATED_KEYS);
                        ps3.setString(1, user);
                        ps3.setInt(2, j_id);
                        ps3.setString(3, summary);

                        r = ps3.executeUpdate();
                        key_a = ps3.getGeneratedKeys();
                    } else {
                        throw new SQLException("Failed to retrieve journal ID");
                    }
                }
            }

            if (key_a != null) {
                if (key_a.next()) {
                    PreparedStatement ps4 = con.prepareStatement(select_article);
                    ps4.setInt(1, key_a.getInt(1));

                    ResultSet rs = ps4.executeQuery();
                    if (rs.next()) {
                        article = new Article(rs.getInt("id"), rs.getString("user"), rs.getInt("j_id"), rs.getString("summary"), rs.getDate("date"));
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return article;
    }


    public Author authenticate(String author, String creation) {
        ResultSet rs;
        String query = "SELECT * FROM authors WHERE name = ? AND (document_list LIKE ? OR movie_list LIKE ?)";
        Author a = null;
        try (PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, author);
            ps.setString(2, "%" + creation + "%");
            ps.setString(3, "%" + creation + "%");

            rs = ps.executeQuery();
            if (rs.next()) {
                a = new Author(rs.getInt("id"), rs.getString("name"), rs.getString("document_list"), rs.getString("movie_list"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return a;
    }

    public boolean addDocument(Author a, Document d) {
        int r = 0;
        String insert_query = "INSERT INTO documents(name, contents) VALUES (?, ?)";
        String update_query = "UPDATE authors SET document_list = CONCAT(document_list, ', ', ?) WHERE id = ?";
        try {
            PreparedStatement ps1 = con.prepareStatement(insert_query);
            ps1.setString(1, d.getName());
            ps1.setString(2, d.getContents());

            PreparedStatement ps2 = con.prepareStatement(update_query);
            ps2.setString(1, d.getName());
            ps2.setString(2, Integer.toString(a.getId()));

            r = ps1.executeUpdate() + ps2.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r > 1;
    }

    public Document getDocumentByName(String name) {
        Document document = null;
        ResultSet rs;
        String query = "SELECT * FROM documents WHERE name = ?";
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setString(1, name);
            rs = ps.executeQuery();
            if (rs.next()) {
                document = new Document(rs.getInt("id"), rs.getString("name"), rs.getString("contents"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return document;
    }

    public Movie getMovieByName(String title) {
        Movie movie = null;
        ResultSet rs;
        String query = "SELECT * FROM movies WHERE title = ?";
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setString(1, title);
            rs = ps.executeQuery();
            if (rs.next()) {
                movie = new Movie(rs.getInt("id"), rs.getString("title"), rs.getInt("duration"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movie;
    }

    public boolean deleteMovie(int id) {
        int r1 = 0;
        int r2 = 0;
        String delete_query = "DELETE FROM movies WHERE id = ?";
        String select_query = "SELECT title FROM movies WHERE id = ?";
        String movieName = new String();
        String select_authors = "SELECT id, movie_list FROM authors WHERE movie_list LIKE ?";
        String update_authors = "UPDATE authors SET movie_list = ? WHERE id = ?";
        String newMovieList = "";
        try {
            PreparedStatement ps1 = con.prepareStatement(select_query);
            ps1.setInt(1, id);
            ResultSet rs1 = ps1.executeQuery();
            if (rs1.next()) {
                movieName = rs1.getString("title");
            }

            PreparedStatement ps2 = con.prepareStatement(delete_query);
            ps2.setInt(1, id);
            r1 = ps2.executeUpdate();

            PreparedStatement ps3 = con.prepareStatement(select_authors);
            ps3.setString(1, "%" + movieName + "%");
            ResultSet rs3 = ps3.executeQuery();

            while (rs3.next()) {
                int authorId = rs3.getInt("id");
                String movie_list = rs3.getString("movie_list");
                String finalMovieName = movieName;
                newMovieList = Arrays.stream(movie_list.split(", "))
                        .filter(m -> !m.equals(finalMovieName)).
                        collect(Collectors.joining(", "));

                PreparedStatement ps4 = con.prepareStatement(update_authors);
                ps4.setString(1, newMovieList);
                ps4.setInt(2, authorId);
                r2 = ps4.executeUpdate();
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r1 > 0;
    }

    public Author getAuthorById(int id) {
        Author a = null;
        ResultSet rs;
        String query = "SELECT * FROM authors WHERE id = ?";
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setInt(1, id);
            rs = ps.executeQuery();
            if (rs.next()) {
                a = new Author(rs.getInt("id"), rs.getString("name"), rs.getString("document_list"), rs.getString("movie_list"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return a;
    }

    public Document getBestDocument() {
        Document document = null;
        ResultSet rs1;
        ResultSet rs2;
        String select_docs = "SELECT * FROM documents";
        String select_authors = "SELECT COUNT(*) AS count FROM authors WHERE document_list LIKE ?";
        int maxCount = 0;
        try {
            PreparedStatement ps1 = con.prepareStatement(select_docs);
            rs1 = ps1.executeQuery();
            while (rs1.next()) {
                int count = 0;
                PreparedStatement ps2 = con.prepareStatement(select_authors);
                String documentName = rs1.getString("name");
                ps2.setString(1, "%" + documentName + "%");
                rs2 = ps2.executeQuery();
                if (rs2.next()) {
                    count = rs2.getInt("count");
                    if (count > maxCount) {
                        maxCount = count;
                        document = new Document(rs1.getInt("id"), rs1.getString("name"), rs1.getString("contents"));
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return document;
    }

//    public ArrayList<Topic> getTopics() {
//        ArrayList<Topic> topics = new ArrayList<>();
//        ResultSet rs;
//
//        try {
//            rs = stmt.executeQuery("SELECT * FROM topics");
//            while (rs.next()) {
//                topics.add(new Topic(rs.getInt("id"), rs.getString("title"), rs.getInt("user_id")));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return topics;
//    }
//
//    public ArrayList<Post> getTopicPosts(int id) {
//        ArrayList<Post> posts = new ArrayList<>();
//        ResultSet rs;
//
//        try {
//            rs = stmt.executeQuery("SELECT * FROM posts WHERE topic_id=" + id);
//            while (rs.next()) {
//                posts.add(new Post(rs.getInt("id"), rs.getString("content"), rs.getInt("user_id"), rs.getInt("topic_id"), rs.getString("username")));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return posts;
//    }
//
//
//    public boolean addPost(Post post) {
//        int r = 0;
//        try {
//            r = stmt.executeUpdate("INSERT INTO posts (content, user_id, topic_id, username) VALUES('" + post.getContent() + "', " + post.getUserId() + ", " + post.getTopicId() + ", '" + post.getUsername() + "')");
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return r > 0;
//    }
//
//    public boolean deletePost(int id) {
//        int r = 0;
//        try {
//            r = stmt.executeUpdate("DELETE FROM posts WHERE id=" + id);
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return r > 0;
//    }
//
//    public Topic getTopicById(int id) {
//        Topic topic = null;
//        ResultSet rs;
//
//        try {
//            rs = stmt.executeQuery("SELECT * FROM topics WHERE id=" + id);
//            if (rs.next()) {
//                topic = new Topic(rs.getInt("id"), rs.getString("title"), rs.getInt("user_id"));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return topic;
//    }
}
