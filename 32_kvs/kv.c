#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * splitLine(char * line){
  size_t ptr_idx = strchr(line, '=') - line;
  size_t diff_len; // difference in length of line and key
  kvpair_t *ans = malloc(sizeof(*ans));

  ans->key = malloc((ptr_idx + 1) * sizeof(*ans->key));
  strncpy(ans->key, line, ptr_idx);
  ans->key[ptr_idx] = '\0';

  stripNewLine(line);
  diff_len = strlen(line) - ptr_idx;
  ans->value = malloc((diff_len) * sizeof(*ans->value));
  strncpy(ans->value, line + (ptr_idx + 1), diff_len); // includes \0

  return ans;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t *ans;
  FILE *f = fopen(fname, "r");
  char * line = NULL;
  size_t sz = 0;

  if(f == NULL){
    fprintf(stderr, "Cannot open file: %s\n", fname);
    return NULL;
  }
  ans = malloc(sizeof(*ans));
  ans->array = NULL;
  ans->num = 0;
  while(getline(&line, &sz, f) != -1){
    ans->num++;
    ans->array = realloc(ans->array, ans->num * sizeof(*ans->array));
    ans->array[ans->num - 1] = splitLine(line);
  }
  free(line);
  fclose(f);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  //free all the memory allocated by readKV
  for(size_t i=0; i < pairs->num; i++){
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i=0; i < pairs->num ;i++){
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(size_t i = 0; i < pairs->num; i++){
    if(strcmp(pairs->array[i]->key, key) == 0)
      return pairs->array[i]->value;
  }
  return NULL;
}
