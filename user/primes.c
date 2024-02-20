#include "kernel/types.h"
#include "user/user.h"
#define READ 0
#define WRITE 1

int prime(int p[2])
{
    int buf;
    int n = read(p[READ],&buf, sizeof(buf));
    if(n == sizeof(buf))
    {
        fprintf(1, "prime %d\n", buf);
        int tem;
        int p1[2];
        pipe(p1);
        while (read(p[READ], &tem, sizeof(tem)) > 0)
        { 
            if (tem % buf != 0)
                write(p1[WRITE], &tem, sizeof(tem));
        }
	close(p1[WRITE]);
        if (fork() == 0)
        {
            prime(p1);
        }
        else
        {
            wait(0);
        }
	close(p1[READ]);
    }
    else if(n ==0){
	    exit(0);
    }
    exit(0);
}
int main(int argc, char *argv[])
{
    if(argc != 1){
	    fprintf(2,"Usage:primes");
    	    exit(1);
    }
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++)
    {
        write(p[WRITE], &i, sizeof(int));
    }
    close(p[WRITE]);
    if (fork() == 0)
    {
        prime(p); 
   }
    else
    {
        wait(0);
    }
    exit(0);
}
