package webubb.controller;

import java.io.IOException;

import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import webubb.domain.Author;
import webubb.model.DBManager;

public class LoginController extends HttpServlet{

    public LoginController(){
        super();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String author_name = request.getParameter("author");
        String creation = request.getParameter("creation");
        RequestDispatcher rd = null;

        DBManager dbmanager = new DBManager();
        Author author = dbmanager.authenticate(author_name, creation);
        if (author != null){
            rd = request.getRequestDispatcher("/success.jsp");
            HttpSession session = request.getSession();
            session.setAttribute("author", author);
        }
        else{
            rd = request.getRequestDispatcher("/error.jsp");
        }
        rd.forward(request, response);
    }
}
