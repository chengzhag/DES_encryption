// DES_encryption.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <bitset>
#include <iostream>
#include <string>
#include <fstream>
#include "encyption.h"

using namespace zhang;


int main()
{
	//cout << "功能选择（1加密/2解密）：" ;
	//int option;
	//cin >> option;
	//switch (option)
	//{
	//case 1:
	//{
	//	cout << "加密文件：";
	//	string file;
	//	cin >> file;
	//	cout << "密钥（8个字符）：";
	//	string k;
	//	cin >> k;
	//	key = charToBitset(k.c_str());

	//	// 将文件 file 加密到 file.des 中
	//	ifstream in;
	//	ofstream out;
	//	in.open(file, ios::binary);
	//	out.open(file.append(".des"), ios::binary);
	//	bitset<64> plain;
	//	while (in.read((char*)&plain, sizeof(plain)))
	//	{
	//		bitset<64> cipher = encrypt(plain);
	//		out.write((char*)&cipher, sizeof(cipher));
	//		plain.reset();  // 置0
	//	}
	//	in.close();
	//	out.close();
	//}
	//break;
	//	
	//case 2:
	//{
	//	cout << "解密文件：";
	//	string file;
	//	cin >> file;
	//	cout << "密钥（8个字符）：";
	//	string k;
	//	cin >> k;
	//	key = charToBitset(k.c_str());

	//	// 解密 file.des，并写入 file
	//	ifstream in;
	//	ofstream out;
	//	in.open(file, ios::binary);
	//	out.open(file.substr(0, file.size() - 4), ios::binary);
	//	bitset<64> plain;
	//	while (in.read((char*)&plain, sizeof(plain)))
	//	{
	//		bitset<64> temp = decrypt(plain);
	//		out.write((char*)&temp, sizeof(temp));
	//		plain.reset();  // 置0
	//	}
	//	in.close();
	//	out.close();
	//}
	//	break;
	//default:
	//	cout << "重新选择功能" << endl;
	//	break;
	//}
	//

	//return 0;
	
	string k = "12345678";
	desEncryption des(bitset<64>(*((uint64_t*)(k.c_str()))));
	string s = "romantic";
	bitset<64> plain = bitset<64>(*((uint64_t*)(s.c_str())));
	// 密文写入 a.txt
	bitset<64> cipher = des.encrypt(plain);
	fstream file1;
	file1.open("a.txt", ios::binary | ios::out);
	file1.write((char*)&cipher, sizeof(cipher));
	file1.close();

	// 读文件 a.txt
	bitset<64> temp;
	file1.open("a.txt", ios::binary | ios::in);
	file1.read((char*)&temp, sizeof(temp));
	file1.close();

	// 解密，并写入文件 b.txt
	bitset<64> temp_plain = des.decrypt(temp);
	file1.open("b.txt", ios::binary | ios::out);
	file1.write((char*)&temp_plain, sizeof(temp_plain));
	file1.close();

	return 0;
}

