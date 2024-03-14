#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
#define READ_END 0
#define WRITE_END 1

int* find()
{
	int *A = new int[2];
	int numLines = 0;
	int lineLength = 0;
	int Length = 0;
	char buf[1];
	ssize_t size = 1; // Initialize size
	int file = open("input.txt", O_RDONLY, S_IRUSR);
	while(size>0)
	{
		size = read(file, buf, sizeof(buf));
		if(buf[0] == '\n')
		{
			numLines++;
			lineLength = 0;
		}
		else
		{
			lineLength++;
			Length = lineLength;
		}
	}
	cout<<"Number of Lines = "<<numLines-1<<endl;
	cout<<"Line Length = "<<Length<<endl;
	A[0]=numLines-1;
	A[1]=Length;
	return A;
}

char** sep(int r, int c) 
{
    char** arr = new char*[25];
    for (int i = 0; i < 25; i++)
        arr[i] = new char[50];

    char buf[1];
    int row = 0;
    int col = 0;
    ssize_t size = 1; // Initialize size
    int file = open("input.txt", O_RDONLY, S_IRUSR);

    while (size > 0) 
    {
        size = read(file, buf, sizeof(buf));
        if (size > 0 && buf[0] != '\n') 
            arr[row][col++] = buf[0];
        else
        {
            arr[row++][col] = '\0';
            col = 0;
        }
    }
    return arr;
}

string rem(char row[25][50], int r, int c)
{
	string s;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (row[i][j] != '0' && row[i][j] != '1' && row[i][j] != '2' && row[i][j] != '3' && row[i][j] != '4' && row[i][j] != '5' && row[i][j] != '6' && row[i][j] != '7' && row[i][j] != '8' && row[i][j] != '9')
			{
				//row[i][j] = ' ';
				s+=' ';
			}
			else
			{
				s+=row[i][j];
			}
		}
	}
	return s;
}

int main()
{
	int*arr=find();
	int c=arr[1];
	int r=arr[0];
	cout<<"===============================\n";
	
	int fd[2];
	pipe(fd);

	int pid = fork();
	if (pid > 0)
	{
		//cout<<"               IN PARENT BLOCK\n";
		close(fd[READ_END]);
		//cout<<r<<" "<<c<<endl;
		char**row;
		row = sep(r,c);
		for(int i = 0; i < r; i++)
		{
			cout<<row[i]<<" SENT\n";
			write(fd[1], row[i], 25);
		}
		cout<<"===============================\n";
		close(fd[WRITE_END]);
		wait(NULL);
		exit(0);
	}
	else
	{
		//cout<<"               IN CHILD BLOCK\n";
		close(fd[WRITE_END]);
		
		char row[25][50];
		for(int i = 0; i < r; i++)
		{
			read(fd[READ_END], row[i], 25);
			cout<<row[i]<<" RECIEVED\n";
		}
		cout<<"===============================\n";
		close(fd[READ_END]);
		string s;
		s=rem(row,r,c);
		const char *args[] = {"./s", s.c_str(), NULL};
    		execvp(args[0], const_cast<char *const *>(args));
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		exit(0);
	}
}
