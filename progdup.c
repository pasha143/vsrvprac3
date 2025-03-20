#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
//создание переменных для файлового дескриптора и для хранения копии дексриптора stdout 
  int fd, saved_stdout;
//Дублируем файловый дескриптор в нашу переменную
  fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1){
    perror("open");
    exit(1);
}
  saved_stdout = dup(STDOUT_FILENO);

  if (dup2(fd, STDOUT_FILENO) == -1){
    perror("dup2"); 
    close(fd); 
    exit(1);
  }
  printf("Hello\n");
  fflush(stdout); //Сбрасываем буфер stdout на диск
  
//Возвращаем вывод на экран 
  dup2(saved_stdout, STDOUT_FILENO);
  
  close(fd); 
  close(saved_stdout);
  
  return 0;
}
