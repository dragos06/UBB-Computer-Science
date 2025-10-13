using Microsoft.AspNetCore.Mvc;
using Org.BouncyCastle.Asn1.Mozilla;
using WP_Lab10.DataAbstractionLayer;
using WP_Lab10.Models;

namespace WP_Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private int? UserId => HttpContext.Session.GetInt32("UserId");

        public IActionResult Index()
        {
            if (UserId == null) return View("Login");

            ViewBag.Username = HttpContext.Session.GetString("Username");
            return View("MainPage");
        }

        public string Test()
        {
            return "It's working";
        }

        [HttpGet]
        public IActionResult GetDocuments(string type, string format)
        {
            if (UserId == null) return View("Login");

            List<Document> documents = dal.GetDocuments(type, format, UserId.Value);
            if (documents.Count == 0)
            {
                return Content("<p>No documents found.</p>");
            }

            var html = "<ul>";
            foreach (var doc in documents)
            {
                html += $"<li data-id='{doc.Id}'>" +
                        $"{doc.Title} - {doc.Author} ({doc.Type}, {doc.Format}) " +
                        $"<div class='button-group'>" +
                        $"<button class='editBtn' data-id='{doc.Id}'>Edit</button>" +
                        $"<button class='deleteBtn' data-id='{doc.Id}'>Delete</button>" +
                        $"</div>" +
                        "</li>";

            }
            html += "</ul>";

            return Content(html);
        }

        [HttpGet]
        public IActionResult AddDocument()
        {
            if (UserId == null) return View("Login");

            return View("AddPage");
        }

        [HttpPost]
        public IActionResult SaveDocument(Document doc)
        {
            if (UserId == null) return View("Login");

            doc.UserId = UserId.Value;
            dal.SaveDocument(doc);
            return Ok();
        }

        [HttpGet]
        public IActionResult EditDocument(int id)
        {
            if (UserId == null) return View("Login");

            ViewData["DocumentId"] = id;
            return View("EditPage");
        }

        [HttpPost]
        public IActionResult UpdateDocument(Document updateDoc)
        {
            if (UserId == null) return View("Login");

            updateDoc.UserId = UserId.Value;
            dal.UpdateDocument(updateDoc);
            return Ok();
        }

        [HttpGet]
        public IActionResult GetDocumentById(int id)
        {
            if (UserId == null) return View("Login");

            Document doc = dal.GetDocumentById(id);
            return Json(doc);
        }

        [HttpPost]
        public IActionResult DeleteDocument(int id)
        {
            if (UserId == null) return View("Login");

            dal.DeleteDocument(id, UserId.Value);
            return Ok();
        }
    }
}
