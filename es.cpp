#include <iostream>
#include <cmath>
#include <ctime>
#include<vector>                   

const double PI = atan(1.0) * 4;
const int mu = 5;
const int lambda = 35;
const int eta = lambda / mu;
const double sigma = 0.1;

using namespace std;

class lw_4
{
private:
    double x1[mu], y1[mu], x2[mu], y2[mu], x3[mu], y3[mu];
    double x1_lambda[lambda], y1_lambda[lambda], x2_lambda[lambda], y2_lambda[lambda], x3_lambda[lambda], y3_lambda[lambda];
    double result1[mu], result2[mu], result3[mu];
    double new_result1[lambda], new_result2[lambda], new_result3[lambda];
    short a = 1;
    int iteration = 0;
    bool flag = true;
    double min_first, min_lamda, index_first, index_lambda;
    double mass_x_y[mu+lambda][3];
    double min1, min2, min3, new_min1, new_min2, new_min3;
    int index, index1;
    vector<double> global_min;
public:
    double func1(double x, double y)
    {
        return pow((1.5 - x + x * y), 2) + pow((2.25 - x + x * pow(y, 2)), 2) + pow((2.625 - x + x * pow(y, 3)), 2);
    }

    int func2(double x, double y)
    {
        return  (1 + pow((x + y + 1), 2) * (19 - 14 * x + 3 * x * x - 14 * y + 6 * x * y + 3 * y * y)) * (30 + pow((2 * x - 3 * y), 2) * (18 - 32 * x + 12 * x * x + 48 * y - 36 * x * y + 27 * y * y));
    }

    double func3(double x, double y)
    {
        return  -1 * (y + 47) * sin(sqrt(fabs((x / 2) + y + 47))) - x * sin(sqrt(fabs(x - y - 47)));
    }
    double rozpodil(double m, double sig)
    {
        double r1 = double(rand()) / RAND_MAX;
        double r2 = double(rand()) / RAND_MAX;
        return m + sig * cos(2 * PI * r1) * sqrt(-2 * log(r2));
    }
    void rand_inp()
    {
        for (int i = 0; i < mu; i++)
        {
            if (a == 1)
            {
                x1[i] = -4.5 + double(rand()) / RAND_MAX * (4.5 + 4.5);
                y1[i] = -4.5 + double(rand()) / RAND_MAX * (4.5 + 4.5);
            }
            if (a == 2)
            {
                x2[i] = -2 + double(rand()) / RAND_MAX * (2 + 2);
                y2[i] = -2 + double(rand()) / RAND_MAX * (2 + 2);
            }
            if (a == 3)
            {
                x3[i] = 500 + double(rand()) / RAND_MAX * (500 - 512);
                y3[i] = 400 + double(rand()) / RAND_MAX * (400 - 405);
            }
        }
    }
    lw_4 main_func()
    {
        while (flag)
        {
            for (int i = 0; i < mu; i++)
            {
                if (a == 1)
                {
                    result1[i] = func1(x1[i], y1[i]);
                }
                if (a == 2)
                {
                    result2[i] = func2(x2[i], y2[i]);
                }
                if (a == 3)
                {
                    result3[i] = func3(x3[i], y3[i]);
                }
            }

            min1 = result1[0]; min2 = result2[0]; min3 = result3[0];
            for (int i = 0; i < mu; i++)
            {
                if (a == 1)
                {
                    if (result1[i] < min1)
                    {
                        min1 = result1[i];
                        index = i;
                    }
                }
                if (a == 2)
                {
                    if (result2[i] < min2)
                    {
                        min2 = result2[i];
                        index = i;
                    }
                }
                if (a == 3)
                {
                    if (result3[i] < min3)
                    {
                        min3 = result3[i];
                        index = i;
                    }
                }
            }
            if (a == 1)
            {
                global_min.push_back(min1);
            }
            if (a == 2)
            {
                global_min.push_back(min2);
            }
            if (a == 3)
            {
                global_min.push_back(min3);
            }

            int e = 0;
            for (int i = 0; i < mu; i++)
            {
                for (int j = 0; j < eta; j++)
                {
                    if (a == 1)
                    {
                        x1_lambda[e] = x1[i] + rozpodil(0, sigma);
                        y1_lambda[e] = y1[i] + rozpodil(0, sigma);
                        e++;
                    }
                    if (a == 2)
                    {
                        x2_lambda[e] = x2[i] + rozpodil(0, sigma);
                        y2_lambda[e] = y2[i] + rozpodil(0, sigma);
                        e++;
                    }
                    if (a == 3)
                    {
                        x3_lambda[e] = x3[i] + rozpodil(0, sigma);
                        y3_lambda[e] = y3[i] + rozpodil(0, sigma);
                        e++;
                    }
                }
            }

            for (int i = 0; i < lambda; i++)
            {
                if (a == 1)
                {
                    new_result1[i] = func1(x1_lambda[i], y1_lambda[i]);
                }
                if (a == 2)
                {
                    new_result2[i] = func2(x2_lambda[i], y2_lambda[i]);
                }
                if (a == 3)
                {
                    new_result3[i] = func3(x3_lambda[i], y3_lambda[i]);
                }
            }

            //lambda+mu
            for (int i = 0; i < mu + lambda; i++)
            {
                if (a == 1)
                {
                    if (i < mu)
                    {
                        mass_x_y[i][0] = result1[i];
                        mass_x_y[i][1] = x1[i];
                        mass_x_y[i][2] = y1[i];
                    }
                    else
                    {
                        mass_x_y[i][0] = new_result1[i - 5];
                        mass_x_y[i][1] = x1_lambda[i - 5];
                        mass_x_y[i][2] = y1_lambda[i - 5];
                    }
                }
                if (a == 2)
                {
                    if (i < mu)
                    {
                        mass_x_y[i][0] = result2[i];
                        mass_x_y[i][1] = x2[i];
                        mass_x_y[i][2] = y2[i];
                    }
                    else
                    {
                        mass_x_y[i][0] = new_result2[i - 5];
                        mass_x_y[i][1] = x2_lambda[i - 5];
                        mass_x_y[i][2] = y2_lambda[i - 5];
                    }
                }
                if (a == 3)
                {
                    if (i < mu)
                    {
                        mass_x_y[i][0] = result3[i];
                        mass_x_y[i][1] = x3[i];
                        mass_x_y[i][2] = y3[i];
                    }
                    else
                    {
                        mass_x_y[i][0] = new_result3[i - 5];
                        mass_x_y[i][1] = x3_lambda[i - 5];
                        mass_x_y[i][2] = y3_lambda[i - 5];
                    }
                }
            }

            double temp, temp1, temp2;
            for (int i = 0; i < lambda + mu - 1; i++) {
                for (int j = 0; j < lambda + mu - i - 1; j++) {
                    if (mass_x_y[j][0] > mass_x_y[j + 1][0]) {
                        temp = mass_x_y[j][0];
                        temp1 = mass_x_y[j][1];
                        temp2 = mass_x_y[j][2];
                        mass_x_y[j][0] = mass_x_y[j + 1][0];
                        mass_x_y[j][1] = mass_x_y[j + 1][1];
                        mass_x_y[j][2] = mass_x_y[j + 1][2];
                        mass_x_y[j + 1][0] = temp;
                        mass_x_y[j + 1][1] = temp1;
                        mass_x_y[j + 1][2] = temp2;
                    }
                }
            }
            for (int i = 0; i < mu; i++)
            {
                if (a == 1)
                {
                    x1[i] = mass_x_y[i][1];
                    y1[i] = mass_x_y[i][2];
                }
                if (a == 2)
                {
                    x2[i] = mass_x_y[i][1];
                    y2[i] = mass_x_y[i][2];
                }
                if (a == 3)
                {
                    x3[i] = mass_x_y[i][1];
                    y3[i] = mass_x_y[i][2];
                }
            }
            ////////

            //lambda, mu
           /* for (int i = 0; i < lambda; i++)
            {
                if (a == 1)
                {
                    mass_x_y[i][0] = new_result1[i];
                    mass_x_y[i][1] = x1_lambda[i];
                    mass_x_y[i][2] = y1_lambda[i];
                }
                if (a == 2)
                {
                    mass_x_y[i][0] = new_result2[i];
                    mass_x_y[i][1] = x2_lambda[i];
                    mass_x_y[i][2] = y2_lambda[i];
                }
                if (a == 3)
                {
                    mass_x_y[i][0] = new_result3[i];
                    mass_x_y[i][1] = x3_lambda[i];
                    mass_x_y[i][2] = y3_lambda[i];
                }
            }

            double temp, temp1, temp2;
            for (int i = 0; i < lambda - 1; i++) {
                for (int j = 0; j < lambda - i - 1; j++) {
                    if (mass_x_y[j][0] > mass_x_y[j + 1][0]) {
                        temp = mass_x_y[j][0];
                        temp1 = mass_x_y[j][1];
                        temp2 = mass_x_y[j][2];
                        mass_x_y[j][0] = mass_x_y[j + 1][0];
                        mass_x_y[j][1] = mass_x_y[j + 1][1];
                        mass_x_y[j][2] = mass_x_y[j + 1][2];
                        mass_x_y[j + 1][0] = temp;
                        mass_x_y[j + 1][1] = temp1;
                        mass_x_y[j + 1][2] = temp2;
                    }
                }
            }
            for (int i = 0; i < mu; i++)
            {
                if (a == 1)
                {
                    x1[i] = mass_x_y[i][1];
                    y1[i] = mass_x_y[i][2];
                }
                if (a == 2)
                {
                    x2[i] = mass_x_y[i][1];
                    y2[i] = mass_x_y[i][2];
                }
                if (a == 3)
                {
                    x3[i] = mass_x_y[i][1];
                    y3[i] = mass_x_y[i][2];
                }
            }*/
            ///////
            iteration++;
            int r;
            if (a == 1)
            {
                r = 1;
            }
            if (a == 2)
            {
                r = 4;
            }
            if (a == 3)
            {
                r = 7;
            }
            if (iteration % r == 0)
            {
                if (a == 1)
                {
                    new_min1 = func1(x1[0], y1[0]);
                    double minn;
                    for (int i = 0; i < mu; i++)
                    {
                        minn = func1(x1[i], y1[i]);
                        if (minn < new_min1)
                        {
                            new_min1 = func1(x1[i], y1[i]);
                            index1 = i;
                        }
                    }
                    minn = global_min[0];
                    for (int i = 0; i < global_min.size(); i++)
                    {
                        if (global_min[i] < minn)
                        {
                            minn = global_min[i];
                        }
                    }
                    if (new_min1 >= minn || ((x1[index] < -4.5 || x1[index] > 4.5) || (y1[index] < -4.5 || y1[index] > 4.5)) )
                    {
                        flag = false;
                        index = index1;
                    }
                }
                if (a == 2)
                {
                    new_min2 = func2(x2[0], y2[0]);
                    double minn;
                    for (int i = 0; i < mu; i++)
                    {
                        minn = func2(x2[i], y2[i]);
                        if (minn < new_min2)
                        {
                            new_min2 = func2(x2[i], y2[i]);
                            index1 = i;
                        }
                    }
                    minn = global_min[0];
                    for (int i = 0; i < global_min.size(); i++)
                    {
                        if (global_min[i] < minn)
                        {
                            minn = global_min[i];
                        }
                    }
                    if (new_min2 >= minn || ((x2[index] < -2 || x2[index] > 2) || (y2[index] < -2 || y2[index] > 2)))
                    {
                        flag = false;
                        index = index1;
                    }
                }
                if (a == 3)
                {
                    new_min3 = func3(x3[0], y3[0]);
                    double minn;
                    for (int i = 0; i < mu; i++)
                    {
                        minn = func3(x3[i], y3[i]);
                        if (minn < new_min3)
                        {
                            new_min3 = func3(x3[i], y3[i]);
                            index1 = i;
                        }
                    }
                    minn = global_min[0];
                    for (int i = 0; i < global_min.size(); i++)
                    {
                        if (global_min[i] < minn)
                        {
                            minn = global_min[i];
                        }
                    }
                    if (new_min3 >= minn || ((x3[index] < -512 || x3[index] > 512) || (y3[index] < -512 || y3[index] > 512)))
                    {
                        flag = false;
                        index = index1;
                    }
                }
            }
            if (a == 1)
            {
                cout << "iteration = " << iteration << endl;
                cout << "f = " << func1(x1[index], y1[index]) << " x = " << x1[index] << " y = " << y1[index] << endl;
            }
            if (a == 2)
            {
                cout << "iteration = " << iteration << endl;
                cout << "f = " << func2(x2[index], y2[index]) << " x = " << x2[index] << " y = " << y2[index] << endl;
            }
            if (a == 3)
            {
                cout << "iteration = " << iteration << endl;
                cout << "f = " << func3(x3[index], y3[index]) << " x = " << x3[index] << " y = " << y3[index] << endl;
            }
        }
        flag = true;
        iteration = 0;
        return *this;
    }
    void set_a(short b)
    {
        a = b;
    }
    void interface()
    {
        short b;
        bool fl = true;
        while (fl)
        {
            cout << "Input number of function" << endl;
            cout << "1 - Bill" << endl << "2 - Goldman-Price" << endl << "3 - Eggholder" << endl << "4 - Exit" << endl;
            cin >> b;
            this->set_a(b);
            this->rand_inp();
            switch (b)
            {
            case 1:
                this->main_func();
                break;
            case 2:
                this->main_func();
                break;
            case 3:
                this->main_func();
                break;
            case 4:
                fl = false;
                break;
            }
            global_min.clear();
        }
    }
};
int main()
{
    lw_4 t;
    t.interface();
    return 0;
}
