#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  size_t len = strlen(inputName);
  char * out = NULL;
  if(len > 0){
    //out string to append ".counts" with null character, so 8
    out = malloc((len + 8) * sizeof(*out));
    if(out != NULL){
      strcpy(out, inputName);
      strcat(out, ".counts");
    }
  }
  //default else returns NULL
  return out;
}
