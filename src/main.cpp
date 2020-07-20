#include <Vtn.hpp>
#include <iostream>

int main()
{
	Ventana vtn1({500, 500}, L"Owo");
	Ventana vtn2({500, 500}, L"Uwu");

	std::deque<std::string> events;
	while ((vtn1 >> events))
	{
		for (std::string e: events)
		{
			if (e == "closed") vtn1.close();
			if (e == "mouse moved") std::cout << "1: mouse moved" << std::endl;
		}
		if (vtn2 >> events)
		{
			for (auto e: events)
			{
				if (e == "closed") vtn2.close();
				if (e == "mouse moved") std::cout << "2: mouse moved" << std::endl;
			}
		}
	}
	return 0;
}
