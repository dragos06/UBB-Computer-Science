using WP_Lab10.Models;
using MySql.Data.MySqlClient;
using static Org.BouncyCastle.Bcpg.Attr.ImageAttrib;
using System.Reflection.Metadata;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace WP_Lab10.DataAbstractionLayer
{
    public class DAL
    {
        private MySqlConnection conn;
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=feedback_db";

        public Customer GetCustomer(string name, string email)
        {
            Customer customer = new Customer();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM Customer WHERE name = @Name and email = @Email";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Name", name);
                cmd.Parameters.AddWithValue("@Email", email);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    customer = new Customer
                    {
                        Id = myreader.GetInt32("id"),
                        Name = myreader.GetString("name"),
                        Email = myreader.GetString("email")
                    };
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return customer;
        }

        public List<Feedback> GetFeedbacks()
        {
            List<Feedback> flist = new List<Feedback>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM feedback";
                cmd.CommandText = query;

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    Feedback feedback = new Feedback
                    {
                        Id = myreader.GetInt32("id"),
                        CustomerId = myreader.GetInt32("customerId"),
                        Message = myreader.GetString("message"),
                        Timestamp = myreader.GetDateTime("timestamp")
                    };

                    flist.Add(feedback);
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

        public bool AddFeedback(int customerId, string message)
        {
            var id = 0;
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "INSERT INTO feedback (customerId, message) VALUES (@CustomerId, @Message); SELECT LAST_INSERT_ID()";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@CustomerId", customerId);
                cmd.Parameters.AddWithValue("@Message", message);

                id = Convert.ToInt32(cmd.ExecuteScalar());

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }

            return id != 0;
        }

        public List<string> VerifyFeedback(string message)
        {
            List<string> words = new List<string>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT pattern FROM blockedwords WHERE @Message LIKE CONCAT('%', pattern, '%')";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Message", message);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    words.Add(myreader.GetString("pattern"));
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return words;
        }

        public List<Channel> GetChannelsByPerson(string person)
        {
            List<Channel> clist = new List<Channel>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT c.id, c.owner_id, c.name, c.description, c.subscribers FROM channels c INNER JOIN persons p ON c.owner_id = p.id WHERE p.name = @Name";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Name", person);

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    Channel channel = new Channel
                    {
                        Id = myreader.GetInt32("id"),
                        OwnerId = myreader.GetInt32("owner_id"),
                        Name = myreader.GetString("name"),
                        Description = myreader.GetString("description"),
                        Subscribers = myreader.GetString("subscribers")
                    };

                    clist.Add(channel);
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return clist;
        }

        public List<Channel> GetSubscribedChannels(string name)
        {
            List<Channel> clist = new List<Channel>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM channels WHERE subscribers LIKE @Name";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Name", "%" + name + "%");

                MySqlDataReader myreader = cmd.ExecuteReader();
                while (myreader.Read())
                {
                    Channel channel = new Channel
                    {
                        Id = myreader.GetInt32("id"),
                        OwnerId = myreader.GetInt32("owner_id"),
                        Name = myreader.GetString("name"),
                        Description = myreader.GetString("description"),
                        Subscribers = myreader.GetString("subscribers")
                    };

                    clist.Add(channel);
                }

                myreader.Close();
                conn.Close();
            }
            catch (MySqlException e)
            {
                Console.Write(e.Message);
            }
            return clist;
        }

        public void AddSubscription(string name, string channel)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT COUNT(*) AS count FROM channels WHERE subscribers LIKE @Name AND name=@Channel";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Name", "%" + name + "%");
                cmd.Parameters.AddWithValue("@Channel", channel);

                MySqlDataReader myreader = cmd.ExecuteReader();
                int count = 0;
                while (myreader.Read())
                {
                    count = myreader.GetInt32("count");
                }
                myreader.Close();

                if (count == 0)
                {
                    query = "UPDATE channels SET subscribers = CONCAT(subscribers, ',', @Subscriber) WHERE name=@Channel";
                    cmd.CommandText = query;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@Subscriber", name + ":" + DateTime.Now.ToString("yyyy-MM-dd"));
                    cmd.Parameters.AddWithValue("@Channel", channel);
                    cmd.ExecuteNonQuery();
                }
                else
                {
                    query = "SELECT subscribers FROM channels WHERE name=@Channel";
                    cmd.CommandText = query;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@Channel", channel);

                    myreader = cmd.ExecuteReader();
                    string subscribers = "";
                    while (myreader.Read())
                    {
                        subscribers = myreader.GetString("subscribers");
                    }
                    myreader.Close();

                    List<string> subscribersList = subscribers.Split(",").ToList();
                    for (int i = 0; i < subscribersList.Count; i++)
                    {
                        if (subscribersList[i].StartsWith(name + ":"))
                        {
                            subscribersList[i] = name + ":" + DateTime.Now.ToString("yyyy-MM-dd");
                            break;
                        }
                    }

                    string updatedSubscribers = string.Join(",", subscribersList);

                    query = "UPDATE channels SET subscribers = @Subscribers WHERE name=@Channel";
                    cmd.CommandText = query;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@Subscribers", updatedSubscribers);
                    cmd.Parameters.AddWithValue("@Channel", channel);
                    cmd.ExecuteNonQuery();
                }

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }














        public List<Flight> GetFlights(DateOnly date, string city)
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

        public List<Hotel> GetHotels(DateOnly date, string city)
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
