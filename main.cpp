#include <iostream>
#include "./include/big_uint.h"

using AG::Big_uint;

int main()
{
	Big_uint::initNumSystem();
	

	Big_uint res,
		a( "10000043053454543535834573459347593475834759437594375394573984543573453475983475984759348543875678346587346587346587435678436587346583475643785643875643786587987837459834754376534583465874365873465873465784365874365873465837465438756348756438756348756435"),
		b ( "34857634785633456545655323424534565435443534534534534534534534541212000012121212121212324325435654654234378567438569324783849895638497563847965348795638475683475638476583724965897324659837426592834756943875692378465923847568347563847658473657843658743568");


	res = a * b;
//	res = res * res * a * a * a * b * b * b;
//	res = res * res * res * res * res * res * res * a * a * a * b * a * b + 100;
//	res = res * res * res * res * res;
//	res = res * a * b * a * b * res * res;
//
	std::ofstream f;
	f.open("result.txt");
	if (f.is_open())
	{
		res.print(f);
		f.close();
	}


	return 0;
}
