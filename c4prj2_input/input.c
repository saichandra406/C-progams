#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void stripNewLine(char * line){
  char *ptr = line;
  while(*ptr != '\n'){
    ptr++;
  }
  *ptr = '\0';
}

char * getsub(const char * str, size_t idx){
  char *ans = NULL;
  int n = 0;
  while(str[idx+n] != '\0' && str[idx+n] != ' '){
    n++;
  }
  if(n){
    ans = malloc((n+1) * sizeof(char));
    strncpy(ans, str+idx, n);
    ans[n] = '\0';
  }
  return ans;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  size_t idx = 0;
  int count = 0, tmp;
  deck_t * ans = NULL;
  card_t *p;
  char * sub;
  if(strlen(str) == 0)
    return NULL;
  ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;
  while((sub = getsub(str, idx)) != NULL){
    count++;
    tmp = strlen(sub);
    idx = tmp + 1;
    if(sub[0] == '?'){
      tmp = atoi(sub+1);//index in fc
      p = add_empty_card(ans);
      add_future_card(fc, idx, p);
    }
    else{
      add_card_to(ans, card_from_letters(sub[0], sub[1]));
    }
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){

  char * line = NULL;
  size_t sz = 0;
  deck_t ** ans = NULL;
  while(getline(&line, &sz, f) > 0){
    ans = realloc(ans, (*n_hands + 1) * sizeof(*ans));
    stripNewLine(line);
    ans[*n_hands] = hand_from_string(line , fc);
    *n_hands = *n_hands + 1;
  }
  free(line);
  return ans;
}
