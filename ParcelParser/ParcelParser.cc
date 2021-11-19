#pragma once
#include "ParcelParser.h"
#include "Printa/printa.hpp"
#include "crypt.hpp"
ParcelParser::ParcelParser(double x, double y)
{
    this->categorize_normal(x, y);
}
ParcelParser::ParcelParser(double a, double b, double c)
{
    this->categorize_by_volume(a, b, c);
}

void ParcelParser::print_info() {
    if (this->category == _unknown || this->category == _oversize) {
        printa->print<fail>("Package Over or Under sized\n");
        return;
    }

    if (this->ex_type == ex_8)
    {
        printa->print<loading_salmon>(E_("---New Package Obj---\n"));
        printa->print<loading_violet>(E_("Loaded Information by Volume\n"));

        if(this->category == _small) 
            printa->print<ok>(E_("Package Category: S\n"), this->category);
        if (this->category == _medium)
            printa->print<ok>(E_("Package Category: M\n"), this->category);
        if (this->category == _large)
            printa->print<ok>(E_("Package Category: L\n"), this->category);

        printa->print<ok>(E_("Package Width:\t{} dm\n"), this->width);
        printa->print<ok>(E_("Package Lenght:\t{} dm\n"), this->lenght);
        printa->print<ok>(E_("Package Height:\t{} dm\n"), this->height);
        printa->print<ok>(E_("Package Volume:\t{} dm^3\n"), this->volume);
        printa->print<ok>(E_("Package Price:\t{} Euro\n"), this->price);
        printa->print<loading>(E_("---------------------"));
    }
    if (this->ex_type == ex_7)
    {
        printa->print<loading_salmon>(E_("---New Package Obj---\n"));
        printa->print<loading_violet>(E_("Loaded Information by SUM\n"));

        if (this->category == _small)
            printa->print<ok>(E_("Package Category: S\n"), this->category);
        if (this->category == _medium)
            printa->print<ok>(E_("Package Category: M\n"), this->category);
        if (this->category == _large)
            printa->print<ok>(E_("Package Category: L\n"), this->category);

        printa->print<ok>(E_("Package Width:\t{} cm\n"), this->width);
        printa->print<ok>(E_("Package Height:\t{} cm\n"), this->height);
        printa->print<ok>(E_("Package Price:\t{} Euro\n"), this->price);
        printa->print<loading>(E_("---------------------"));
    }


}
//Private

void ParcelParser::categorize_normal(double x, double y)
{
    this->ex_type = ex_7;

    this->width = x;
    this->height = y;

    double d = x + y;
   
    if (d <= 50.0) {
        this->category = _small;
        this->price = 4.00;
    }
    if (d > 50.0 && d <= 80.0) {
        this->category = _medium;
        this->price = 6.00;
    }
    if (d > 80.0 && d <= 120.0) {
        this->category = _large;
        this->price = 9.00;
    }
    else if (d > 120) {
        this->category = _oversize;
        this->price = -1;
    }
}
void ParcelParser::categorize_by_volume(double a, double b, double c)
{
    this->ex_type = ex_8;

    this->width = a / 10;   // cm to dm
    this->lenght = b / 10;  // cm to dm
    this->height = c / 10;  // cm to dm

    this->volume = (this->width * this->lenght * this->height);

    double d = this->volume;

    if (d <= 60.0) {
        this->category = _small;
        this->price = 4.00;
    }
    if (d > 60.0 && d <= 300.0) {
        this->category = _medium;
        this->price = 6.00;
    }
    if (d < 1.0) {
        this->category = _oversize;
        this->price = -1;
    }
    if (d > 300.0 && d <= 800.0) {
        this->category = _large;
        this->price = 9.00;
    }
    else if (d > 800.0) {
        this->category = _oversize;
        this->price = -1;
    }
}
