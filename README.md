# DES_encryption
- 信息安全课程作业。章程2015010912010
- C++实现的DES加密算法，基于密文反馈（CFB）实现对任意长度二进制文件的分组加密。

## 运行
1. 双击“\DES_encryption\Debug”下的DES_encryption.exe文件
1. 键入1/2选择功能，回车确认
1. 键入输入文件相对/绝对路径，若操作文件与exe在同一文件夹下，可直接键入文件名。文件名包括后缀。如“E:\Projects\学校\课堂\201701_信息安全\DES加密\DES_encryption\DES_encryption\test.txt”或“..\DES_encryption\test.txt”，回车确认
1. 键入输出文件路径，要求与3相同，回车开始加密/解密
1. 对于较大文件（100KB以上）可能需要等待较长时间（1分钟以上）

## 代码解析
程序采用面向对象的编程思路，类图如下：

![image](https://github.com/pidan1231239/DES_encryption/blob/master/%E7%B1%BB%E5%9B%BE.jpg)

### ```class encyptionAlg```
加密算法的接口
- 通过stl::bitset类进行数据交换
- 模板参数```size_t N```针对具有不同分组长度的加解密算法

### ```class desEncryption```
继承自```class encyptionAlg```类
- 重载其```setKey```、```encrypt```、```decrypt```函数
- DES算法分组长度为64，此处以64作为模板参数。

### ```class CFB```
密文反馈（CFB）算法的实现。实现原理如下图（引用自维基百科[分组密码工作模式](https://zh.wikipedia.org/wiki/%E5%88%86%E7%BB%84%E5%AF%86%E7%A0%81%E5%B7%A5%E4%BD%9C%E6%A8%A1%E5%BC%8F)）

![image](https://github.com/pidan1231239/DES_encryption/blob/master/Cfb_encryption.png)

![image](https://github.com/pidan1231239/DES_encryption/blob/master/Cfb_decryption.png)

- 通过指针聚合```desEncryption```类，在实例化时传入不同加解密算法的指针可实现同种分组加密算法通用于不同加解密算法。代码示例：
	```	
	CFB<64> cfb(
		new desEncryption
	);
	```

- 通过迭代器对文件或数据结构进行加解密，调用格式如：
	```
	cfb.encrypt(
		istreambuf_iterator<char>(infile),
		istreambuf_iterator<char>(),
		ostreambuf_iterator<char>(outfile)
	);
	```
- 在while中对迭代器按字节递进读取，填充分组，未满一组的填充0
	```
	while (inBegin != inEnd)
	{
		block.chars[index] = *inBegin;
		++inBegin;
		index++;
		if (index >= N / 8 || inBegin == inEnd)
		{
			//对block进行加密
			old.bits = alg->encrypt(old.bits);
			old.bits = old.bits^block.bits;
			for (size_t i = 0; i < index; ++i)
			{
				*outBegin = old.chars[i];
				++outBegin;
			}
			
			//清空block
			block.bits.reset();
			index = 0;
		}
	}
	```
- 利用bitset重载的操作符实现异或操作
	```
	...
	old.bits = old.bits^block.bits;
	...
	```

