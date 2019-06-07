
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
int init()
{
  int n;
  printf("WELCOME TO SUSHMA SHELL\n");
  printf("Press 1 to start exploring the shell and 0 to quit\n");
  scanf("%d",&n);
  if(n==0)
  return 0;
  else
  return 1;
}
void sh_init()
{
  char *line;
  char **args;
  int status;
  do {
    printf("sush>>>");
    line=read_line();
    args=split_line(line);
    status=sh_execute(args);
  } while(status);
}

char *read_line(){
  char *line=NULL;
  size_t bufsize=0;
  getline(&line,&bufsize,stdin);
  return line;
}
char **split_line(char *line)
{
  int bufsize=LSH_TOK_BUFSIZE,position=0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  token=strtok(line,LSH_TOK_DELIM);
  while(token!=NULL)
  {
    tokens[position]=token;
    position++;
    token=strtok(NULL,LSH_TOK_DELIM);
  }
  tokens[position]=NULL;
  return tokens;

}
int sh_launch(char **args)
{
  pid_t pid,wpid;
  int status;
  pid=fork();
  if(pid==0)
  {
    //child process
  }
}
int main(int argc, char **argv) {
  int y;
  y=init();
  if(y==0)
  return 0;
  if(y==1)
  {
    printf("THIS SHELL IMPLEMENTS FEATURES LIKE ls,pipes and redirection.Find out more about this by exploring the shell!\n");
    sh_init();
  }
}
