using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace L1
{
    public partial class Form1 : Form
    {
        SqlConnection con;
        SqlDataAdapter daParent;
        SqlDataAdapter daChild;
        DataSet dset;
        BindingSource bsParent;
        BindingSource bsChild;

        SqlCommandBuilder cmdBuilder;

        string queryParent;
        string queryChild;

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            try
            {
                con = new SqlConnection("Data Source=DESKTOP-SBCUNGL\\SQLEXPRESS;Initial Catalog=CulturalEvents;Integrated Security=true;");

                queryParent = "SELECT * FROM Categories";
                queryChild = "SELECT * FROM CulEvents";

                daParent = new SqlDataAdapter(queryParent, con);
                daChild = new SqlDataAdapter(queryChild, con);

                dset = new DataSet();
                daParent.Fill(dset, "Categories");
                daChild.Fill(dset, "CulEvents");

                cmdBuilder = new SqlCommandBuilder(daChild);

                dset.Relations.Add("CategoriesCulEvents", dset.Tables["Categories"].Columns["c_id"], dset.Tables["CulEvents"].Columns["c_id"]);

                bsParent = new BindingSource();
                bsParent.DataSource = dset.Tables["Categories"];
                bsChild = new BindingSource(bsParent, "CategoriesCulEvents");
                dgvCategories.DataSource = bsParent;
                labelParent.Text = "Categories";
                dgvCulturalEvents.DataSource = bsChild;
                labelChild.Text = "CulEvents";

                cmdBuilder.GetUpdateCommand();
            }
            catch (SqlException ex)
            {
                MessageBox.Show("Database error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Unexpected error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                daChild.Update(dset, "CulEvents");
                FillData();
                MessageBox.Show("Database updated successfully", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (DBConcurrencyException ex)
            {
                MessageBox.Show("Concurrency error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (SqlException ex)
            {
                MessageBox.Show("Database update error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Unexpected error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void dataGridViewEquipment_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
