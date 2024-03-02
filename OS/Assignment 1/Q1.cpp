#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
using namespace std;

string input;
bool redirectInput;
bool redirectOutput;
string inputFileName, outputFileName;

void Tokenization(string input, char* argv[])
{
	int r = 0;
	int c = 0;

	for (int i = 0; i < strlen(input.c_str()); i++)
	{
		if (input[i] == '\0')
		    break;
		    
		
		    
		//chatgpt===============================================================================
		if (input[i] == '<')
		{
		    // Input redirection detected
		    redirectInput = true;
		    i++; // Skip the '<' symbol
		    while (i < strlen(input.c_str()) && input[i] == ' ')
		        i++; // Skip spaces after '<'

		    // Read the input filename
		    int filenameStart = i;
		    while (i < strlen(input.c_str()) && input[i] != ' ')
		        i++;
		    inputFileName = input.substr(filenameStart, i - filenameStart);
		}
		if (input[i] == '>')
		{
		    // Output redirection detected
		    redirectOutput = true;
		    i++; // Skip the '>' symbol
		    while (i < strlen(input.c_str()) && input[i] == ' ')
		        i++; // Skip spaces after '>'

		    // Read the output filename
		    int filenameStart = i;
		    while (i < strlen(input.c_str()) && input[i] != ' ')
		        i++;
		    outputFileName = input.substr(filenameStart, i - filenameStart);
		}
		//chatgpt===============================================================================
		
		
		
		if (input[i] == '&')
			i++;
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
	for(int i=0; i<6 && argv[i]!=NULL; i++)
		cout<<"command "<<i+1<<": "<<argv[i]<<endl;
}

bool containsExit(string input) 
{
	size_t found = input.find("exit");
	return (found != string::npos);
}

int main()
{
	redirectInput = false;
	redirectOutput = false;
	char* argv[]={NULL,NULL,NULL,NULL,NULL,NULL};
	//1
	cout << "\033[38;2;255;0;0mworo@shell\033[0m:\033[34m~\033[0m$ ";
	getline(cin, input);
	input += '\0';
	//cout<<input;
	if(containsExit(input))
		return 0;
		
	//2	
	Tokenization(input, argv);
	//PrintCommands(argv);
	
	//3
	int ret = fork( );
	if (ret == 0) 
	{
		//cout<<"			IN CHILD BLOCK\n";
		
		
		
		//chatgpt===============================================================================
		// Input redirection
		if (redirectInput)
		{
		    int inputFile = open(inputFileName.c_str(), O_RDONLY);
		    dup2(inputFile, STDIN_FILENO);
		    close(inputFile);
		}

		// Output redirection
		if (redirectOutput)
		{
		    int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		    dup2(outputFile, STDOUT_FILENO);
		    close(outputFile);
		}
		//chatgpt===============================================================================
		
		
		
		redirectInput = redirectOutput = false;
		
		execvp(argv[0],argv);
		exit(0);
	}
	else
	{
		//cout<<"			IN PARENT BLOCK\n";
		//4
		if (input.find("&") == string::npos)
			wait(NULL);
		else 
			printf("Executing concurrently...\n");
	}    
	main();
}