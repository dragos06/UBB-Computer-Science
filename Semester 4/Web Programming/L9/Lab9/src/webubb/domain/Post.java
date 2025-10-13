package webubb.domain;

public class Post {
    private int id;
    private String content;
    private int userId;
    private int topicId;
    private String username;

    public Post(int id, String content, int userId, int topicId, String username) {
        this.id = id;
        this.content = content;
        this.userId = userId;
        this.topicId = topicId;
        this.username = username;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public int getTopicId() {
        return topicId;
    }

    public void setTopicId(int topicId) {
        this.topicId = topicId;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }
}
