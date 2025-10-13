using WP_Lab10.Models;
using MySql.Data.MySqlClient;
using static Org.BouncyCastle.Bcpg.Attr.ImageAttrib;
using System.Reflection.Metadata;

namespace WP_Lab10.DataAbstractionLayer
{
    public class DAL
    {
        private MySqlConnection conn;
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=reservation_db";

        public List<Flight> GetFlights(DateOnly date, String city)
        {
            List<Flight> flist = new List<Flight>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM flights WHERE f_date = @Date AND f_destination_city = @City AND f_available_seats > 0";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Date", date.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@City", city);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    Flight flight = new Flight
                    {
                        Id = myreader.GetInt32("f_id"),
                        Date = DateOnly.FromDateTime(myreader.GetDateTime("f_date")),
                        City = myreader.GetString("f_destination_city"),
                        Seats = myreader.GetInt32("f_available_seats")
                    };

                    flist.Add(flight);
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return flist;
        }

        public Flight GetFlightById(int id)
        {
            Flight flight = new Flight();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM flights WHERE f_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Id", id);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    flight = new Flight
                    {
                        Id = myreader.GetInt32("f_id"),
                        Date = DateOnly.FromDateTime(myreader.GetDateTime("f_date")),
                        City = myreader.GetString("f_destination_city"),
                        Seats = myreader.GetInt32("f_available_seats")
                    };
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return flight;
        }

        public List<Hotel> GetHotels(DateOnly date, String city)
        {
            List<Hotel> hlist = new List<Hotel>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM hotels WHERE h_date = @Date AND h_city = @City AND h_available_rooms > 0";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Date", date.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@City", city);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    Hotel hotel = new Hotel
                    {
                        Id = myreader.GetInt32("h_id"),
                        Name = myreader.GetString("h_name"),
                        Date = DateOnly.FromDateTime(myreader.GetDateTime("h_date")),
                        City = myreader.GetString("h_city"),
                        Rooms = myreader.GetInt32("h_available_rooms")
                    };

                    hlist.Add(hotel);
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return hlist;
        }

        public Hotel GetHotelById(int id)
        {
            Hotel hotel = new Hotel();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM hotels WHERE h_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Id", id);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    hotel = new Hotel
                    {
                        Id = myreader.GetInt32("h_id"),
                        Name = myreader.GetString("h_name"),
                        Date = DateOnly.FromDateTime(myreader.GetDateTime("h_date")),
                        City = myreader.GetString("h_city"),
                        Rooms = myreader.GetInt32("h_available_rooms")
                    };
                }
                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return hotel;
        }

        public Reservation AddReservation(Reservation reservation)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "INSERT INTO reservations (r_person, r_type, id_reserved_resource) VALUES (@Person, @Type, @ResourceId); SELECT LAST_INSERT_ID();";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Person", reservation.Person);
                cmd.Parameters.AddWithValue("@Type", reservation.Type);
                cmd.Parameters.AddWithValue("@ResourceId", reservation.ResourceId);

                var insertedId = Convert.ToInt32(cmd.ExecuteScalar());
                reservation.Id = insertedId;

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }

            return reservation;
        }

        public Reservation GetReservationById(int id)
        {
            Reservation reservation = new Reservation();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM reservations WHERE r_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Id", id);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    reservation = new Reservation
                    {
                        Id = myreader.GetInt32("r_id"),
                        Person = myreader.GetString("r_person"),
                        Type = myreader.GetString("r_type"),
                        ResourceId = myreader.GetInt32("id_reserved_resource")
                    };
                }
                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return reservation;
        }

        public void UpdateFlight(Flight flight)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "UPDATE flights SET f_date = @Date, f_destination_city = @City, f_available_seats = @Seats WHERE f_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Date", flight.Date.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@City", flight.City);
                cmd.Parameters.AddWithValue("@Seats", flight.Seats);
                cmd.Parameters.AddWithValue("@Id", flight.Id);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public void UpdateHotel(Hotel hotel)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "UPDATE hotels SET h_name = @Name, h_date = @Date, h_city = @City, h_available_rooms = @Rooms WHERE h_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Name", hotel.Name);
                cmd.Parameters.AddWithValue("@Date", hotel.Date.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@City", hotel.City);
                cmd.Parameters.AddWithValue("@Rooms", hotel.Rooms);
                cmd.Parameters.AddWithValue("@Id", hotel.Id);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public void DeleteReservation(int id)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "DELETE FROM reservations WHERE r_id = @Id";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Id", id);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }
    }
}
