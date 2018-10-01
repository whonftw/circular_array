#include "circular_array.hpp"
#include <iostream>
#include <vector>

int main()
{
	circular_array<int> circular_array(4);
	std::vector<int> vec(4);
	circular_array.push_back(1);
	circular_array.push_front(2);
	circular_array.push_front(3);
	circular_array.push_back(4);
	circular_array.push_front(5);
	for (std::size_t i = 0; i < circular_array.size(); ++i)
	{
		std::cout << circular_array[i] << " ";
	}
	system("pause");
}