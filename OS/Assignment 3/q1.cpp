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

string input;
bool redirectInput;
bool redirectOutput;
string inputFileName, outputFileName;
bool skip = false;
std::vector<string> history;
std::vector<string> history_backup;
bool usePipe;

void Tokenization(string input, char* argv[], char* argv_after[])
{
	//cout<<"\""<<input<<"\" to be tokened\n";
	int r = 0;
	int c = 0;

	for (int i = 0; i < strlen(input.c_str()); i++)
	{
		if (input[i] == '&')
		{
			i++;
		}
		if (input[i] == '\0')
		    break;
		if (input[i] == '<')
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
		if (input[i] == '>')
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
	for(int i=0; i<10 && argv[i]!=NULL; i++)
		cout<<"command "<<i+1<<": "<<argv[i]<<endl;
}

void PrintHistory()
{
	int count = history.size();
    for (int i = count - 1; i >= 0; i--)
	{
		cout<<i+1<<": "<<history[i]<<endl;
	}
	
}

bool containsExit(string input, string s = "exit") 
{
	size_t found = input.find(s);
	return (found != string::npos);
}

void rightShift(char* argv[])
{
	char* new_argv[4] = {NULL};
	string command;
	for (int i = 0; i < 12; i++)
	{
		if(argv[i]==NULL)
			break;
		command += argv[i];
		command+=' ';
		argv[i]=NULL;
	}
	//cout<<"CMD = "<<command<<endl;
	string t = "./t";
	new_argv[0]=strdup(t.c_str());
	new_argv[1]=strdup(command.c_str());

	for (int i = 0; i < 2; i++)
	{
		argv[i] = new_argv[i];
	}
	
	// string s = "./test.cpp";
	// new_argv[0] = strdup(s.c_str());

	// for (int i = 0; i < 10; ++i) 
	// {
    // 	argv[i] = new_argv[i];
    // }
}

string shellTXT = "\033[38;2;255;0;0mworo@shell\033[0m:\033[34m~\033[0m$ ";

int main()
{
	cout << shellTXT;
	getline(cin, input);
	int fd[2];
	usePipe = false;
	redirectInput = false;
	redirectOutput = false;
	char* argv[]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	char* argv_after[]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	//1
	input += '\0';
	if(containsExit(input))
		return 0;
	if(containsExit(input, "history"))
	{	
		PrintHistory();
		skip = true;
	}
	if(!skip)
	{
		if(containsExit(input, "!!") || containsExit(input, "!"))
		{
			if(containsExit(input, "!!"))
			{
				if(!history.empty())
				{
					//cout<<history[history.size() - 1]<<" to be executed\n";
					Tokenization(history[history.size() - 1], argv, argv_after);
					input = history[history.size() - 1];
					if(history.size()!=10)
						history.push_back(history[history.size() - 1]);
					//argv = history[history.size() - 1];
				}
				else
					cout<<"No commands in history"<<endl;
			}
			else if(containsExit(input, "!"))
			{
				if(input[1] - '0'<= history.size())
				{
					//cout<<history[(input[1] - '0') - 1]<<" to be executed\n";
					Tokenization(history[(input[1] - '0') - 1], argv, argv_after);
					input = history[(input[1] - '0') - 1];
					if(history.size()!=10)
						history.push_back(history[(input[1] - '0') - 1]);
					//argv = history[input[1] - 1];
				}
				else
					cout<<"No such command in history"<<endl;
			}
		}
		else
		{
			//cout<<"Tokening...";
			Tokenization(input, argv, argv_after);
			//cout<<"Tokening ended\n";

			if(history.size()!=10)
				history.push_back(input);
		}

		if(containsExit(input,"|") )
		{
			rightShift(argv);
			usePipe = true;
			//cout<<"to be exe by test.cpp\n\n";
			int ret = fork();
			if(ret==0)
			{
				execvp(argv[0], argv);
			}
			else
			{
				if (input.find("&") == string::npos)
					wait(NULL);
				else
				{
					cout<<"\b\b\b\b\033[38;2;255;165;0m(bg):~\033[0m$ ";
				}
			}
		}
		// cout<<"Before Pipe: ";
		//PrintCommands(argv);
		// cout<<"After Pipe: ";
		// PrintCommands(argv_after);

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
				exit(0);
			}
			else
			{
				//cout<<"			IN PARENT BLOCK\n";

				if (input.find("&") == string::npos)
					wait(NULL);
				else
				{
					//printf("Executing concurrently...\n");
					cout<<"\b\b\b\b\033[38;2;255;165;0m(bg):~\033[0m$ ";
				} 
			}  
		} 
		else
		{
			//cout<<"skipping\n\n"; 

		}
	}
	skip = false;
	main();
}
