#include <iostream>

#include "CSVLoader.h"

using namespace std;

int main()
{
	CSVLoader* loader = new CSVLoader();

	if (loader->loadCSV("test.csv"))
	{
		//跳过第一行
		loader->skip(1);

		while (loader->hasNextLine())
		{
			int id = loader->nextInt();
			std::string name = loader->nextStr();
			int hp = loader->nextInt();
			int mp = loader->nextInt();
			int atk = loader->nextInt();
			float f = loader->nextFloat();

			cout << id << "," << name << "," << hp << "," << mp << atk << f << endl;
		}
	}

	delete loader;
	return 0;
}