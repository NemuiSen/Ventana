#include <Vtn.hpp>
#include <iostream>

int main()
{
	Vtn vtn1({500, 500}, L"Owo");
	Vtn vtn2({500, 500}, L"Uwu");

	std::deque<std::string> events;
	while (vtn2 >> events)
	{
		for (std::string e: events)
		{
			if (e == "closed") vtn2.close();
			if (e == "mouse moved") std::cout << "mouse moved" << std::endl;
		}
		if (vtn1 >> events)
		{
			for (auto e: events) if (e == "closed") vtn1.close();
		}
	}
	return 0;
}
