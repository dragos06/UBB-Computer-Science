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
        public IActionResult Login(string name)
        {
            if (string.IsNullOrEmpty(name))
            {
                ViewBag.Error = "Name is required.";
                return View();
            }

            HttpContext.Session.SetString("Name", name);
            return RedirectToAction("Index", "Main");

        }
    }
}
