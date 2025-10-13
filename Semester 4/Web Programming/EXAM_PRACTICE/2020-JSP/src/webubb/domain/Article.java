package webubb.domain;

import java.util.Date;

public class Article {
    private int id;
    private String user;
    private int j_id;
    private String summary;
    private Date date;

    public Article(int id, String user, int j_id, String summary, Date date) {
        this.id = id;
        this.user = user;
        this.j_id = j_id;
        this.summary = summary;
        this.date = date;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public int getJ_id() {
        return j_id;
    }

    public void setJ_id(int j_id) {
        this.j_id = j_id;
    }

    public String getSummary() {
        return summary;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }
}
