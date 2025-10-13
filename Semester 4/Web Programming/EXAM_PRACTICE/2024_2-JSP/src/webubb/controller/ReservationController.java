package webubb.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Document;
import webubb.domain.Reservation;
import webubb.domain.Room;
import webubb.model.DBManager;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;
import java.util.List;

public class ReservationController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if((action != null) && (action.equals("getGuestsByDate"))) {
            Date date = Date.valueOf(request.getParameter("date"));

            DBManager db = new DBManager();
            int guests = db.getNumberGuestsByDate(date);

            JSONObject jObj = new JSONObject();
            jObj.put("guests", guests);

            out.println(jObj.toJSONString());
            out.flush();
        }
        else if((action != null) && (action.equals("getReservations"))){
            int userId = Integer.parseInt(request.getParameter("user_id"));

            DBManager db = new DBManager();
            List<Reservation> reservations = db.getReservations(userId);

            JSONArray jsonArray = new JSONArray();
            for (Reservation reservation : reservations) {
                JSONObject json = new JSONObject();
                json.put("id", reservation.getId());
                json.put("user_id", reservation.getUser_id());
                json.put("room_id", reservation.getRoom_id());
                json.put("checkin", reservation.getCheckin().toString());
                json.put("checkout", reservation.getCheckout().toString());
                json.put("guests", reservation.getGuests());
                json.put("price", reservation.getPrice());
                jsonArray.add(json);
            }
            out.println(jsonArray.toJSONString());
            out.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");

        String action = request.getParameter("action");
        if ((action != null) && (action.equals("reserveRoom"))) {
            int user_id = Integer.parseInt(request.getParameter("user_id"));
            int room_id = Integer.parseInt(request.getParameter("room_id"));
            Date checkin = Date.valueOf(request.getParameter("checkin"));
            Date checkout = Date.valueOf(request.getParameter("checkout"));
            int guests = Integer.parseInt(request.getParameter("guests"));

            DBManager db = new DBManager();
            int price = db.getTotalPrice(checkin, checkout, room_id, user_id);

            PrintWriter out = response.getWriter();

            if (price == -1) {
                JSONObject jObj = new JSONObject();
                jObj.put("success", "false");

                out.println(jObj.toJSONString());
                out.flush();
            } else {
                Reservation reservation = new Reservation(0, user_id, room_id, checkin, checkout, guests, price);
                boolean result = db.addReservation(reservation);


                JSONObject jObj = new JSONObject();
                jObj.put("success", result);

                out.println(jObj.toJSONString());
                out.flush();
            }
        }
    }
}
