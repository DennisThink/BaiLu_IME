#include <iostream>
#include "RegKeyFunction.hpp"
int main(int argc,char * argv[])
{
	std::cout << "Please Input a number: 1 for register and 2 for unregister" << std::endl;
	int nChoice = 0;
	std::cin >> nChoice;
	if (nChoice == 1)
	{
		CRegKeyFunction::InstallRegKeyValues();
	}
	else if(nChoice == 2)
	{
		CRegKeyFunction::UnInstallRegKeyValues();
	}
	std::cout << "Finished" << std::endl;
	int nStop = 0;
	std::cin >> nStop;
	return 0;
}