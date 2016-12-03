// LightPainterCompanion.cpp : Defines the entry point for the console application.

#include <iostream>
#include <fstream>
#include <sstream>
#include "dll\CImg.h"
//for GetConsoleHeight, windows > win2000
#define _WIN32_WINNT 0x0500
#include <Windows.h> // Has to be after win32_winnt



using namespace cimg_library;

void padIntegers(int R, int G, int B, std::string* pR, std::string* pG, std::string* pB) {
	std::ostringstream Rss;
	std::ostringstream Gss;
	std::ostringstream Bss;
	if (R < 10) //RED
		Rss << "  " << R;
	else if (R < 100)
		Rss << " " << R;
	else
		Rss << R;
	if (G < 10) //GREEN
		Gss << "  " << G;
	else if (G < 100)
		Gss << " " << G;
	else
		Gss << G;
	if (B < 10) //BLUE
		Bss << "  " << B;
	else if (B < 100)
		Bss << " " << B;
	else
		Bss << B;
	(*pR) = Rss.str();
	(*pG) = Gss.str();
	(*pB) = Bss.str();
}

int main()
{
	std::cout << "Starting up the bitmap conversion.\n";

	float pixvalR; //0-255
	float pixvalG;
	float pixvalB;
	std::string *padded_pixvalR = new std::string; //0-255
	std::string *padded_pixvalG = new std::string;
	std::string *padded_pixvalB = new std::string;

	float byteCounter = 0;

	CImg<float> image("input.bmp");
	CImgDisplay main_disp(image);

	//resize the window so the output fits in better
	HWND console = GetConsoleWindow();
	//MoveWindow(window_handle, x, y, width,height, redraw_window);
	MoveWindow(console, 40, 40, 800, 1000, TRUE);

	std::cout << "Width: " << image.width() << " px";
	std::cout << " Height: " << image.height() << " px\n\n";
	std::cout << "Showing red channel:\n";

	std::ofstream out("output.txt");

	//Loopyloop
	for (int x = 0; x < image.width(); x++) {
		for (int y= 0; y < image.height(); y++) {
			pixvalR = image(x, y, 0, 0); // read red val at coord x,y
			pixvalG = image(x, y, 0, 1); // read green val at coord x,y
			pixvalB = image(x, y, 0, 2); // read blue val at coord x,y

			padIntegers(pixvalR, pixvalG, pixvalB, padded_pixvalR, padded_pixvalG, padded_pixvalB);

			std::cout << (*padded_pixvalR);
			std::cout << ",";

			//First one doesn't have comma before it.
			if (y == 0 && x == 0) {
				out <<  (*padded_pixvalR);
			}
			else {
				out << "," << (*padded_pixvalR);
			}
			out << "," << (*padded_pixvalG);
			out << "," << (*padded_pixvalB);

			byteCounter += 3;
		}
		std::cout << "\n";
		out << "\n";
	}

	out.close();

	std::cout << "\nSize\n" << byteCounter << " bytes.\n";
	std::cout << byteCounter / 1000 << " kB\n";
	std::cout << byteCounter / 1000000 << " MB\n";

	std::cout << "\n";
	system("pause");

	delete padded_pixvalR;
	delete padded_pixvalG;
	delete padded_pixvalB;

    return 0;
}

