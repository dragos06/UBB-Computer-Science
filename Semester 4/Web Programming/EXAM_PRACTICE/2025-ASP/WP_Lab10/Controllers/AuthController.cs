using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using System.Reflection.Metadata;
using System.Security.Claims;
using WP_Lab10.DataAbstractionLayer;
using System.Security.Cryptography;
using System.Text;
using Mysqlx.Prepare;
using WP_Lab10.Models;

namespace WP_Lab10.Controllers
{
    public class AuthController : Controller
    {
        private readonly DAL dal = new DAL();

        [HttpGet]
        public IActionResult Login() => View();

        [HttpPost]
        public IActionResult Login(string name, string email)
        {
            if (string.IsNullOrEmpty(name) || string.IsNullOrEmpty(email))
            {
                ViewBag.Error = "Name and Email are required.";
                return View();
            }

            Customer customer = dal.GetCustomer(name, email);
            if (customer.Id != 0 && !string.IsNullOrEmpty(customer.Name) && !string.IsNullOrEmpty(customer.Email))
            {
                HttpContext.Session.SetInt32("id", customer.Id);
                HttpContext.Session.SetString("name", customer.Name);
                HttpContext.Session.SetString("email", customer.Email);
                HttpContext.Session.SetInt32("badWords", 0);
                return RedirectToAction("Index", "Main");
            }
            return View();
        }
    }
}
