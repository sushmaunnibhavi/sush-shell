
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char *sh_read_line(void);
char **sh_split_line(char *line);
int sh_execute(char **args);
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
    line=(*sh_read_line)();
    args=(**sh_split_line)(line);
    status=sh_execute(args);
  } while(status);
}

char *sh_read_line(void){
  char *line=NULL;
  size_t bufsize=0;
  getline(&line,&bufsize,stdin);
  return line;
}
char **sh_split_line(char *line)
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
//In order to execute commands we need to create a child process
int sh_launch(char **args)
{
  pid_t pid,wpid;
  int status;
  pid=fork();
  if(pid==0)
  {
    //child process
    //use execvp to pass the program name and an array(vector) of string arguments
    if(execvp(args[0],args)==-1)
    {
      perror("sh");
    }
    exit(EXIT_FAILURE);

  }
  else if(pid<0)
  {
    //Error forking
    perror("sh");
  }
  else
  {
    //parent process
    do
    {
      wpid=waitpid(pid,&status,WUNTRACED);

    } while (!WIFEXITED(status)&&!WIFSIGNALED(status));
    
    //wait until the child process either exits normally or is killed by a signal
  }
  return 1;
  //we return 1 to prompt for input again
}
/*
  List of builtin commands
*/
char *builtin_str[]={
  "cd",
  "help",
  "exit"
};

/*
  Function Declarations for builtin shell commands:
 */
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
/*
  List of builtin functions
*/
int (*builtin_func[])(char**)={
  &sh_cd,
  &sh_help,
  &sh_exit
};
int sh_num_builtins()
{
  return sizeof(builtin_str)/sizeof(char*);

}

/*
  Builtin function implementation
*/
int sh_cd(char **args)
{
  if(args[1]==NULL)
  {
    fprintf(stderr,"sh:expected argument to \"cd\"\n");

  }
  else
  {
    if(chdir(args[1])!=0)
    {
      perror("sh");
    }
  }
  return 1;
  
}

int sh_help(char **args)
{
  int i,y;
  printf("Sushma Unnibhavi's shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");
  y=sh_num_builtins();
  for(i=0;i<y;i++)
  {
    printf("%s\n",builtin_str[i]);

  }
  printf("use the man command for information on other programs");
  return 1;
}

int sh_exit(char **args)
{
  return 0;
}

int sh_execute(char **args)
{
  int i,y;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  y=sh_num_builtins();
  for (i = 0; i < y; i++) {
    /*
    Check if the entered command is present in the set of builtin commands
    */
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return sh_launch(args);
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
