/* Write a recursive function to multiply two positive integers without using the * operator
(or / operator). You can use addition, subtraction and bit shifting, but you should minimize 
the number of those operations. */

#include <algorithm>
#include <iostream>

int recursiveMultiplication(int n, int op2, int acc)
{
    if ((op2 & 1) != 0)
    {
        if (acc == 0)
        {
            acc = n;
        }
        else
        {
            acc += n;
        }
    }
    op2 = op2 >> 1;
    if (op2 == 0)
        return acc;
    n += n;
    return recursiveMultiplication(n, op2, acc);
}

int recursiveMultiplication(int op1, int op2)
{
    if (op1 < op2)
    {
        std::swap(op1, op2);
    }
    return recursiveMultiplication(op1, op2, 0);
}

void test(int op1, int op2)
{
    std::cout << op1 << " * " << op2 << " = " << recursiveMultiplication(op1, op2) << std::endl;
}

int main()
{
    test(8, 1);
    test(3, 8);
    test(8, 5);
    test(8, 8);
    return 0;
}