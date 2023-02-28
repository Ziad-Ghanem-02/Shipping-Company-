#include<iostream>
#include "Truck.h"
#include "UI.h"
#include "Time.h"
#include "Company.h"
using namespace std;

int main()
{
	Company shipping;
	UI* u =shipping.GetUI();
	string filename=u->ReadStringFromUser();
	int mode = u->ReadIntFromUser();
	shipping.SetFileName(filename);
	shipping.ReadInputFile();
	shipping.Phase2(mode);
	system("pause");
	return 0;
}