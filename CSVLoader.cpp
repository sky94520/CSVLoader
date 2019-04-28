#include "CSVLoader.h"

CSVLoader::CSVLoader()
	:_hasMore(false)
	,_token(",")
{
}

CSVLoader::~CSVLoader()
{
}

bool CSVLoader::loadCSV(const std::string& filename)
{
	std::ifstream in;
	in.open(filename);

	//���ļ�ʧ��
	if (!in.is_open()) 
		return false;
	//��λ���ļ���ĩβ
	in.seekg(0, std::ios::end);
	//��ȡ�ܳ���
	int size = (int)in.tellg();

	char* buffer = new char[size + 1];
	memset(buffer, '\0', size + 1);

	//��ȡ
	in.seekg(0, std::ios::beg);
	in.read(buffer, size);
	//�ر��ļ�
	in.close();

	//���ñ���
	_reader = std::stringstream(buffer);
	_hasMore = true;

	//�ͷű���
	delete[] buffer;

	return true;
}

void CSVLoader::loadStr(const std::string& text)
{
	_reader = std::stringstream(text);
	_hasMore = true;
}

void CSVLoader::skip(int num)
{
	std::string src;
	int index = 0;

	//��ȡһ��
	while (index < num)
	{
		if (getline(_reader, src))
		{
		}
		else
		{
			_hasMore = false;
			return;
		}

		index += 1;
	}
}

bool CSVLoader::hasNextLine()
{
	if (_queue.size() > 0)
		return true;
	else if (_hasMore)
	{
		this->readLine();
		return _queue.size() > 0;
	}
	return false;
}

int CSVLoader::nextInt()
{
	//��ȡ
	const std::string& token = _queue.front();
	int number = std::stoi(token);
	_queue.erase(_queue.begin());

	return number;
}

float CSVLoader::nextFloat()
{
	//��ȡ
	const std::string& token = _queue.front();
	float number = std::stof(token);
	_queue.erase(_queue.begin());

	return number;
}

std::string CSVLoader::nextStr()
{
	std::string token = _queue.front();
	_queue.erase(_queue.begin());

	return token;
}

void CSVLoader::readLine()
{
	std::string src;
	//��ȡһ��,֮��Ѷ�ȡ���ĵ��ʱ��浽_queue��
	if (getline(_reader, src))
	{
		size_t nend = 0;
		size_t nbegin = 0;
		size_t tokenSize = _token.size();

		while (nend != std::string::npos)
		{
			nend = src.find(_token, nbegin);
			if (nend == std::string::npos)
				_queue.push_back(src.substr(nbegin, src.length() - nbegin));
			else
			{
				_queue.push_back(src.substr(nbegin, nend - nbegin));
				nbegin = nend + tokenSize;
			}
		}//end while
	}//end if
	else
		_hasMore = false;
}
