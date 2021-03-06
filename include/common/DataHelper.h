#include "base.h"
#include "math/Matrix.h"
using namespace std;
namespace HCN
{
    class DataHelper
    {
    private:
        /* data */
    public:
        int imageRow, imageCol;
        vector<Matrix<double>> input;
        vector<Matrix<double>> output;
        void read_Mnist(const string &mnist_img_path, const string &mnist_label_path);
        DataHelper(/* args */);
        ~DataHelper();
    };
    uint32_t swap_endian(uint32_t val)
    {
        val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
        return (val << 16) | (val >> 16);
    }

    void DataHelper::read_Mnist(const string &mnist_img_path, const string &mnist_label_path)
    {
        ifstream mnist_image(mnist_img_path, ios::in | ios::binary);
        ifstream mnist_label(mnist_label_path, ios::in | ios::binary);
        if (mnist_image.is_open() == false || mnist_label.is_open() == false)
        {
            cout << "open mnist image or lable file error!" << endl;
            return;
        }

        uint32_t magic;     //文件中的魔术数(magic number)
        uint32_t num_items; //mnist图像集文件中的图像数目
        uint32_t num_label; //mnist标签集文件中的标签数目
        // uint32_t imageRow;      //图像的行数
        // uint32_t imageCol;      //图像的列数
        //读魔术数
        mnist_image.read(reinterpret_cast<char *>(&magic), 4);
        magic = swap_endian(magic);
        if (magic != 2051)
        {
            LOG(ERROR) << "this is not the mnist image file" << endl;
            return;
        }
        mnist_label.read(reinterpret_cast<char *>(&magic), 4);
        magic = swap_endian(magic);
        if (magic != 2049)
        {
            LOG(ERROR) << "this is not the mnist label file" << endl;
            return;
        }
        mnist_image.read(reinterpret_cast<char *>(&num_items), 4);
        mnist_label.read(reinterpret_cast<char *>(&num_label), 4);
        num_label = swap_endian(num_label);
        num_items = swap_endian(num_items);
        //判断两种标签数是否相等
        if (num_items != num_label)
        {
            cout << "the image file and label file are not a pair" << endl;
            return;
        }
        //cout << num_items << " " << num_label << endl;
        mnist_image.read(reinterpret_cast<char *>(&imageRow), 4);
        mnist_image.read(reinterpret_cast<char *>(&imageCol), 4);
        imageCol = swap_endian(imageCol);
        imageRow = swap_endian(imageRow);
        num_items = 100;
        input.resize(num_items);
        output.resize(num_items);
        LOG(INFO) << "need to prepare " << num_items << endl;
        for (int i = 0; i < num_items; i++)
        {
            if (i % 5 == 0)
            {
                double now = 1.0 * i / num_items;
                LOG(INFO) << "prepare :" << now * 100 << "%" << endl;
            }
            char *pixels = new char[imageRow * imageCol];
            mnist_image.read(pixels, imageRow * imageCol);
            char label;
            mnist_label.read(&label, 1);

            vector<vector<double>> in(imageRow * imageCol, vector<double>(1));
            vector<vector<double>> out(10, vector<double>(1));
            out[(unsigned int)label][0] = 1;
            for (int a = 0; a < imageRow; a++)
                for (int b = 0; b < imageCol; b++)
                {
                    if (pixels[a * imageCol + b] == 0)
                        in[a * imageCol + b][0] = 0;
                    else
                        in[a * imageCol + b][0] = 1;
                }
            input[i] = ToMatrix(in);
            output[i] = ToMatrix(out);
        }
    }

    DataHelper::DataHelper(/* args */)
    {
    }

    DataHelper::~DataHelper()
    {
    }
}