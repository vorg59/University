#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main(int args, char* argv[])
{
	string s = argv[1];
	//cout<<s<<endl;
	int digit = 0;
	int sum = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if(isdigit(s[i]))
		{
			digit = s[i] - '0';
			i++;
			while (i<s.length() && s[i]!=' ')
			{
				digit = (digit * 10) + (s[i] - '0');
				i++;
			}
			sum += digit;
		}
	}
	cout << "Sum = " << sum << endl;
	exit(1);
	return 0;
}
