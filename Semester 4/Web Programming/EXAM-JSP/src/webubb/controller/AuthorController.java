package webubb.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import webubb.domain.Author;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;

public class AuthorController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");

        String action = request.getParameter("action");
        if((action != null) && (action.equals("updateSessionAuthor"))) {
            int id = Integer.parseInt(request.getParameter("id"));
            DBManager db = new DBManager();
            Author newAuthor = db.getAuthorById(id);
            HttpSession session = request.getSession();
            session.setAttribute("author", newAuthor);
        }
    }
}
