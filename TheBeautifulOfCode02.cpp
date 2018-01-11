#include <string>
#include <iostream>
#include <vector>
using namespace std;

//求三个数的最小值
int min(int a, int b, int c) {
	if (a > b) {
		if (b > c)
			return c;
		else
			return b;
	}
	if (a > c) {
		if (c > b)
			return b;
		else
			return c;
	}
	if (b > c) {
		if (c > a)
			return a;
		else
			return c;
	}
}

//使用动态规划求解方法
int StringDistance(string &str1, int start1, int end1,
	string &str2, int start2, int end2) {
	if (start1 > end1) {
		if (start2 > end2)
			return 0;
		else
			return end2 - start2 + 1;
	}

	if (start2 > end2) {
		if (start1 > end1)
			return 0;
		else
			return end1 - start1 + 1;
	}

	if (str1[start1] == str2[start2])
		return StringDistance(str1, start1 + 1, end1, str2, start2 + 1, end2);
	else {
		int t1 = StringDistance(str1, start1 + 1, end1, str2, start2, end2);
		int t2 = StringDistance(str1, start1, end1, str2, start2 + 1, end2);
		int t3 = StringDistance(str1, start1 + 1, end1, str2, start2 + 1, end2);
		return min(t1, t2, t3) + 1;
	}
}

//递归求解方法
int StringDistance(string &str1, string &str2) {
	int len1 = str1.length(), len2 = str2.length();
	vector<vector<int> > ivec(len1 + 1, vector<int>(len2 + 1));

	//下面初始化的含义：
	//当str1长度为0时，那么两个字符串的距离就是str2的长度
	//同样，当str2长度为0， 那么两个字符串距离就是str1的长度
	for (int i = 0; i < len1 + 1; ++i)
		ivec[i][0] = i;
	for (int i = 0; i < len2 + 1; ++i)
		ivec[0][i] = i;

	for(int i = 1; i <= len1; ++i) {
		for (int j = 1; j <= len2; ++j) {
			if (str1[i - 1] == str2[j - 1])
				ivec[i][j] = ivec[i - 1][j -1];
			else
				ivec[i][j] = min(ivec[i][j - 1], ivec[i - 1][j], ivec[i - 1][j - 1]) + 1;
		}
	}
	return ivec[len1][len2];
}
int main() {
	string str1, str2;
	cin >> str1 >> str2;
	//int dis = StringDistance(str1, 0, str1.length() - 1,	str2, 0, str2.length() - 1);
	int dis = StringDistance(str1,0,str1.length(), str2,0,str2.length());
    cout << dis << endl;
    
    while(1){}
    return 0;
}