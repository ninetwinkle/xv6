#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


int find(char *pattern, char *path)
{
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;
    if ((fd = open(path, 0)) < 0)
    {
        //printf(2, "find:cannot open %s\n", path);
        return 0 ;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find:cannot stat %s\n", path);
        close(fd);
        return 0 ;
    }
    switch (st.type)
    {
    case T_DIR:
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++='/';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
	    p[DIRSIZ] = 0;
	    if (stat(buf,&st) < 0)
	    {
		    fprintf(2,"find cannot stat %s\n",buf);
		    continue;
	    }
            if(strcmp(p,".") != 0 && strcmp(p,"..")!=0 && st.type==T_DIR)
	    {
		   find(pattern,buf);
	    }
            if(strcmp(de.name,pattern) == 0)
	    {
		    printf("%s\n",buf);
	    }
        }
        close(fd);
	break;
    } 
	return 0;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(1, "Usage:find");
        exit(0);
    }
    find(argv[2], argv[1]);
    exit(0);
}
