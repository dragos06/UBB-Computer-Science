using WP_Lab10.Models;
using MySql.Data.MySqlClient;
using static Org.BouncyCastle.Bcpg.Attr.ImageAttrib;

namespace WP_Lab10.DataAbstractionLayer
{
    public class DAL
    {
        public List<Document> GetDocuments(string type, string format, int userId)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";
            List<Document> dlist = new List<Document>();

            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "SELECT * FROM documents WHERE user_id = @UserId";
                if (!string.IsNullOrEmpty(type))
                    query += " AND type = @Type";
                if (!string.IsNullOrEmpty(format))
                    query += " AND format = @Format";

                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@UserId", userId);
                if (!string.IsNullOrEmpty(type))
                    cmd.Parameters.AddWithValue("@Type", type);
                if (!string.IsNullOrEmpty(format))
                    cmd.Parameters.AddWithValue("@Format", format);

                MySqlDataReader myreader = cmd.ExecuteReader();

                while (myreader.Read())
                {
                    Document doc = new Document();
                    doc.Id = myreader.GetInt32("id");
                    doc.Author = myreader.GetString("author");
                    doc.Title = myreader.GetString("title");
                    doc.Pages = myreader.GetInt32("pages");
                    doc.Type = myreader.GetString("type");
                    doc.Format = myreader.GetString("format");
                    doc.UserId = myreader.GetInt32("user_id");

                    dlist.Add(doc);
                }

                myreader.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }

            return dlist;
        }

        public Document GetDocumentById(int id)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";
            Document doc = new Document();
            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "SELECT * FROM documents WHERE id=" + id + ";";

                cmd.CommandText = query;
                MySqlDataReader myreader = cmd.ExecuteReader();

                while (myreader.Read())
                {
                    doc.Id = myreader.GetInt32("id");
                    doc.Author = myreader.GetString("author");
                    doc.Title = myreader.GetString("title");
                    doc.Pages = myreader.GetInt32("pages");
                    doc.Type = myreader.GetString("type");
                    doc.Format = myreader.GetString("format");
                }

                myreader.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }

            return doc;
        }

        public void SaveDocument(Document newDoc)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";

            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = @"INSERT INTO documents (author, title, pages, type, format, user_id) 
                         VALUES (@Author, @Title, @Pages, @Type, @Format, @UserId)";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Author", newDoc.Author);
                cmd.Parameters.AddWithValue("@Title", newDoc.Title);
                cmd.Parameters.AddWithValue("@Pages", newDoc.Pages);
                cmd.Parameters.AddWithValue("@Type", newDoc.Type);
                cmd.Parameters.AddWithValue("@Format", newDoc.Format);
                cmd.Parameters.AddWithValue("@UserId", newDoc.UserId);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }
        public void UpdateDocument(Document updateDoc)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";

            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = @"UPDATE documents 
                             SET author = @Author, 
                                 title = @Title, 
                                 pages = @Pages, 
                                 type = @Type, 
                                 format = @Format 
                             WHERE id = @Id AND user_id = @UserId";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Author", updateDoc.Author);
                cmd.Parameters.AddWithValue("@Title", updateDoc.Title);
                cmd.Parameters.AddWithValue("@Pages", updateDoc.Pages);
                cmd.Parameters.AddWithValue("@Type", updateDoc.Type);
                cmd.Parameters.AddWithValue("@Format", updateDoc.Format);
                cmd.Parameters.AddWithValue("@Id", updateDoc.Id);
                cmd.Parameters.AddWithValue("@UserId", updateDoc.UserId);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }
        public void DeleteDocument(int id, int userId)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";

            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "DELETE FROM documents WHERE id=@Id AND user_id=@UserId";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Id", id);
                cmd.Parameters.AddWithValue("@UserId", userId);
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public int? ValidateUser(string username, string password)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";
            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "SELECT id FROM users WHERE username=@Username AND password=@Password";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Username", username);
                cmd.Parameters.AddWithValue("@Password", password);
                var result = cmd.ExecuteScalar();
                if (result != null)
                {
                    return Convert.ToInt32(result);
                }
                return null;
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
                return null;
            }
        }

        public bool RegisterUser(string username, string hashedPassword)
        {
            MySql.Data.MySqlClient.MySqlConnection conn;
            string myConnectionString;

            myConnectionString = "server=localhost;uid=root;pwd=;database=document_manager";
            try
            {
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand checkCmd = new MySqlCommand("SELECT COUNT(*) FROM users WHERE username = @Username", conn);
                checkCmd.Parameters.AddWithValue("@Username", username);
                int count = Convert.ToInt32(checkCmd.ExecuteScalar());

                if (count > 0)
                {
                    return false;
                }

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "INSERT INTO users (username, password) VALUES (@Username, @Password)";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@Username", username);
                cmd.Parameters.AddWithValue("@Password", hashedPassword);
                cmd.ExecuteNonQuery();

                return true;
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
                return false;
            }
        }
    }
}
