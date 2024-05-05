#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <limits>
using namespace std;
//sort f1.txt | grep box -i
//cat fifo1 | grep ls | wc -l &
//sort ls.dat | tee fifo1 | wc -l
int argvSize = 15;
std::vector<string> history;
bool redirectInput, redirectOutput, skip, usePipe;
string input, inputFileName, outputFileName, red = "\033[91m", blue = "\033[34m", orange = "\033[38;5;208m", reset = "\033[0m", shellTXT = red + "woro@shell" + reset + ":" + blue + "~" + reset + "$ ", bgshellTXT = orange + "(bg)" + reset + ":" + blue + "~" + reset + "$ ";

void Tokenization(string input, char* argv[])
{
	int r = 0;
	int c = 0;
	for (int i = 0; i < strlen(input.c_str()); i++)
	{
		if (input[i] == '&')
			i++;
		else if (input[i] == '\0')
		    break;
		else if (input[i] == '<')
		{
		    redirectInput = true;
		    i++; 
		    while (i < strlen(input.c_str()) && input[i] == ' ')
		        i++;
		    int filenameStart = i;
		    while (i < strlen(input.c_str()) && input[i] != ' ')
		        i++;
		    inputFileName = input.substr(filenameStart, i - filenameStart);
		}
		else if (input[i] == '>')
		{
		    redirectOutput = true;
		    i++;
		    while (i < strlen(input.c_str()) && input[i] == ' ')
		        i++;
		    int filenameStart = i;
		    while (i < strlen(input.c_str()) && input[i] != ' ')
		        i++;
		    outputFileName = input.substr(filenameStart, i - filenameStart);
		}
		else if (input[i] == ' ')
		{
			c = 0;
			r++;
		}
		else
		{
			if (argv[r] == NULL)
			{
				argv[r] = new char[40];
				memset(argv[r], 0, 40);
			}
			argv[r][c] = input[i];
			c++;
		}
	}
}

void PrintCommands(char* argv[])
{
	for(int i=0; i<argvSize && argv[i]!=NULL; i++)
		cout<<"command "<<i+1<<": "<<argv[i]<<endl;
}

void PrintHistory()
{
	int count = history.size();
    for (int i = count - 1; i >= 0; i--)
		cout<<i+1<<": "<<history[i]<<endl;
}

bool containsExit(string input, string s = "exit") 
{
	size_t found = input.find(s);
	return (found != string::npos);
}

void rightShift(char* argv[])
{
	string command;
	char* new_argv[4] = {NULL};
	for (int i = 0; i < argvSize; i++)
	{
		if(argv[i]==NULL)
			break;
		command += argv[i];
		command+=' ';
		argv[i]=NULL;
	}

	string t = "./t";
	new_argv[0]=strdup(t.c_str());
	new_argv[1]=strdup(command.c_str());

	for (int i = 0; i < 2; i++)
		argv[i] = new_argv[i];
}

int main()
{
	cout << shellTXT;
	getline(cin, input);
	input += '\0';

	char* argv[argvSize]={NULL};
	skip = false, usePipe = false, redirectInput = false, redirectOutput = false;
	
	if(containsExit(input))
		return 0;
	else if(containsExit(input, "history"))
	{	
		PrintHistory();
		skip = true;
	}
	if(!skip)
	{
		bool cond_1 = containsExit(input, "!!"), cond_2 = containsExit(input, "!");
		if(cond_1 || cond_2)
		{
			if(cond_1)
			{
				if(!history.empty())
				{
					//cout<<history[history.size() - 1]<<" to be executed\n";
					Tokenization(history[history.size() - 1], argv);
					if(history.size()<=10)
						history.push_back(history[history.size() - 1]);
					input = history[history.size() - 1];
				}
				else
					cout<<"No commands in history"<<endl;
			}
			else if(cond_2)
			{
				if(input[1] - '0'<= history.size()) // to fix !0 and !10
				{
					Tokenization(history[(input[1] - '0') - 1], argv);
					if(history.size()<=10)
						history.push_back(history[(input[1] - '0') - 1]);
					input = history[(input[1] - '0') - 1];
				}
				else
					cout<<"No such command in history"<<endl;
			}
		}
		else
		{
			Tokenization(input, argv);
			if(history.size()!=10)
				history.push_back(input);
		}

		if(containsExit(input,"|"))
		{
			rightShift(argv);
			usePipe = true;
			int ret = fork();
			if(ret==0)
				execvp(argv[0], argv);
			else
			{
				if (input.find("&") == string::npos)
					wait(NULL);
				else
					cout<<bgshellTXT;
			}
		}
		if(!usePipe)
		{
			int ret = fork();
			if (ret == 0) 
			{
				//cout<<"			IN CHILD BLOCK\n";
				
				if (redirectInput)
				{
					int inputFile = open(inputFileName.c_str(), O_RDONLY);
					dup2(inputFile, STDIN_FILENO);
					close(inputFile);
				}
				if (redirectOutput)
				{
					int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
					dup2(outputFile, STDOUT_FILENO);
					close(outputFile);
				}
				
				execvp(argv[0],argv);
			}
			else
			{
				//cout<<"			IN PARENT BLOCK\n";

				if (input.find("&") == string::npos)
					wait(NULL);
				else
					cout<<bgshellTXT;
			}  
		}
	}
	main();
}
