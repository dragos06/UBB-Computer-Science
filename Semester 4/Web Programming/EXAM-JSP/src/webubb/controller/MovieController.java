package webubb.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.json.simple.JSONObject;
import webubb.domain.Document;
import webubb.domain.Movie;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;

public class MovieController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if((action != null) && (action.equals("getByName"))) {
            String name = request.getParameter("title");

            DBManager db = new DBManager();
            Movie movie = db.getMovieByName(name);

            JSONObject jObj = new JSONObject();
            jObj.put("id", movie.getId());
            jObj.put("title", movie.getTitle());
            jObj.put("duration", movie.getDuration());

            out.println(jObj.toJSONString());
            out.flush();
        }
    }

    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        int id = Integer.parseInt(request.getParameter("id"));
        DBManager db = new DBManager();
        boolean result = db.deleteMovie(id);

        JSONObject jObj = new JSONObject();
        jObj.put("success", result);

        out.println(jObj.toJSONString());
        out.flush();
    }
}
