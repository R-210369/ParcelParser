#pragma once
#include "ParcelParser.h"
#include "crypt.hpp"
#include "Printa/printa.hpp"
#include <iostream>

double width, lenght, height;

auto main(int argc, char** argv) -> int
{
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

	if(lenght == 0)
		parcel = new ParcelParser(width, height);
	else
		parcel = new ParcelParser(width, lenght, height);

	parcel->print_info();

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
	_return();
}
