using Microsoft.AspNetCore.Mvc;
using System.Threading.Channels;
using WP_Lab10.DataAbstractionLayer;
using WP_Lab10.Models;

namespace WP_Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();

        private int? Id => HttpContext.Session.GetInt32("id");
        private string Name => HttpContext.Session.GetString("name");
        private string Email => HttpContext.Session.GetString("email");
        private int? Count => HttpContext.Session.GetInt32("badWords");

        public IActionResult Index()
        {
            if (Id == null || string.IsNullOrEmpty(Name) || string.IsNullOrEmpty(Email))
                return RedirectToAction("Login", "Auth");
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult ViewFeedbacks()
        {
            return View("ViewFeedbacks");
        }

        [HttpGet]
        public IActionResult GetFeedbacks()
        {
            List<Feedback> feedbacks = dal.GetFeedbacks();
            if (feedbacks.Count == 0)
            {
                return Content("<p>No feedbacks found.</p>");
            }
            var html = "";
            foreach (var feedback in feedbacks)
            {
                if (feedback.CustomerId != Id)
                {
                    html += "<div>";
                    html += $"<h2>ID: {feedback.Id}, Customer ID: {feedback.CustomerId}</h2>";
                    html += $"<p>Message: {feedback.Message}</p>";
                    html += $"<p>Timestamp: {feedback.Timestamp.ToString()}</p>";
                    html += "</div>";
                }
                else
                {
                    html += "<div style=\"background-color:yellow\">";
                    html += $"<h2>ID: {feedback.Id}, Customer ID: {feedback.CustomerId}</h2>";
                    html += $"<p>Message: {feedback.Message}</p>";
                    html += $"<p>Timestamp: {feedback.Timestamp.ToString()}</p>";
                    html += "</div>";
                }
            }
            return Content(html);
        }

        [HttpGet]
        public IActionResult InsertFeedbackPage()
        {
            return View("InsertFeedback");
        }

        [HttpPost]
        public IActionResult InsertFeedback(string message)
        {

            bool result = dal.AddFeedback((int)Id, message);
            return result ? Ok() : BadRequest();
        }

        [HttpGet]
        public IActionResult VerifyFeedbacK(string message)
        {
            List<string> words = dal.VerifyFeedback(message);
            if (words.Count <= 3)
            {

                InsertFeedback(message);
                return Content("Success");
            }
            int numberFlags = (int)Count;
            HttpContext.Session.SetInt32("badWords", numberFlags + 1);
            return Content("The following words are blocked: " + String.Join(", ", words));
        }

        [HttpGet]
        public IActionResult GetBadWordsCount()
        {
            return Ok(Count);
        }






        //[HttpGet]
        //public IActionResult ViewPersonChannels()
        //{
        //    return View("ViewPersonChannels");
        //}

        //[HttpGet]
        //public IActionResult GetChannelsByPerson(string person)
        //{
        //    List<Channel> channels = dal.GetChannelsByPerson(person);
        //    if (channels.Count == 0)
        //    {
        //        return Content("<p>No channels found.</p>");
        //    }
        //    var html = "";
        //    foreach (var channel in channels)
        //    {
        //        html += "<div>";
        //        html += $"<h2>ID: {channel.Id}, Owner ID: {channel.OwnerId}, Name: {channel.Name}</h2>";
        //        html += $"<p>Description: {channel.Description}</p>";
        //        html += $"<p>Subscribers: {channel.Subscribers}</p>";
        //        html += "</div>";
        //    }
        //    return Content(html);
        //}

        //[HttpGet]
        //public IActionResult ViewSubscribedChannels()
        //{
        //    return View("ViewSubscribedChannels");
        //}

        //[HttpGet]
        //public IActionResult GetSubscribedChannels()
        //{
        //    string name = Name;
        //    List<Channel> channels = dal.GetSubscribedChannels(name);
        //    if (channels.Count == 0)
        //    {
        //        return Content("<p>No channels found.</p>");
        //    }
        //    var html = "";
        //    foreach (var channel in channels)
        //    {
        //        html += "<div>";
        //        html += $"<h2>Name: {channel.Name}</h2>";
        //        html += $"<p>Description: {channel.Description}</p>";
        //        html += "</div>";
        //    }

        //    return Content(html);
        //}

        //[HttpGet]
        //public IActionResult SubscribeChannel()
        //{
        //    return View("SubscribeChannel");
        //}

        //[HttpGet]
        //public IActionResult AddSubscription(string channel)
        //{
        //    string name = Name;
        //    dal.AddSubscription(name, channel);
        //    return Content("Subscription added successfully");
        //}














        //[HttpGet]
        //public IActionResult GetFlights()
        //{
        //    List<Flight> flights = dal.GetFlights(Date, City);
        //    if (flights.Count == 0)
        //    {
        //        return Content("<p>No flights found.</p>");
        //    }
        //    var html = "";
        //    foreach (var flight in flights)
        //    {
        //        html += "<div>";
        //        html += "<h2>Flight " + flight.Id + ": Destination->" + flight.City + " on " + flight.Date + "</h2>";
        //        html += "<p>Available Seats: " + flight.Seats + "</p>";
        //        html += $"<button data-id='{flight.Id}'>Reserve</button>";
        //        html += "<br><br></div>";
        //    }
        //    return Content(html);
        //}

        //[HttpGet]
        //public IActionResult GetHotelsPage()
        //{
        //    return View("HotelsPage");
        //}

        //[HttpGet]
        //public IActionResult GetHotels()
        //{
        //    List<Hotel> hotels = dal.GetHotels(Date, City);
        //    if (hotels.Count == 0)
        //    {
        //        return Content("<p>No hotels found.</p>");
        //    }
        //    var html = "";
        //    foreach (var hotel in hotels)
        //    {
        //        html += "<div>";
        //        html += "<h2>Hotel " + hotel.Name + ": City->" + hotel.City + " on " + hotel.Date + "</h2>";
        //        html += "<p>Available Rooms: " + hotel.Rooms + "</p>";
        //        html += $"<button data-id='{hotel.Id}'>Reserve</button>";
        //        html += "<br><br></div>";
        //    }
        //    return Content(html);
        //}

        //[HttpPost]
        //public IActionResult ReserveFlight(int flightId)
        //{
        //    Reservation reservation = new Reservation
        //    {
        //        Id = 0,
        //        Person = Person,
        //        Type = "Flight",
        //        ResourceId = flightId
        //    };
        //    Reservation addedReservation = dal.AddReservation(reservation);

        //    Flight flight = dal.GetFlightById(flightId);
        //    flight.Seats--;
        //    dal.UpdateFlight(flight);

        //    string oldReservations = Reservations;
        //    string newReservations = string.IsNullOrEmpty(oldReservations) ? addedReservation.Id.ToString() : addedReservation.Id.ToString() + "," + oldReservations;
        //    HttpContext.Session.SetString("Reservations", newReservations);
        //    Console.WriteLine(Reservations);
        //    return Ok();
        //}

        //[HttpPost]
        //public IActionResult ReserveHotel(int hotelId)
        //{
        //    Reservation reservation = new Reservation
        //    {
        //        Id = 0,
        //        Person = Person,
        //        Type = "Hotel",
        //        ResourceId = hotelId
        //    };
        //    Reservation addedReservation = dal.AddReservation(reservation);

        //    Hotel hotel = dal.GetHotelById(hotelId);
        //    hotel.Rooms--;
        //    dal.UpdateHotel(hotel);

        //    string oldReservations = Reservations;
        //    string newReservations = string.IsNullOrEmpty(oldReservations) ? addedReservation.Id.ToString() : addedReservation.Id.ToString() + "," + oldReservations;
        //    HttpContext.Session.SetString("Reservations", newReservations);
        //    Console.WriteLine(Reservations);
        //    return Ok();
        //}

        //[HttpGet]
        //public IActionResult CancelAllReservations()
        //{
        //    string reservations = Reservations;
        //    List<string> reservationsList = reservations.Split(",").ToList();
        //    Reservation reservation;
        //    foreach (var r in reservationsList)
        //    {
        //        int r_id = Convert.ToInt32(r);
        //        reservation = dal.GetReservationById(r_id);
        //        if (reservation.Type == "Flight")
        //        {
        //            Flight flight = dal.GetFlightById(reservation.ResourceId);
        //            flight.Seats++;
        //            dal.UpdateFlight(flight);
        //        }
        //        else if (reservation.Type == "Hotel")
        //        {
        //            Hotel hotel = dal.GetHotelById(reservation.ResourceId);
        //            hotel.Rooms++;
        //            dal.UpdateHotel(hotel);
        //        }

        //        dal.DeleteReservation(r_id);
        //    }
        //    HttpContext.Session.SetString("Reservations", "");
        //    return Ok();
        //}
    }
}
