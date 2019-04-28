#ifndef __CSVLoader_H__
#define __CSVLoader_H__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/*csv��������*/
class CSVLoader
{
public:
	CSVLoader();
	~CSVLoader();

	//����csv�ļ�
	bool loadCSV(const std::string& filename);
	//�����ַ���
	void loadStr(const std::string& text);

	//������һ��
	void skip(int num=1);

	//�Ƿ�����һ��
	bool hasNextLine();

	int nextInt();
	float nextFloat();
	std::string nextStr();
private:
	void readLine();
private:
	//�Ƿ��и�����
	bool _hasMore;
	//�ָ���
	std::string _token;
	std::stringstream _reader;
	std::vector<std::string> _queue;
};
#endif