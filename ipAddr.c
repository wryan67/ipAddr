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


int main()
{
    FILE *pipe;
    char hostName[32];
    char ipAddress[32];

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

