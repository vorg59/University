# include<iostream>
# include<unistd.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<cstring>
using namespace std;

int collatz(int n) 
{
    if (n % 2 == 0)
        return n / 2;
    else 
        return 3 * n + 1;
}

int main(int argc, char* argv[])
{
	int startingNumber = stoi(argv[1]);
	while(true) 
	{
		int fs[2]; // pipe for child write parent read
		int fd[2]; // pipe for parent write child read
		int pid,rc,nr,status;
		rc=pipe(fd);
		nr=pipe(fs);
		pid=fork();
		if(pid==0)
		{	//child
			close(fd[1]);
			close(fs[0]);
			
			int a;
			rc=read(fd[0],&a,sizeof(int));
			
			startingNumber = collatz(a);
			write(fs[1],&startingNumber,sizeof(int));
			
			close(fd[0]);
			close(fs[1]);
			exit(0);
		}
		else
		{	//parent
			close(fd[0]);
			close(fs[1]);
			cout<<startingNumber<<"\n";
			
			write(fd[1],&startingNumber,sizeof(int));
			pid = wait(&status);
			
			rc=read(fs[0],&startingNumber,sizeof(int));
			
			close(fd[1]);
			close(fs[0]);
			if(startingNumber == 1)
			{
				cout<<startingNumber<<endl;
				break;
			}
		}
	}
	
	return 0;
}