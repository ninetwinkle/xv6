#include "kernel/types.h"
#include "user/user.h"

int
main(int argc ,char *argv[])
{
  if(argc <=1){
	fprintf(2,"slepp: input error\n");
	exit(1);
  }
  else if (argc >2)
	 fprintf(2,"sleep:excessive argument\n");
  int sleeptime = atoi(argv[1]);
  sleep(sleeptime);
  exit(0);

}
