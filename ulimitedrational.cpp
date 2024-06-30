/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include <iostream>
using namespace std;
bool bg1(string s1, string s2)
{
    if (s1.length() > s2.length())
    {
        return true;
    }
    else if (s1.length() < s2.length())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s2[i] > s1[i])
            {
                return false;
            }
            else if (s2[i] < s1[i])
            {
                return true;
            }
        }
    }
    return true;
}
string ds1(string num, string divisor)
{
    if (divisor == "0")
    {
        return "-0";
    }
    if (divisor == "1")
    {
        return num;
    }
    string result = "";
    int index = 0;

    string dividend = "";

    while (index < num.length())
    {
        int count = 0;
        if (dividend != "0")
        {
            dividend += num[index];
        }
        else
        {
            dividend = num[index];
        }

        while (bg1(dividend, divisor))
        {
            UnlimitedInt *a1 = new UnlimitedInt(dividend);
            UnlimitedInt *a2 = new UnlimitedInt(divisor);
            UnlimitedInt *a3 = UnlimitedInt::sub(a1, a2);
            int *dividend_arr = a3->get_array();
            int size3 = a3->get_size();
            dividend = "";
            for (int i = 0; i < size3; i++)
            {
                dividend = dividend + char(dividend_arr[i] + '0');
            }

            count++;
            delete a1;
            delete a2;
            delete a3;
        }

        result = result + to_string(count);
        index++;
    }
    if (result.empty())
    {
        return "0";
    }
    int y = 0;
    while (result[y] == '0')
    {
        y++;
    }
    string res1 = result.substr(y, result.length() - y);
    if (res1.length() == 0)
    {
        res1 = '0';
    }
    return res1;
}
string rem1(string num, string divisor)
{
    if (divisor == "0")
    {
        return "-0";
    }
    string result = "";
    int index = 0;

    string dividend = "";

    while (index < num.length())
    {
        int count = 0;
        dividend += num[index];
        while (bg1(dividend, divisor))
        {
            UnlimitedInt *a1 = new UnlimitedInt(dividend);
            UnlimitedInt *a2 = new UnlimitedInt(divisor);
            UnlimitedInt *a3 = UnlimitedInt::sub(a1, a2);
            int *dividend_arr = a3->get_array();
            int size3 = a3->get_size();
            dividend = "";
            for (int i = 0; i < size3; i++)
            {
                dividend = dividend + char(dividend_arr[i] + '0');
            }

            count++;
            delete a1;
            delete a2;
            delete a3;
        }

        result = result + to_string(count);
        index++;
    }
    result = dividend;
    if (result.empty())
    {
        return "0";
    }
    int y = 0;
    while (result[y] == '0')
    {
        y++;
    }
    string res1 = result.substr(y, result.length() - y);
    if (res1.length() == 0)
    {
        res1 = '0';
    }
    return res1;
}
string gcd(string num, string divisor)
{

    string a1 = num;
    string a2 = divisor;
    if (!bg1(num, divisor) && divisor != "0")
    {

        a1 = divisor;
        a2 = num;
    }
    if (a2 == "0")
    {
        return "-0";
    }
    string res = "";
    while (rem1(a1, a2) != "0")
    {
        string temp = a2;
        a2 = rem1(a1, a2);
        a1 = temp;
    }
    return a2;
}
UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt("0"); // possible erros
    q = new UnlimitedInt("1");
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (den->to_string() == "-0" || den->to_string() == "0")
    {
        p = new UnlimitedInt("-0");
        q = new UnlimitedInt("-0");
    }
    else
    {

        int sign1 = num->get_sign();
        int sign2 = den->get_sign();
        int *a1 = num->get_array();
        int size1 = num->get_size();
        string s1 = "";
        for (int i = 0; i < size1; i++)
        {
            s1 = s1 + char(a1[i] + '0');
        }
        int *a2 = den->get_array();
        int size2 = den->get_size();
        string s2 = "";
        for (int i = 0; i < size2; i++)
        {
            s2 = s2 + char(a2[i] + '0');
        }

        string s3 = gcd(s1, s2);

        if (s3 == "-0" && num->to_string() == "0")
        {
            p = new UnlimitedInt("0");
            q = new UnlimitedInt(s2);
        }
        else
        {

            s1 = ds1(s1, s3);
            s2 = ds1(s2, s3);

            if (sign1 * sign2 < 0)
            {
                s1.insert(s1.begin(), '-');
            }
            p = new UnlimitedInt(s1);
            q = new UnlimitedInt(s2);
        }
    }
}
UnlimitedRational::~UnlimitedRational()
{
    delete p; // possible errors
    delete q;
}
UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    UnlimitedInt *p1 = this->get_p();
    return p1->to_string();
}
string UnlimitedRational::get_q_str()
{
    UnlimitedInt *q1 = this->get_q();
    return q1->to_string();
}
string UnlimitedRational::get_frac_str()
{
    if (this->get_q_str() == "-0" || this->get_q_str() == "0")
    {
        return "0/0";
    }
    else
    {
        return this->get_p_str() + "/" + this->get_q_str();
    }
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0")
    {
        UnlimitedInt *a1 = new UnlimitedInt("-0");
        UnlimitedInt *a2 = new UnlimitedInt("-0");
        UnlimitedRational *answer = new UnlimitedRational(a1, a2);
        delete a1;
        delete a2;
        return answer;
    }
    else
    {
        UnlimitedInt *num1 = new UnlimitedInt(i1->get_p_str());
        UnlimitedInt *num2 = new UnlimitedInt(i2->get_p_str());
        UnlimitedInt *den1 = new UnlimitedInt(i1->get_q_str());
        UnlimitedInt *den2 = new UnlimitedInt(i2->get_q_str());

        UnlimitedInt *numerator = UnlimitedInt::add(UnlimitedInt::mul(num1, den2), UnlimitedInt::mul(num2, den1));
        UnlimitedInt *denominator = UnlimitedInt::mul(den1, den2);

        UnlimitedRational *result = new UnlimitedRational(numerator, denominator);
        delete num1;
        delete num2;
        delete den1;
        delete den2;
        delete numerator;
        delete denominator;
        return result;
    }
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0")
    {
        UnlimitedInt *a1 = new UnlimitedInt("-0");
        UnlimitedInt *a2 = new UnlimitedInt("-0");
        UnlimitedRational *answer = new UnlimitedRational(a1, a2);
        delete a1;
        delete a2;
        return answer;
    }
    else
    {
        UnlimitedInt *num1 = new UnlimitedInt(i1->get_p_str());
        UnlimitedInt *num2 = new UnlimitedInt(i2->get_p_str());
        UnlimitedInt *den1 = new UnlimitedInt(i1->get_q_str());
        UnlimitedInt *den2 = new UnlimitedInt(i2->get_q_str());

        UnlimitedInt *numerator = UnlimitedInt::sub(UnlimitedInt::mul(num1, den2), UnlimitedInt::mul(num2, den1));
        UnlimitedInt *denominator = UnlimitedInt::mul(den1, den2);

        UnlimitedRational *result = new UnlimitedRational(numerator, denominator);
        delete num1;
        delete num2;
        delete den1;
        delete den2;
        delete numerator;
        delete denominator;
        return result;
    }
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *num1 = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *num2 = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *den1 = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *den2 = new UnlimitedInt(i2->get_q_str());
    UnlimitedInt *numerator = UnlimitedInt::mul(num1, num2);
    UnlimitedInt *denominator = UnlimitedInt::mul(den1, den2);

    UnlimitedRational *result = new UnlimitedRational(numerator, denominator);
    delete num1;
    delete num2;
    delete den1;
    delete den2;
    delete numerator;
    delete denominator;
    return result;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *num1 = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *num2 = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *den1 = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *den2 = new UnlimitedInt(i2->get_q_str());
    UnlimitedInt *numerator = UnlimitedInt::mul(num1, den2);
    UnlimitedInt *denominator = UnlimitedInt::mul(den1, num2);
    UnlimitedRational *result = new UnlimitedRational(numerator, denominator);
    delete num1;
    delete num2;
    delete den1;
    delete den2;
    delete numerator;
    delete denominator;
    return result;
}
// int main()
// {

//     UnlimitedInt *a = new UnlimitedInt("800");

//     UnlimitedInt *b = new UnlimitedInt("1");

//     UnlimitedInt *c = new UnlimitedInt("2");

//     UnlimitedInt *d = new UnlimitedInt("1");

//     UnlimitedRational *obj1 = new UnlimitedRational(a, b);

//     UnlimitedRational *obj2 = new UnlimitedRational(c, d);
//     cout << UnlimitedInt::sub(b, d)->to_string() << endl;
//     cout << obj1->get_frac_str() << " ";
//     cout << obj2->get_frac_str() << " ";
//     cout << UnlimitedRational::div(obj1, obj2)->get_frac_str();

//     delete a, b, c, d;
// }