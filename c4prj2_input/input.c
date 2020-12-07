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

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  int len=strlen(str);
  deck_t *ans=malloc(sizeof(*ans));
  ans->cards=NULL;
  ans->n_cards=0;
  for(int i=0;i<len-1;i++){
    if ((str[i] == '\n') || (str[i] == ' ')){
      continue;
    }
    else{
      if(str[i]=='?'){
	i++;
	char num[strlen(str)];
	int n = 0;
	while (!((str[i] == '\n') || (str[i] == ' '))){
	  num[n] = str[i];
	  i++;
	  n++;
	}
	num[n] = '\0';
	add_future_card(fc, atoi(num), add_empty_card(ans));
      }
      else{
	card_t card=card_from_letters(str[i],str[i+1]);
	add_card_to(ans,card);
	i++;
      }
    }}
  if(ans->n_cards<5){
    fprintf(stderr,"Less than 5 cards\n");
    return NULL;
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){

  char * line = NULL;
  size_t sz = 0;
  deck_t ** ans = NULL;
  while(getline(&line, &sz, f) > 0){
    ans = realloc(ans, (*n_hands + 1) * sizeof(*ans));
    ans[*n_hands] = hand_from_string(line , fc);
    *n_hands = *n_hands + 1;
  }
  free(line);
  return ans;
}
