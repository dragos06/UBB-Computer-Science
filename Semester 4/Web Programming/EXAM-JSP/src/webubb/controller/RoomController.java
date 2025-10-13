package webubb.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Author;
import webubb.domain.Room;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;
import java.util.List;

public class RoomController extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");

        String action = request.getParameter("action");
        if ((action != null) && (action.equals("getRoomsByDate"))) {
            Date checkin = Date.valueOf(request.getParameter("checkin"));
            Date checkout = Date.valueOf(request.getParameter("checkout"));
            DBManager db = new DBManager();
            List<Room> rooms = db.getRoomsByDates(checkin, checkout);

            PrintWriter out = response.getWriter();

            JSONArray jsonArray = new JSONArray();
            for (Room room : rooms) {
                JSONObject json = new JSONObject();
                json.put("id", room.getId());
                json.put("number", room.getNumber());
                json.put("capacity", room.getCapacity());
                json.put("price", room.getPrice());
                jsonArray.add(json);
            }
            out.println(jsonArray.toJSONString());
            out.flush();
        }
    }
}
