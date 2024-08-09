#include "base64.h"

#include <fstream>
#include <curl/curl.h>


std::string getFileBase64Content(const char* path, bool urlencoded)
{
	const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	unsigned int bufferSize = 1024;
	unsigned char buffer[bufferSize];
	std::ifstream file_read;
	file_read.open(path, std::ios::binary);
	while (!file_read.eof())
	{
		file_read.read((char*)buffer, bufferSize * sizeof(char));
		int num = file_read.gcount();
		int m = 0;
		while (num--)
		{
			char_array_3[i++] = buffer[m++];
			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;
				for (i = 0; (i < 4); i++)
				{
					ret += base64_chars[char_array_4[i]];
				}
				i = 0;
			}
		}
	}
	file_read.close();
	if (i)
	{
		for (j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		for (j = 0; (j < i + 1); j++)
		{
			ret += base64_chars[char_array_4[j]];
		}
		while ((i++ < 3))
		{
			ret += '=';
		}
	}
	if (urlencoded)
	{
		ret = curl_escape(ret.c_str(), ret.length());
	}
	return ret;
}

std::string base64_to_url_encoded(const std::string& base64_str)
{
	std::string url_encoded_str;
	for (char c : base64_str) {
		switch (c) {
		case '+':
			url_encoded_str += "%2B";
			break;
		case '/':
			url_encoded_str += "%2F";
			break;
		case '=':
			url_encoded_str += "%3D"; // 通常Base64的结尾'='不需要编码，但如果你确实需要编码它
			break;
		default:
			url_encoded_str += c;
		}
	}
	return url_encoded_str;
}