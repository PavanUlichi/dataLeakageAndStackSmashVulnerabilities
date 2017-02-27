#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
run_wrapper(char *cmd) {
  system(cmd);
}

void
show_logs(char *cmd, char *logfile) {
  char buffer[100];
  int i, j;
  snprintf(buffer, sizeof(buffer), "%s -f /var/log/%s", cmd, logfile);
  for(i=0;i<99;i++){
 	if(buffer[i] == ';'){
		printf("warning! use of semicolon is not allowed\n");
		exit(1);	
	}	
  	if(buffer[i] == '.'){
		if(buffer[i+1] == '.'){		
		printf("warning! use of '..' not allowed\n");
		exit(1);
		}
	}
  }

  run_wrapper(buffer);
}


int
main(int argc, char **argv) {
  printf("Display the log file\n");

  if(argc < 2) {
    printf("Usage: %s <log-file>\n\n", argv[0]);
    exit(1);
  }

  show_logs("/usr/bin/tail", argv[1]);
}
