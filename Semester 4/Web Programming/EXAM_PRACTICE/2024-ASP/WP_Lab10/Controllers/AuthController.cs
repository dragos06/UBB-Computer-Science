using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using System.Reflection.Metadata;
using System.Security.Claims;
using WP_Lab10.DataAbstractionLayer;
using System.Security.Cryptography;
using System.Text;
using Mysqlx.Prepare;

namespace WP_Lab10.Controllers
{
    public class AuthController : Controller
    {
        private readonly DAL dal = new DAL();

        [HttpGet]
        public IActionResult Login() => View();

        [HttpPost]
        public IActionResult Login(string person, DateOnly date, string city)
        {
            if (string.IsNullOrEmpty(person) || string.IsNullOrEmpty(city))
            {
                ViewBag.Error = "Person and city are required.";
                return View();
            }

            HttpContext.Session.SetString("Person", person);
            HttpContext.Session.SetString("Date", date.ToString());
            HttpContext.Session.SetString("City", city);
            HttpContext.Session.SetString("Reservations", "");
            return RedirectToAction("Index", "Main");

        }
    }
}
