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
        public IActionResult Login(string username, string password)
        {
            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                ViewBag.Error = "Username and password are required.";
                return View();
            }

            string hashedPassword = HashPassword(password);
            int? userId = dal.ValidateUser(username, hashedPassword);
            if (userId != null)
            {
                HttpContext.Session.SetInt32("UserId", userId.Value);
                HttpContext.Session.SetString("Username", username);
                return RedirectToAction("Index", "Main");
            }
            else
            {
                ViewBag.Error = "Invalid username or password.";
                return View();
            }
        }

        [HttpPost]
        public IActionResult Register(string username, string password)
        {
            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                ViewBag.Error = "Username and password are required.";
                return View("Login");
            }

            string hashedPassword = HashPassword(password);
            bool success = dal.RegisterUser(username, hashedPassword);

            if (!success)
            {
                ViewBag.Error = "Username already exists.";
                return View("Login");
            }

            int? userId = dal.ValidateUser(username, hashedPassword);
            if (userId != null)
            {
                HttpContext.Session.SetInt32("UserId", userId.Value);
                HttpContext.Session.SetString("Username", username);
                return RedirectToAction("Index", "Main");
            }

            ViewBag.Error = "Registration failed. Please try again.";
            return View("Login");
        }

        [HttpGet]
        public IActionResult Logout()
        {
            HttpContext.Session.Clear();
            return RedirectToAction("Login");
        }

        private string HashPassword(string password)
        {
            using var sha = SHA256.Create();
            var bytes = Encoding.UTF8.GetBytes(password);
            var hash = sha.ComputeHash(bytes);
            return Convert.ToHexString(hash);
        }
    }
}
