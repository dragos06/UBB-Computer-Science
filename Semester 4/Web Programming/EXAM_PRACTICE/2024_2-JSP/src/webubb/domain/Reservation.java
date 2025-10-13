package webubb.domain;

import java.util.Date;

public class Reservation {
    private int id;
    private int user_id;
    private int room_id;
    private Date checkin;
    private Date checkout;
    private int guests;
    private int price;

    public Reservation(int id, int user_id, int room_id, Date checkin, Date checkout, int guests, int price) {
        this.id = id;
        this.user_id = user_id;
        this.room_id = room_id;
        this.checkin = checkin;
        this.checkout = checkout;
        this.guests = guests;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getUser_id() {
        return user_id;
    }

    public void setUser_id(int user_id) {
        this.user_id = user_id;
    }

    public int getRoom_id() {
        return room_id;
    }

    public void setRoom_id(int room_id) {
        this.room_id = room_id;
    }

    public Date getCheckin() {
        return checkin;
    }

    public void setCheckin(Date checkin) {
        this.checkin = checkin;
    }

    public Date getCheckout() {
        return checkout;
    }

    public void setCheckout(Date checkout) {
        this.checkout = checkout;
    }

    public int getGuests() {
        return guests;
    }

    public void setGuests(int guests) {
        this.guests = guests;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
