#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
  counts_t *ans = malloc(sizeof(*ans));
  ans->num = 0;
  ans->unknown_count = 0;
  ans->known = NULL;
  return ans;
}

one_count_t *  createOneCount(const char * name){
  one_count_t *ans = malloc(sizeof(*ans));
  int str_sz = strlen(name);

  ans->string = malloc((str_sz + 1) * sizeof(*ans->string));
  strncpy(ans->string, name, str_sz + 1);//inlcude '\0'
  ans->count = 1;

  return ans;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int found = 0; //if name in counts, found = 1
  if(name == NULL){
    c->unknown_count++;
  }
  else{
    for(size_t i = 0; i < c->num; i++){
      if(strcmp(c->known[i]->string, name) == 0){
	c->known[i]->count++;
	found = 1; //found
	break;
      }
    }
    if(!found){
      c->num++;
      c->known = realloc(c->known, c->num * sizeof(*c->known));
      c->known[c->num - 1] = createOneCount(name);
    }
  }

}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i = 0; i < c->num; i++){
    fprintf(outFile, "%s: %lu\n", c->known[i]->string, c->known[i]->count);
  }
  if(c->unknown_count > 0){
    fprintf(outFile, "<unknown> : %lu\n", c->unknown_count);
  }
}

void freeOneCount(one_count_t * p){
  free(p->string);
  free(p);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i = 0; i < c->num; i++){
    freeOneCount(c->known[i]);
  }
  free(c->known);
  free(c);
}
