/****************************/
/*       pi address         */
/* This program displays    */
/* the current ip address   */
/* and the pi's hostname    */
/* onto an LCD1602 display  */
/****************************/
/* Written by: Wade Ryan    */
/* Date:       2020-11-24   */
/****************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <lcd101rpi.h>

int fd=0;
int lcdHandle=0;
int lcdAddress=0x23;
 


char *chomp(char *s) {
  int len=strlen(s);

  if (len>0 && s[len-1]=='\n') {
     s[len-1]=0;
  }
  return s;
}

int usage(char **args) {
  fprintf(stderr,"usage: %s [ -a hex_address ]\n", args[0]);
  return 0;
}

int commandLineOptions(int argc, char **args) {
	int c;


	while ((c = getopt(argc, args, "a:h?")) != -1)
		switch (c) {
		case 'a':
      if (strncmp(optarg,"0x",2)==0) {
  			sscanf(&optarg[2], "%x", &lcdAddress);
      } else {
  			sscanf(optarg, "%x", &lcdAddress);
      }
			break;
		case 'h':
			return usage(args);
		case '?':
			if (optopt == 'a')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character \\x%x.\n", optopt);

			return usage(args);

		default:
			abort();
		}


	//	for (index = optind; index < argc; index++)
	//		printf("Non-option argument %s\n", args[index]);
	return 1;
}

 
int main (int argc, char **args)
{
    FILE *pipe;
    char hostName[32];
    char ipAddress[32];

    if (!commandLineOptions(argc, args)) {
      return 1;
    }

    int rs = wiringPiSetup();
    if (rs !=0) {
        fprintf(stderr, "unable to initialize wiringPi: \n");
        return 1;
    }

    lcdHandle = lcdSetup(lcdAddress);
    if( lcdHandle < 0) {
        fprintf(stderr, "lcdInt failed\n");
        return 2;
    }


    pipe=popen("/bin/hostname -s", "r");
    fgets(hostName, sizeof(hostName), pipe);
    pclose(pipe);

    pipe=popen("/bin/hostname -I", "r");
    fgets(ipAddress, sizeof(ipAddress), pipe);
    pclose(pipe);

    chomp(hostName);
    chomp(ipAddress);

    printf("Hostname: %s\n", hostName);
    printf("Host IP: %s\n", ipAddress);

    for (int i=0;i<strlen(ipAddress);++i) {
        if (ipAddress[i]==' ') {
            ipAddress[i]=0;
            break;
        }
    }

    lcdPosition(lcdHandle,0,0);
    lcdPrintf(lcdHandle, "%-16.16s", hostName);

    lcdPosition(lcdHandle,0,1);
    lcdPrintf(lcdHandle, "%-16.16s", ipAddress);

    return 0;
}

