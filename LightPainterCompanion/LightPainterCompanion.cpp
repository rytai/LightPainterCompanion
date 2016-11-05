// LightPainterCompanion.cpp : Defines the entry point for the console application.
//
#include <iostream>;
#include <png.h>;

int intarvo;

int main()
{
	std::cin >> intarvo;

	std::cout << "\n";

	std::cout << "0x" << std::hex << intarvo;

	std::cout << "\n";
	system("pause");

    return 0;
}

