#ifndef PARCEL_PARSER_H_
#define PARCEL_PARSER_H_
enum categories : int   
{
	_small	= 0,
	_medium	= 1,
	_large	= 3,
	_oversize = 4,
	
	_unknown
};
enum exercise_type : int
{
	ex_7	= 0,
	ex_8	= 1,

	def
};
class ParcelParser
{
public:
	int category = _unknown;
	int ex_type = def;

	double price = -1;
	double width = -1;
	double lenght = -1;
	double height = -1;
	double volume = -1;

	ParcelParser(double x, double y); // Constructor Ü7
	ParcelParser(double a, double b, double c); // Constructor Ü8
	~ParcelParser() = default;

	void print_info();

private:
	void categorize_normal(double x, double y);
	void categorize_by_volume(double a, double b, double c);
};
#endif // !PARCEL_PARSER_H_
