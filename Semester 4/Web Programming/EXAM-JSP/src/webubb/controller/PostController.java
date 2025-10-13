//package webubb.controller;
//
//import jakarta.servlet.ServletException;
//import jakarta.servlet.http.HttpServlet;
//import jakarta.servlet.http.HttpServletRequest;
//import jakarta.servlet.http.HttpServletResponse;
//import org.json.simple.JSONArray;
//import org.json.simple.JSONObject;
//import webubb.model.DBManager;
//
//import java.io.IOException;
//import java.io.PrintWriter;
//import java.util.ArrayList;
//
//public class PostController extends HttpServlet {
//    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        response.setContentType("application/json");
//        int topic_id = Integer.parseInt(request.getParameter("topic_id"));
//        DBManager db = new DBManager();
//        ArrayList<Post> posts = db.getTopicPosts(topic_id);
//        JSONArray jsonPosts = new JSONArray();
//        for(Post post : posts){
//            JSONObject jObj = new JSONObject();
//            jObj.put("id", post.getId());
//            jObj.put("content", post.getContent());
//            jObj.put("user_id", post.getUserId());
//            jObj.put("topic_id", post.getTopicId());
//            jObj.put("username", post.getUsername());
//            jsonPosts.add(jObj);
//        }
//        PrintWriter out = new PrintWriter(response.getOutputStream());
//        out.println(jsonPosts.toJSONString());
//        out.flush();
//    }
//
//    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        response.setContentType("application/json");
//        PrintWriter out = response.getWriter();
//
//        String content = request.getParameter("content");
//        int user_id = Integer.parseInt(request.getParameter("user_id"));
//        int topic_id = Integer.parseInt(request.getParameter("topic_id"));
//        String username = request.getParameter("username");
//
//        DBManager db = new DBManager();
//        Post post = new Post(0, content, user_id, topic_id, username);
//        boolean result = db.addPost(post);
//
//        JSONObject jObj = new JSONObject();
//        jObj.put("success", result);
//
//        out.println(jObj.toJSONString());
//        out.flush();
//    }
//
//    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        response.setContentType("application/json");
//        PrintWriter out = response.getWriter();
//
//        int post_id = Integer.parseInt(request.getParameter("id"));
//
//        DBManager db = new DBManager();
//        boolean result = db.deletePost(post_id);
//
//        JSONObject jObj = new JSONObject();
//        jObj.put("success", result);
//
//        out.println(jObj.toJSONString());
//        out.flush();
//
//    }
//}
