#include<stdlib.h>

size_t maxSeq(int * array, size_t n){
size_t tmp = 1, len = 1;
  if(n == 0) return 0;
  for(int i=1;i < n; i++){
if(array[i] > array[i-1]){
tmp++;
}
 else if(tmp > len){
len = tmp;
tmp = 1;
}
   }

return len > tmp? len : tmp;
}
