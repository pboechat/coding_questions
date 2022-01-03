/*
Write two conversion routines. The first routine converts a string to a signed integer. 
You may assume that the string contains only digits and the minus character ('-'), 
that it is a properly formatter integer number, and thatthe number is within the range of 
an int type. The second routine converts a signed integer stored as an int back to a string.
*/

#include <iostream>
#include <string>

const int c_max_positive = 0x7fffffff;
const int c_max_negative = 0x80000000;

int str_to_int(const std::string& str)
{
    auto neg = str[0] == '-';
    auto len = str.size();
    auto max = len;
    if (neg)
        max -= 1;
    int mult = 1, total = 0;
    for (size_t i = 1; i <= max; ++i, mult *= 10)
        total += (int)(str[len - i] - '0') * mult;
    if (neg)
        total = -total;
    return total;
}

enum class _type : char { positive = 0, negative = 1, max_negative = 2 };

std::string int_to_str(int n)
{
    auto type = n > 0 ? _type::positive : _type::negative;
    int i = 0;
    char str[11]; // 2^31 ~= 2 billion, which can be represented w/ 10 digits (plus one for sign)
    if (type != _type::positive)
    {
        str[i++] = '-';
        if (n == c_max_negative)
        {
            n++;
            type = _type::max_negative;
        }
        n = -n;
    }
    do
    {
        int c = n % 10;
        n /= 10;
        str[i++] = (char)(c + '0');
    } while (n > 0);
    str[i] = 0;
    int s = 0;
    if (type != _type::positive)
        s = 1;
    for (int j = 0; j < i / 2; ++j)
    {
        auto& a = str[s + j];
        auto& b = str[i - j - 1];
        auto tmp = a;
        a = b;
        b = tmp;
        if (j == 0 && type == _type::max_negative)
            b += 1;
    }
    return str;
}

int main() 
{
    // str to int
    std::cout << "732 == " << str_to_int("732") << std::endl;
    std::cout << "1 == " << str_to_int("1") << std::endl;
    std::cout << "0 == " << str_to_int("0") << std::endl;
    std::cout << "-1 == " << str_to_int("-1") << std::endl;

    // int to str
    std::cout << "732 == " << int_to_str(732) << std::endl;
    std::cout << "1 == " << int_to_str(1) << std::endl;
    std::cout << "0 == " << int_to_str(0) << std::endl;
    std::cout << "-1 == " << int_to_str(-1) << std::endl;
    std::cout << c_max_positive << " == " << int_to_str(c_max_positive) << std::endl;
    std::cout << c_max_negative << " == " << int_to_str(c_max_negative) << std::endl;

    return 0;
}