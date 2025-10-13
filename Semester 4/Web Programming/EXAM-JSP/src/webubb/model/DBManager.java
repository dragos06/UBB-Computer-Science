package webubb.model;

import webubb.domain.*;

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
            con = DriverManager.getConnection("jdbc:mysql://localhost/exam_db", "root", "");
            stmt = con.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, int password) {
        ResultSet rs;
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        User u = null;
        try (PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, username);
            ps.setInt(2, password);

            rs = ps.executeQuery();
            if (rs.next()) {
                u = new User(rs.getInt("id"), rs.getString("username"), rs.getInt("password"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public List<Room> getRoomsByDates(Date checkin, Date checkout) {
        List<Room> rooms = new ArrayList<>();
        ResultSet rs;
        String query = """
                SELECT * FROM rooms
                WHERE id NOT IN (
                    SELECT room_id FROM reservations
                    WHERE NOT (checkout <= ? OR checkin >= ?)
                )
                """;
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setDate(1, checkin);
            ps.setDate(2, checkout);
            rs = ps.executeQuery();
            while (rs.next()) {
                rooms.add(new Room(rs.getInt("id"), rs.getString("number"), rs.getInt("capacity"), rs.getInt("price")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rooms;
    }

    public boolean addReservation(Reservation reservation) {
        int r = 0;
        String insert_query = "INSERT INTO reservations(user_id, room_id, checkin, checkout, guests, price) VALUES (?, ?, ?, ?, ?, ?)";
        try {
            PreparedStatement ps1 = con.prepareStatement(insert_query);
            ps1.setInt(1, reservation.getUser_id());
            ps1.setInt(2, reservation.getRoom_id());
            ps1.setDate(3, (Date) reservation.getCheckin());
            ps1.setDate(4, (Date) reservation.getCheckout());
            ps1.setInt(5, reservation.getGuests());
            ps1.setInt(6, reservation.getPrice());

            r = ps1.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return r > 0;
    }

    public int getTotalPrice(Date checkin, Date checkout, int room_id, int user_id) {
        ResultSet rs;
        String queryPrice = "SELECT price FROM rooms WHERE id = ?";

        // Get free rooms: only those not having any overlapping reservation
        String freeRooms = """
                SELECT COUNT(*) AS free FROM rooms
                WHERE id NOT IN (
                    SELECT room_id FROM reservations
                    WHERE NOT (checkout <= ? OR checkin >= ?)
                )
                """;

        // Get total room count
        String totalRooms = "SELECT COUNT(*) AS total FROM rooms";

        // Check for overlapping reservations for the current user
        String userOverlapCheck = """
                SELECT COUNT(*) AS overlaps FROM reservations
                WHERE user_id = ? AND NOT (checkout <= ? OR checkin >= ?)
                """;

        try {
            // Step 1: Get base price
            PreparedStatement ps = con.prepareStatement(queryPrice);
            ps.setInt(1, room_id);
            rs = ps.executeQuery();
            if (!rs.next()) return -1;
            int base_price = rs.getInt("price");
            rs.close();

            // Step 2: Check for overlapping user reservations
            PreparedStatement psOverlap = con.prepareStatement(userOverlapCheck);
            psOverlap.setInt(1, user_id);
            psOverlap.setDate(2, checkin);
            psOverlap.setDate(3, checkout);
            ResultSet rOverlap = psOverlap.executeQuery();
            if (rOverlap.next() && rOverlap.getInt("overlaps") > 0) {
                System.out.println("User has overlapping reservation");
                return -1; // or throw exception / return -1 to signal user conflict
            }
            rOverlap.close();

            // Step 3: Get number of free rooms
            PreparedStatement ps1 = con.prepareStatement(freeRooms);
            ps1.setDate(1, checkin);
            ps1.setDate(2, checkout);
            ResultSet r1 = ps1.executeQuery();

            // Step 4: Get total rooms
            PreparedStatement ps2 = con.prepareStatement(totalRooms);
            ResultSet r2 = ps2.executeQuery();

            if (r1.next() && r2.next()) {
                int free = r1.getInt("free");
                int total = r2.getInt("total");
                int booked = total - free;
                float ratio = (float) booked / total;

                if (ratio <= 0.5f) {
                    return base_price;
                } else if (ratio <= 0.8f) {
                    return (int) (base_price * 1.2);
                } else {
                    return (int) (base_price * 1.5);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public int getNumberGuestsByDate(Date date) {
        int guests = 0;
        ResultSet rs;
        String query = """
                SELECT guests
                FROM reservations
                WHERE checkin <= ? AND ? <= checkout
                """;
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setDate(1, date);
            ps.setDate(2, date);
            rs = ps.executeQuery();
            while (rs.next()) {
                guests += rs.getInt("guests");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return guests;
    }

    public List<Reservation> getReservations(int userId) {
        List<Reservation> reservations = new ArrayList<>();
        ResultSet rs;
        String query = "SELECT * FROM reservations WHERE user_id = ?";
        try {
            PreparedStatement ps = con.prepareStatement(query);
            ps.setInt(1, userId);
            rs = ps.executeQuery();
            while (rs.next()) {
                reservations.add(new Reservation(rs.getInt("id"), rs.getInt("user_id"), rs.getInt("room_id"), rs.getDate("checkin"), rs.getDate("checkout"), rs.getInt("guests"), rs.getInt("price")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reservations;
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
