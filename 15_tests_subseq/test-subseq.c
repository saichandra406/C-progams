#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int array1[] = {},\
      array2[] = {0, 1, 2, 3, -1},\
      array3[]= {4, 0, 1, 2},\
      array4[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9},\
      array5[] = {0,0};
  size_t answer[] = {0, 4, 3, 4, 1};

  if(maxSeq(array1, 0) != answer[0]){
    return EXIT_FAILURE;
  }
  else if(maxSeq(array2, 5) != answer[1]){
    return EXIT_FAILURE;
  }
  else if(maxSeq(array3, 4) != answer[2]){
    return EXIT_FAILURE;    
  }
  else if(maxSeq(array4, 10) != answer[3]){
    return EXIT_FAILURE;
  }
  else if(maxSeq(array5, 2) != answer[4]){
    return EXIT_FAILURE;
  }  
  return EXIT_SUCCESS;
}
