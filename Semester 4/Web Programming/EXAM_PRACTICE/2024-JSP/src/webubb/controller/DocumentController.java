package webubb.controller;

import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.json.simple.JSONObject;
import webubb.domain.Author;
import webubb.domain.Document;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;

public class DocumentController extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String name = request.getParameter("name");
        String contents = request.getParameter("contents");
        int id = Integer.parseInt(request.getParameter("id"));
        String authorName = request.getParameter("author_name");
        String documentList = request.getParameter("document_list");
        String movieList = request.getParameter("movie_list");

        Author author = new Author(id, authorName, documentList, movieList);
        Document document = new Document(0, name, contents);

        DBManager db = new DBManager();
        boolean result = db.addDocument(author, document);

        JSONObject jObj = new JSONObject();
        jObj.put("success", result);

        out.println(jObj.toJSONString());
        out.flush();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if((action != null) && (action.equals("getByName"))) {
            String name = request.getParameter("name");

            DBManager db = new DBManager();
            Document document = db.getDocumentByName(name);

            JSONObject jObj = new JSONObject();
            jObj.put("id", document.getId());
            jObj.put("name", document.getName());
            jObj.put("contents", document.getContents());

            out.println(jObj.toJSONString());
            out.flush();
        }
        else if((action != null) && (action.equals("bestDocument"))) {
            DBManager db = new DBManager();
            Document document = db.getBestDocument();
            JSONObject jObj = new JSONObject();
            jObj.put("id", document.getId());
            jObj.put("name", document.getName());
            jObj.put("contents", document.getContents());
            out.println(jObj.toJSONString());
            out.flush();
        }
    }
}
