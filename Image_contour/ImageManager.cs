using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Image_contour
{
    class ImageManager
    {
        private Bitmap _bitmap;

        public ImageManager()
        { }

        public ImageManager(Bitmap bitmap) => SetBitmap(bitmap);

        public ImageManager SetBitmap(Bitmap bitmap)
        {
            _bitmap = bitmap;

            return this;
        }

        public Bitmap GetBitmap()
        {
            return _bitmap;
        }

        public Bitmap LaplaceOperator()
        {
            Bitmap res = null;

            return res;
        }

        public Bitmap RobertsOperator()
        {
            Bitmap res = null;

            return res;
        }

        public Bitmap SobelOperator()
        {
            Bitmap res;

            int width = _bitmap.Width;
            int height = _bitmap.Height;

            res = new Bitmap(width, height);

            for (int i = 1; i < height - 1; i++)
            {
                for (int j = 1; j < width - 1; j++)
                {
                    int currentPixel = ApplySobelOperator(j, i);
                    res.SetPixel(j, i, Color.FromArgb(currentPixel, currentPixel, currentPixel));
                }
            }

            return res;
        }


        private int ApplySobelOperator(int x, int y)
        {
            int res;

            int[,] Gx = new int[3, 3]{ {-1, 0, 1 },
                                       {-2, 0, 2 } ,
                                       {-1, 0, 1 } };

            int[,] Gy = new int[3, 3]{ {-1,-2,-1},
                                       { 0, 0, 0 },
                                       { 1, 2, 1}};

            res = MultiplyMatrixByBitmapSquare(Gx, x, y) + MultiplyMatrixByBitmapSquare(Gy, x, y);

            res = Math.Min(res, 255);
            res = Math.Max(res, 0);

            return res;
        }

        private int MultiplyMatrixByBitmapSquare(int[,] mat3x3, int x, int y)
        {
            int res = 0;

            for (int i = 0; i < 3; ++i)
            {
                Color a = _bitmap.GetPixel(x - 1, y + i - 1);
                Color b = _bitmap.GetPixel(x,     y + i - 1);
                Color c = _bitmap.GetPixel(x + 1, y + i - 1);

                res += mat3x3[i, 0] * a.G + mat3x3[i, 1] * b.G + mat3x3[i, 2] * c.G;
            }

            res = Math.Min(res, 255);
            res = Math.Max(res, 0);

            return res;
        }
    }
}
