#include "Tools.h"

void Tools::report(rstring info)
{
	std::cout << info << std::endl;
}

void Tools::report(rstring info, int error_code)
{
	std::cout << info + std::to_string(error_code) << std::endl;
}

void Tools::to_lower(rstring& s)
{
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
}

void Tools::to_upper(rstring& s)
{
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
	}
}

size_t Tools::cal_len(const char* start, const char* end)
{
	return (size_t)(end - start);
}

const char* Tools::find_line(const char* start, const char* end)
{
	//���ҳ���Ϊ2������-1�ж�
	for (const char* lstart = start; lstart < (end - 1); lstart++) {
		if ('\r' == lstart[0] && '\n' == lstart[1])
		{
			return &lstart[2];
		}
	}
	return nullptr;
}

const char* Tools::find_head(const char* start, const char* end)
{
	for (const char* hstart = start; hstart < (end - 3); hstart++) {
		if (hstart[0] == '\r' && hstart[1] == '\n' && \
			hstart[2] == '\r' && hstart[3] == '\n')
		{
			return &hstart[4];
		}
	}
	return nullptr;
}

const char* Tools::find_content(const char* start, const char* end, char c_end, size_t& content_len, size_t& sum_len)
{
	size_t _content_len = 0;
	const char* content_start = nullptr;
	for (const char* _start = start; _start < end; _start++)
	{
		if (content_start == nullptr)
		{
			//�ҵ��ǿո�Ŀ�ʼ
			if (*_start != ' ')
			{
				content_start = _start;
				_content_len = 1;
			}
		}
		else
		{
			//��������β
			if (*_start == c_end)
			{
				content_len = _content_len;
				sum_len = cal_len(start, _start);
				return content_start;
			}
			_content_len++;
		}
	}
	return nullptr;
}