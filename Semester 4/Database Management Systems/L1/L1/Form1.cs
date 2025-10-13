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
using System.Configuration;

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
                con = new SqlConnection(ConfigurationManager.AppSettings["ConnectionString"]);

                queryParent = "SELECT * FROM " + ConfigurationManager.AppSettings["ParentTable"];
                queryChild = "SELECT * FROM " + ConfigurationManager.AppSettings["ChildTable"];

                daParent = new SqlDataAdapter(queryParent, con);
                daChild = new SqlDataAdapter(queryChild, con);

                dset = new DataSet();
                daParent.Fill(dset, ConfigurationManager.AppSettings["ParentTable"]);
                daChild.Fill(dset, ConfigurationManager.AppSettings["ChildTable"]);

                cmdBuilder = new SqlCommandBuilder(daChild);

                dset.Relations.Add(ConfigurationManager.AppSettings["Relation"], dset.Tables[ConfigurationManager.AppSettings["ParentTable"]].Columns[ConfigurationManager.AppSettings["ParentColumn"]], dset.Tables[ConfigurationManager.AppSettings["ChildTable"]].Columns[ConfigurationManager.AppSettings["ChildColumn"]]);

                //dataGridViewSkiers.DataSource = dset.Tables["Skiers"];
                //dataGridViewEquipment.DataSource = dataGridViewSkiers.DataSource;
                //dataGridViewEquipment.DataMember = "SkiersEquipment";

                bsParent = new BindingSource();
                bsParent.DataSource = dset.Tables[ConfigurationManager.AppSettings["ParentTable"]];
                bsChild = new BindingSource(bsParent, ConfigurationManager.AppSettings["Relation"]);
                dataGridViewParent.DataSource = bsParent;
                labelParent.Text = ConfigurationManager.AppSettings["ParentTable"];
                dataGridViewChild.DataSource = bsChild;
                labelChild.Text = ConfigurationManager.AppSettings["ChildTable"];

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
                daChild.Update(dset, ConfigurationManager.AppSettings["ChildTable"]);
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
