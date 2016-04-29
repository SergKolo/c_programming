/*
 * Author: 	Sergiy Kolodyazhnyy
 * Course:	EET 2350
 * Assignment:  HW # 6 , final project
 * Description:	This is a process listing program for Linux.
 * 		Linux relies on /proc filesystem to create
 *		a folder for each process, and that will
 *		contain several files with information about
 *		the process. Many utilities take advantage of
 *		the proc filesystem, including more sophisticated
 *		process listing utility such as ps
 *		This program attemts to emulate ps -e -o pid,comm
 */


#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>


char src[256], dest[256],name[256],buf[512];
void printInfo(void);
const char *token = "Name:" ;
int total_procs = 0;

int main(int argc,char *argv[])
{
	/* The essential idea here is that we want to iterate
	 * over all of the directories that have a number in
	 * their filename under /proc directory, build up the 
	 * /proc/PID/status path , and then read each of those
         * status files ( which is the job for printInfo function.
	 * Those status files have executable name and much other
	 * information. Here we only print name of the executable.
	 * Iterating over the directory names also has a benefit:
	 * each name is a process ID.
	 */
	strcpy(dest,"/proc/");
        DIR *dp;
	dp = opendir(dest);
	struct dirent *sd;

	while ((sd = readdir(dp)) != NULL) {
		if ( sd->d_type == 4 && isdigit(sd->d_name[0]) ){
		   total_procs++;
		   printf("%s ", sd->d_name);
		   strcpy(src,sd->d_name);
		   strcat(dest,src);
		   strcat(dest,"/status");
		   printInfo();
		   strcpy(dest,"/proc/");
		   printf("\n\n");
		}
	}	
        return 0;
}

void printInfo()
{
	FILE *status = fopen(dest, "r" );
	if ( status != NULL ){
	   while(fgets(buf,sizeof(buf),status)){
		if (strncmp(buf,token,strlen(token)) == 0){
		  sscanf(buf,"%*s %s",name);
		  printf(" %s",name);
		  break;
		}
	   }
	fclose(status);
	}
}

 
