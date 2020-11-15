#include<stdio.h>
#include<stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void){
  unsigned x[] = {0, 0, 1, 2, 100};
  unsigned y[] = {0, 1, 2, 2, 3};
  unsigned ans[] = {1, 0, 1, 4, 1000000};
  unsigned tmp;
  size_t n = *(&x + 1) - x;
  for (size_t i=0; i < n; i++){
    tmp = power(x[i], y[i]);
    if(tmp != ans[i])
      exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
