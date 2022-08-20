#include <iostream>

#include <limits>
#include <algorithm>

long long kadanesAlgorithm(const int* arr, int n, int& savedL, int& savedR)
{
	//int savedL = 0, savedR = 0;
	long long savedAcc = -std::numeric_limits<long long>::max();
	long long acc = 0;
	for (int l = 0, r = 0; r < n; r++)
	{
		acc += arr[r];
		if (acc > savedAcc)
		{
			savedAcc = acc;
			savedL = l;
			savedR = r;
		}
		if (acc < 0)
		{
			l = r + 1;
			acc = 0;
		}
	} 
	return savedAcc;
}

void test(const std::initializer_list<int>& arr)
{
	int pL, pR;
	auto sum = kadanesAlgorithm(arr.begin(), arr.size(), pL, pR);
	std::cout << "pL = " << pL << "  / pR = " << pR << " / sum = " << sum << std::endl;
}

int main() 
{
	test({ 1, 2, 3, -2, 5 });
	test({ -1, -2, -3, -4 });
	test({ 1,  2, -4,  2,  4, -5,  1 });
	test({ 74, -72, 94, -53, -59, -3, -66, 36, -13, 22, 73, 15, -52, 75 });
	test({ 9, -51, -20, -13, -51, 40, -21, 75, -24, 29, -86, 5, -38, 15, 48, -87, -9, 42, 39, 64, 47, -63, 22, -81, -20, -100, 28 });
	test({ -47, 43, 94, -94, -93, -59, 31, -86 });

	return 0;
}
