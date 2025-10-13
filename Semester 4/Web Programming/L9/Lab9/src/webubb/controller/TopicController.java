package webubb.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Topic;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class TopicController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if((action != null) && (action.equals("add"))) {
            Topic topic = new Topic(0, request.getParameter("title"), Integer.parseInt(request.getParameter("userid")));
            DBManager db = new DBManager();
            Boolean result = db.addTopic(topic);
            PrintWriter out = new PrintWriter(response.getOutputStream());
            if(result == true) {
                out.println("Add topic successful");
            }
            else{
                out.println("Add topic failed");
            }
            out.flush();
        }
        else if ((action != null) && (action.equals("getById"))) {
            int id = Integer.parseInt(request.getParameter("id"));
            DBManager db = new DBManager();
            Topic topic = db.getTopicById(id);

            if (topic != null) {
                response.setContentType("application/json");
                JSONObject jObj = new JSONObject();
                jObj.put("id", topic.getId());
                jObj.put("title", topic.getTitle());
                jObj.put("userid", topic.getUserId());

                PrintWriter out = new PrintWriter(response.getOutputStream());
                out.println(jObj.toJSONString());
                out.flush();
            }
            else{
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Topic not found");
            }
        }
        else if((action != null) && (action.equals("getAll"))) {
            response.setContentType("application/json");
            DBManager db = new DBManager();
            ArrayList<Topic> topics = db.getTopics();
            JSONArray jsonTopics = new JSONArray();
            for (Topic topic : topics) {
                JSONObject jObj = new JSONObject();
                jObj.put("id", topic.getId());
                jObj.put("title", topic.getTitle());
                jObj.put("userid", topic.getUserId());
                jsonTopics.add(jObj);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonTopics.toJSONString());
            out.flush();
        }
    }
}
