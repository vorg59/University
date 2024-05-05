#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
using namespace std;

string command = "ls -l | grep txt | sort | uniq | wc -l";
char* argv1[] = { NULL, NULL, NULL, NULL };
char* argv2[] = { NULL, NULL, NULL, NULL };
char* argv3[] = { NULL, NULL, NULL, NULL };
char* argv4[] = { NULL, NULL, NULL, NULL };
char* argv5[] = { NULL, NULL, NULL, NULL };
char** argv_container[] = { argv1, argv2, argv3, argv4, argv5 };
int container_index = 0;

void PrintCommands()
{	
	for (int i = 0; i < container_index; i++)
	{
		cout << "CONTAINER " << i << endl;
		for (int j = 0; j <= 2; j++)
		{
			if(argv_container[i][j]!=NULL)
				cout << "\t" << argv_container[i][j] << endl;
		}
	}
}


void Token(string command)
{
	char debug;
	int row = 0;
	int next_next_index = 0;
	for (int i = 0; i <= command.length(); i++)
	{
		debug = command[i];
		if (command[i] == '|' || command[i] == '\0')
		{
			string temp;
			for (int j = 0 + next_next_index; j < i; j++)
			{
				debug = command[j];
				if (command[j] == ' ')
				{
					argv_container[container_index][row] = strdup(temp.c_str());
					//cout << temp << "-> stored in container: " << container_index << " in row: " << row << endl;
					row++;
					temp = "";
					j++;
				}
				temp += command[j];
				next_next_index = j + 2;
			}
			//argv_container[container_index][row] = _strdup(temp.c_str());
			for (int i = row; i <= 2; i++)
			{
				argv_container[container_index][i] = NULL;
			}
			container_index++;
			row = 0;
		}
	}
}

int returnPipeCount()
{
	int cnt = 0;
	for (int i = 0; i < command.length(); i++)
	{
		if(command[i]=='|')
			cnt++;
	}
	return cnt;
}

int main(int argc, char* argv[]) 
{
    command = argv[1];
    // cout<<"CMD = "<<command<<endl;
    command += ' ';
    Token(command);
    //PrintCommands();
    
    int pipecount = returnPipeCount();
    int fd[2];
    int ret;
    for (int i = 0; i < pipecount; i++) {
        pipe(fd);
        ret = fork();
        if (ret == 0) {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execvp(argv_container[i][0], argv_container[i]);
            exit(1);
        } else {
            wait(NULL);
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
    }

    // Execute the last command outside the loop
    execvp(argv_container[pipecount][0], argv_container[pipecount]);

    return 0;
}
