/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>
using namespace std;
// resulting array.convert into string then call string constructor then return that.
string multiplyStrings(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--)
        {
            int product = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = product / 10;
            result[i + j + 1] = (product % 10) + '0';
        }
        result[i] += carry;
    }

    int pos = result.find_first_not_of('0');
    if (pos != string::npos) // see it again
    {
        return result.substr(pos);
    }

    return "0";
}
bool big(string s1, string s2)
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
void reverse(string &str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
bool bigone(int arr1[], int arr2[], int size1, int size2)
{
    // Calculate lengths of both string
    int n1 = size1, n2 = size2;

    if (n1 < n2)
        return false;
    if (n2 < n1)
        return true;

    for (int i = 0; i < n1; i++)
        if (arr1[i] < arr2[i])
            return false;
        else if (arr1[i] > arr2[i])
            return true;

    return true;
}
string dividestring(string num, string divisor)
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
        while (big(dividend, divisor))
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
string remainder(string num, string divisor)
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
        while (big(dividend, divisor))
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

UnlimitedInt::UnlimitedInt(int i)
{
}
UnlimitedInt::UnlimitedInt(string s)
{
    // -2341, 2342
    if (s[0] == '-')
    {
        sign = -1;
        size = s.length() - 1;
    }
    else
    {
        sign = 1;
        size = s.length();
    }

    if (size != 0)
    {
        unlimited_int = new int[size];
    } // possible error
    for (int i = 0; i < size; i++)
    {
        if (s[0] == '-')
        {
            unlimited_int[i] = int(s[i + 1]) - int('0');
            continue;
        }
        unlimited_int[i] = int(s[i]) - int('0');
    }
}
UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}
int UnlimitedInt::get_size()
{
    return size;
}
int *UnlimitedInt::get_array()
{
    return unlimited_int;
}
int UnlimitedInt::get_sign()
{
    return sign;
}
string UnlimitedInt::to_string()
{
    int *a = this->get_array();
    string s = "";
    for (int i = 0; i < this->get_size(); i++)
    {
        char b = '0' + a[i];
        s.insert(s.begin() + i, b);
    }
    if (this->get_sign() < 0)
    {
        s.insert(s.begin(), '-');
    }

    return s;
}
UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    UnlimitedInt *result;
    int size1 = i1->get_size();
    int size2 = i2->get_size();

    int maxi = 0;
    if (size1 > size2)
    {
        maxi = size1;
    }
    else
    {
        maxi = size2;
    }

    string res = "";
    int carry = 0;
    int sum1;
    if ((sign1) * (sign2) >= 0)
    {
        for (int i = 0; i < maxi; ++i)
        {
            int a1 = 0;
            int a2 = 0;
            if (i < size1)
            {
                a1 = arr1[size1 - i - 1];
            }
            if (i < size2)
            {
                a2 = arr2[size2 - i - 1];
            }

            sum1 = a1 + a2 + carry;

            carry = sum1 / 10;
            int c = sum1 % 10;
            char b = '0' + c;

            res.insert(res.begin(), b);
        }

        if (carry > 0)
        {
            res.insert(res.begin(), '0' + carry);
        }
        if (sign1 < 0 || sign2 < 0)
        {
            res.insert(res.begin(), '-');
        }
        result = new UnlimitedInt(res);
        return result;
    }
    else
    {
        if (bigone(arr1, arr2, size1, size2))
        {
            for (int i = 0; i < maxi; ++i)
            {
                int a1 = 0;
                int a2 = 0;
                if (i < size1)
                {
                    a1 = arr1[size1 - i - 1];
                }
                if (i < size2)
                {
                    a2 = arr2[size2 - i - 1];
                }

                sum1 = a1 + carry - a2;

                if (sum1 < 0)
                {
                    sum1 = sum1 + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                int c = sum1;
                char b = '0' + c;

                res.insert(res.begin(), b);
            }
            int y = 0;
            while (res[y] == '0')
            {
                y++;
            }
            string res1 = res.substr(y, res.length() - y);
            if (res1.length() == 0)
            {
                res1 = "0";
            }
            if (sign1 < 0 && res1 != "0")
            {
                res1.insert(res1.begin(), '-');
            }
            result = new UnlimitedInt(res1);
            return result;
        }
        else
        {
            for (int i = 0; i < maxi; ++i)
            {
                int a1 = 0;
                int a2 = 0;
                if (i < size1)
                {
                    a1 = arr1[size1 - i - 1];
                }
                if (i < size2)
                {
                    a2 = arr2[size2 - i - 1];
                }

                sum1 = a2 + carry - a1;

                if (sum1 < 0)
                {
                    sum1 = sum1 + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                int c = sum1;
                char b = '0' + c;

                res.insert(res.begin(), b);
            }
            int y = 0;
            while (res[y] == '0')
            {
                y++;
            }
            string res1 = res.substr(y, res.length() - y);
            if (res1.length() == 0)
            {
                res1 = '0';
            }
            if (sign2 < 0 && res1 != "0")
            {
                res1.insert(res1.begin(), '-');
            }

            result = new UnlimitedInt(res1);
            return result;
        }
    }
}
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    string res;
    UnlimitedInt *result;
    int maxi = 0;
    if (size1 > size2)
    {
        maxi = size1;
    }
    else
    {
        maxi = size2;
    }

    int carry = 0;
    int sum1;
    if (sign1 * sign2 < 0)

    {
        for (int i = 0; i < maxi; ++i)
        {
            int a1 = 0;
            int a2 = 0;
            if (i < size1)
            {
                a1 = arr1[size1 - i - 1];
            }
            if (i < size2)
            {
                a2 = arr2[size2 - i - 1];
            }

            sum1 = a1 + a2 + carry;

            carry = sum1 / 10;
            int c = sum1 % 10;
            char b = '0' + c;

            res.insert(res.begin(), b);
        }

        if (carry > 0)
        {
            res.insert(res.begin(), '0' + carry);
        }
        if (sign1 < 0)
        {
            res.insert(res.begin(), '-');
        }
        result = new UnlimitedInt(res);
        return result;
    }
    else
    {
        if (sign2 < 0)
        {
            if (bigone(arr1, arr2, size1, size2))
            {
                for (int i = 0; i < maxi; ++i)
                {
                    int a1 = 0;
                    int a2 = 0;
                    if (i < size1)
                    {
                        a1 = arr1[size1 - i - 1];
                    }
                    if (i < size2)
                    {
                        a2 = arr2[size2 - i - 1];
                    }

                    sum1 = a1 + carry - a2;

                    if (sum1 < 0)
                    {
                        sum1 = sum1 + 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    int c = sum1;
                    char b = '0' + c;

                    res.insert(res.begin(), b);
                }
                int y = 0;
                while (res[y] == '0')
                {
                    y++;
                }
                string res1 = res.substr(y, res.length() - y);
                if (res1.length() == 0)
                {
                    res1 = '0';
                }
                if (res1 != "0")
                {
                    res1.insert(res1.begin(), '-');
                }

                result = new UnlimitedInt(res1);
                return result;
            }
            else
            {
                for (int i = 0; i < maxi; ++i)
                {
                    int a1 = 0;
                    int a2 = 0;
                    if (i < size1)
                    {
                        a1 = arr1[size1 - i - 1];
                    }
                    if (i < size2)
                    {
                        a2 = arr2[size2 - i - 1];
                    }

                    sum1 = a2 + carry - a1;

                    if (sum1 < 0)
                    {
                        sum1 = sum1 + 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    int c = sum1;
                    char b = '0' + c;

                    res.insert(res.begin(), b);
                }
                int y = 0;
                while (res[y] == '0')
                {
                    y++;
                }
                string res1 = res.substr(y, res.length() - y);
                if (res1.length() == 0)
                {
                    res1 = '0';
                }
                if (res1 != "0")
                {
                    res1.insert(res1.begin(), '-');
                }

                result = new UnlimitedInt(res1);
                return result;
            }
        }
        else
        {
            if (!bigone(arr1, arr2, size1, size2))
            {
                for (int i = 0; i < maxi; ++i)
                {
                    int a1 = 0;
                    int a2 = 0;
                    if (i < size1)
                    {
                        a1 = arr1[size1 - i - 1];
                    }
                    if (i < size2)
                    {
                        a2 = arr2[size2 - i - 1];
                    }

                    sum1 = a2 + carry - a1;

                    if (sum1 < 0)
                    {
                        sum1 = sum1 + 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    int c = sum1;
                    char b = '0' + c;

                    res.insert(res.begin(), b);
                }
                int y = 0;
                while (res[y] == '0')
                {
                    y++;
                }
                string res1 = res.substr(y, res.length() - y);
                if (res1.length() == 0)
                {
                    res1 = '0';
                }
                if (res1 != "0")
                {
                    res1.insert(res1.begin(), '-');
                }

                result = new UnlimitedInt(res1);
                return result;
            }
            else
            {
                for (int i = 0; i < maxi; ++i)
                {
                    int a1 = 0;
                    int a2 = 0;
                    if (i < size1)
                    {
                        a1 = arr1[size1 - i - 1];
                    }
                    if (i < size2)
                    {
                        a2 = arr2[size2 - i - 1];
                    }

                    sum1 = a1 + carry - a2;

                    if (sum1 < 0)
                    {
                        sum1 = sum1 + 10;
                        carry = -1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    int c = sum1;
                    char b = '0' + c;

                    res.insert(res.begin(), b);
                }
                int y = 0;
                while (res[y] == '0')
                {
                    y++;
                }
                string res1 = res.substr(y, res.length() - y);
                if (res1.length() == 0)
                {
                    res1 = '0';
                }

                result = new UnlimitedInt(res1);
                return result;
            }
        }
    }
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    UnlimitedInt *result1;
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    string res2;
    string res = "";
    string dividend = "";
    string divisor = "";
    string rem = "";
    for (int i = 0; i < size1; i++)
    {
        dividend = dividend + char(arr1[i] + '0');
    }
    for (int i = 0; i < size2; i++)
    {
        divisor = divisor + char(arr2[i] + '0');
    }
    res2 = multiplyStrings(dividend, divisor);

    string res1;
    int y = 0;
    if (res2[0] == '0')
    {
        while (res2[y] == '0')
        {
            y++;
        }
        res1 = res2.substr(y, res2.length() - y);
        if (res1.length() == 0)
        {
            res1 = '0';
        }
    }
    else
    {
        res1 = res2;
    }
    if (sign1 * sign2 < 0 && res1 != "0")
    {
        res1.insert(res1.begin(), '-');
    }

    result1 = new UnlimitedInt(res1);

    return result1;
}
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    UnlimitedInt *result;
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    string res = "";
    string dividend = "";
    string divisor = "";
    string rem = "";
    for (int i = 0; i < size1; i++)
    {
        dividend = dividend + char(arr1[i] + '0');
    }
    for (int i = 0; i < size2; i++)
    {
        divisor = divisor + char(arr2[i] + '0');
    }
    res = dividestring(dividend, divisor);
    rem = remainder(dividend, divisor);
    if (divisor == "0")
    {
        result = new UnlimitedInt("-0"); // intersting!!!!!!!!!
        return result;
    }
    if (sign1 * sign2 > 0)
    {

        result = new UnlimitedInt(res);
        return result;
    }
    else
    {
        if (rem == "0")
        {
            if (res != "0")
            {
                res.insert(res.begin(), '-');
            }
            result = new UnlimitedInt(res);
            return result;
        }
        else
        {
            UnlimitedInt *a1 = new UnlimitedInt(res);
            UnlimitedInt *a2 = new UnlimitedInt("1");
            UnlimitedInt *a3 = UnlimitedInt::add(a1, a2);
            string res1 = a3->to_string();
            res1.insert(res1.begin(), '-');
            result = new UnlimitedInt(res1);
            delete a1;
            delete a2;
            delete a3;
            return result;
        }
    }
}

// int main()
// {
//     string s1 = "156";
//     string s2 = "7";

//     UnlimitedInt *a = new UnlimitedInt(s1);
//     UnlimitedInt *b = new UnlimitedInt(s2);
//     UnlimitedInt *resulting;
//     UnlimitedInt *result = resulting->add(a, b);
//     UnlimitedInt *result2 = resulting->sub(a, b);
//     UnlimitedInt *result3 = resulting->mul(a, b);

//     cout << result3->to_string();
// }
