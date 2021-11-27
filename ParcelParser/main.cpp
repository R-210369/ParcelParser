#pragma once
#include "ParcelParser.h"
#include "crypt.hpp"
#include "Printa/printa.hpp"
#include <iostream>

#define string_equals_yes(x) x == E_("Y") || x == E_("y") || x == E_("Yes") || x == E_("yes") || x == E_("YES")
#define string_equals_no(x) x == E_("N") || x == E_("n") || x == E_("No") || x == E_("no") || x == E_("no")

double width, lenght, height;
std::string _continue;

auto main(int argc, char** argv) -> int
{
	A:
	
	printa->project<30>(E_("ParcelParser"));
	SetConsoleTitleA(E("ParcelParser by 210369"));
	
	printa->print<loading>(E_("Package Width in cm: "));
	std::cin >> width;

	printa->print<loading>(E_("Package Lenght in cm: "));
	std::cin >> lenght;

	printa->print<loading>(E_("Package Height in cm: "));
	std::cin >> height;

	printf(E("\n"));

	ParcelParser* parcel;
/*
	Availeble Parcel Information:
		parcel->category
		parcel->ex_type
		parcel->price
		parcel->width
		parcel->lenght
		parcel->height
		parcel->volume
*/

	if(lenght == 0)
		parcel = new ParcelParser(width, height);
	else
		parcel = new ParcelParser(width, lenght, height);

	parcel->print_info();

	B:

	printa->print<loading>(E_("Would you like to review another package?\n (Y/N): "));
	std::cin >> _continue;
 
	if (string_equals_yes(_continue)) {
		delete parcel;
		system("CLS");
		goto A;
	}
		 
	if (string_equals_no(_continue)) {
		printa->print<ok>(E_("Thank you for using, ParcelParser by R-210369"));
		for (int i = 0; i < 5; i++) {
			Sleep(80);
			std::cout << ".";
		}
		Sleep(3000);
		exit(0);
	}
	else {
		printa->print<fail>(E_("Unknown Input\n"));
		Sleep(2000);
		goto B;
	}
 
	printa->print<fail>(E_("an unknown error occurred\n"));
	stay_open();
	return -1;
}
