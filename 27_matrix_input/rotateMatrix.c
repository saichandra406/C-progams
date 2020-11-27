#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void rotate(char matrix[10][10]){
  char ans[10][10] = {0};
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++)
      ans[i][j] = matrix[9-j][i];
  }
  for(int i=0; i<10; i++)
    for(int j=0; j<10; j++)
      matrix[i][j] = ans[i][j];
}

int main(int argc, char ** argv)
{
  char matrix[10][10];
  int c;
  
  if(argc != 2){
    fprintf(stderr, "No of arguments: %d. Required: 2\n", argc);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if((c = fgetc(f)) != EOF){
	if(isprint(c))
	  matrix[i][j] = (char) c;
	else
	  return EXIT_FAILURE;
      }
    }
    if(fgetc(f) != '\n')
      return EXIT_FAILURE;
  }
  if(fgetc(f) != EOF)
    return EXIT_FAILURE;

  rotate(matrix);

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++)
      printf("%c",matrix[i][j]);
    printf("\n");
  }
      
  return EXIT_SUCCESS;
}
