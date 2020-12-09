#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  FILE *f;

  if(!(argc == 2 || argc == 3)){
    fprintf(stderr, "Does not have 1 or 2 arguments\n");
    return EXIT_FAILURE;
  }
  
  f = fopen(argv[1], "r");
  if(f == NULL){
    fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  fclose(f);
  return EXIT_SUCCESS;
}
