#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int find_greatest(size_t* array){
  size_t temp = array[0];
  int idx = 0;
  for(int i = 1; i < 26; i++){
    if(array[i] > temp){
      temp = array[i];
      idx = i;
    }
  }
  return idx;
}

int main(int argc, char ** argv)
{
  size_t freq[26] = {0};
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
  while((c = fgetc(f)) != EOF){
    if(isalpha(c)){
      freq[c/32 - 1]++; //A = 65 / 32 = 1, a = 97/32 = 1
    }
  }
  fprintf(stdout, "%d\n", (find_greatest(freq) + 26 - 4) / 26);

  return 0;
}
