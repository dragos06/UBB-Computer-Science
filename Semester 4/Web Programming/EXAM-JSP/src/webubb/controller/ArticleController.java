//package webubb.controller;
//
//import jakarta.servlet.ServletException;
//import jakarta.servlet.http.HttpServlet;
//import jakarta.servlet.http.HttpServletRequest;
//import jakarta.servlet.http.HttpServletResponse;
//import jakarta.servlet.http.HttpSession;
//import org.json.simple.JSONArray;
//import org.json.simple.JSONObject;
//import webubb.domain.Article;
//import webubb.domain.Author;
//import webubb.model.DBManager;
//
//import java.io.IOException;
//import java.io.PrintWriter;
//import java.util.List;
//
//public class ArticleController extends HttpServlet {
//    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        response.setContentType("application/json");
//        PrintWriter out = response.getWriter();
//
//        String action = request.getParameter("action");
//        if ((action != null) && (action.equals("getByUserAndJournal"))) {
//            String user = request.getParameter("user");
//            String journal = request.getParameter("journal");
//
//            DBManager db = new DBManager();
//            List<Article> articles = db.getArticlesByUserAndJournal(user, journal);
//
//            JSONArray jsonArray = new JSONArray();
//            for (Article article : articles) {
//                JSONObject json = new JSONObject();
//                json.put("id", article.getId());
//                json.put("user", article.getUser());
//                json.put("j_id", article.getJ_id());
//                json.put("summary", article.getSummary());
//                json.put("date", article.getDate().toString());
//                jsonArray.add(json);
//            }
//            out.println(jsonArray.toJSONString());
//            out.flush();
//        }
//    }
//
//    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        response.setContentType("application/json");
//        PrintWriter out = response.getWriter();
//
//        String journal = request.getParameter("journal");
//        String user = request.getParameter("user");
//        String summary = request.getParameter("summary");
//
//        DBManager db = new DBManager();
//        Article article = db.addArticle(journal, user, summary);
//
//        JSONObject json = new JSONObject();
//        json.put("id", article.getId());
//        json.put("user", article.getUser());
//        json.put("j_id", article.getJ_id());
//        json.put("summary", article.getSummary());
//        json.put("date", article.getDate().toString());
//        out.println(json.toJSONString());
//        out.flush();
//    }
//}
