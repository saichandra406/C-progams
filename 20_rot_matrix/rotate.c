#include <stdio.h>

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
