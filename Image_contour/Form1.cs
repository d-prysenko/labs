using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Emgu;
using Emgu.CV;
using Emgu.Util;
using Emgu.CV.Structure;
using Emgu.CV.Util;

namespace Image_contour
{
    public partial class Form1 : Form
    {
        private ImageManager imageManager;

        public Form1()
        {
            InitializeComponent();
            imageManager = new ImageManager();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {

                // записываем в эту переменную результат общения пользователя с openFileDialog1
                DialogResult res = openFileDialog1.ShowDialog();

                if (res == DialogResult.OK)// пользователь выбрал файл
                {
                    Image file = Image.FromFile(openFileDialog1.FileName);
                    pictureBox1.Image = file;

                    imageManager.SetBitmap(new Bitmap(file));
                }
                else
                {
                    MessageBox.Show("Файл не выбран", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }


        }

        private void laplaceToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void robertsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void sobelToolStripMenuItem_Click(object sender, EventArgs e)
        {
             pictureBox2.Image = imageManager.SobelOperator();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = "Файл PNG (*.png)|*.png|Все файлы (*.*)|*.*";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                pictureBox2.Image.Save(saveFileDialog1.FileName);
            }
        }


    }




}
