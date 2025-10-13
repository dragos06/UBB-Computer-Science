using Microsoft.AspNetCore.Mvc;
using Org.BouncyCastle.Asn1.Mozilla;
using WP_Lab10.DataAbstractionLayer;
using WP_Lab10.Models;

namespace WP_Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private string Person => HttpContext.Session.GetString("Person");
        private DateOnly Date => DateOnly.Parse(HttpContext.Session.GetString("Date"));
        private string City => HttpContext.Session.GetString("City");
        private string Reservations => HttpContext.Session.GetString("Reservations");

        public IActionResult Index()
        {
            if (string.IsNullOrEmpty(Person)) return View("Login");
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetFlightsPage()
        {
            return View("FlightsPage");
        }

        [HttpGet]
        public IActionResult GetFlights()
        {
            List<Flight> flights = dal.GetFlights(Date, City);
            if (flights.Count == 0)
            {
                return Content("<p>No flights found.</p>");
            }
            var html = "";
            foreach (var flight in flights)
            {
                html += "<div>";
                html += "<h2>Flight " + flight.Id + ": Destination->" + flight.City + " on " + flight.Date + "</h2>";
                html += "<p>Available Seats: " + flight.Seats + "</p>";
                html += $"<button data-id='{flight.Id}'>Reserve</button>";
                html += "<br><br></div>";
            }
            return Content(html);
        }

        [HttpGet]
        public IActionResult GetHotelsPage()
        {
            return View("HotelsPage");
        }

        [HttpGet]
        public IActionResult GetHotels()
        {
            List<Hotel> hotels = dal.GetHotels(Date, City);
            if (hotels.Count == 0)
            {
                return Content("<p>No hotels found.</p>");
            }
            var html = "";
            foreach (var hotel in hotels)
            {
                html += "<div>";
                html += "<h2>Hotel " + hotel.Name + ": City->" + hotel.City + " on " + hotel.Date + "</h2>";
                html += "<p>Available Rooms: " + hotel.Rooms + "</p>";
                html += $"<button data-id='{hotel.Id}'>Reserve</button>";
                html += "<br><br></div>";
            }
            return Content(html);
        }

        [HttpPost]
        public IActionResult ReserveFlight(int flightId)
        {
            Reservation reservation = new Reservation
            {
                Id = 0,
                Person = Person,
                Type = "Flight",
                ResourceId = flightId
            };
            Reservation addedReservation = dal.AddReservation(reservation);

            Flight flight = dal.GetFlightById(flightId);
            flight.Seats--;
            dal.UpdateFlight(flight);

            string oldReservations = Reservations;
            string newReservations = string.IsNullOrEmpty(oldReservations) ? addedReservation.Id.ToString() : addedReservation.Id.ToString() + "," + oldReservations;
            HttpContext.Session.SetString("Reservations", newReservations);
            Console.WriteLine(Reservations);
            return Ok();
        }

        [HttpPost]
        public IActionResult ReserveHotel(int hotelId)
        {
            Reservation reservation = new Reservation
            {
                Id = 0,
                Person = Person,
                Type = "Hotel",
                ResourceId = hotelId
            };
            Reservation addedReservation = dal.AddReservation(reservation);

            Hotel hotel = dal.GetHotelById(hotelId);
            hotel.Rooms--;
            dal.UpdateHotel(hotel);

            string oldReservations = Reservations;
            string newReservations = string.IsNullOrEmpty(oldReservations) ? addedReservation.Id.ToString() : addedReservation.Id.ToString() + "," + oldReservations;
            HttpContext.Session.SetString("Reservations", newReservations);
            Console.WriteLine(Reservations);
            return Ok();
        }

        [HttpGet]
        public IActionResult CancelAllReservations()
        {
            string reservations = Reservations;
            List<string> reservationsList = reservations.Split(",").ToList();
            Reservation reservation;
            foreach (var r in reservationsList)
            {
                int r_id = Convert.ToInt32(r);
                reservation = dal.GetReservationById(r_id);
                if (reservation.Type == "Flight")
                {
                    Flight flight = dal.GetFlightById(reservation.ResourceId);
                    flight.Seats++;
                    dal.UpdateFlight(flight);
                }
                else if (reservation.Type == "Hotel")
                {
                    Hotel hotel = dal.GetHotelById(reservation.ResourceId);
                    hotel.Rooms++;
                    dal.UpdateHotel(hotel);
                }

                dal.DeleteReservation(r_id);
            }
            HttpContext.Session.SetString("Reservations", "");
            return Ok();
        }
    }
}
