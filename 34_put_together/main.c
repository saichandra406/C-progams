#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *f = fopen(filename, "r");
  char *line = NULL;
  size_t sz = 0, n_char = 0;
  counts_t * ans = NULL;
  char * key = NULL, * value = NULL;
  if(f == NULL){
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return NULL;
  }

  ans = createCounts();
  while((n_char = getline(&line, &sz, f)) != -1){
    stripNewLine(line);
    key = realloc(key, n_char * sizeof(*key));
    strncpy(key, line, n_char); // 1 '\0' included
    value = lookupValue(kvPairs, key);
    //no need to free value as return is shallow copy
    addCount(ans, value);
  }
  free(line);
  free(key);
  fclose(f);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  counts_t * c = NULL;
  char * outName = NULL;
  FILE * f = NULL;
  //count from 2 to argc (call the number you count i)
  for(int i = 2; i < argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
