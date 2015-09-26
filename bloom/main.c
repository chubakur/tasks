#include <stdio.h>
#include "libbloom/bloom.h"
#include <stdlib.h>
#include <string.h>
#include "btree.h"

#define print_bool(x) if(x == 0) puts("FALSE"); else puts("TRUE");

int main(int argc, char** argv){
  size_t max_string_size = 2048;
  if(argc < 2){
    printf("Using: %s <dictionary>", argv[0]);
    return 1;
  }
  struct bloom bloom;
  bloom_init(&bloom, 1000000, 0.01);
  btree* tree = btree_init();

  FILE* dictionary = fopen(argv[1], "r");
  char* twisted_buffer = (char*) calloc(max_string_size, sizeof(char));
  char symbol = 'a';
  size_t index = 0;
  do{
    symbol = fgetc(dictionary);
    if(index >= max_string_size){
      char* tmp = twisted_buffer;
      max_string_size *= 2;
      twisted_buffer = (char*) realloc(twisted_buffer, max_string_size);
      if(tmp != twisted_buffer)
        free(tmp);
    }
    if(symbol == '\n' || symbol == EOF){
      if(index > 0){
        twisted_buffer[index] = 0;
        bloom_add(&bloom, twisted_buffer, index + 1);
        char* value = (char*) malloc(index + 1);
        memcpy(value, twisted_buffer, index + 1);
        btree_add(tree, value);
        index = 0 ;
      }
    }else{
      twisted_buffer[index++] = symbol;
    }
  }while(symbol != EOF);
  fclose(dictionary);
  index = 0;
  do{
    symbol = fgetc(stdin);
    if(index >= max_string_size){
      char* tmp = twisted_buffer;
      max_string_size *= 2;
      twisted_buffer = (char*) realloc(twisted_buffer, max_string_size);
      if(tmp != twisted_buffer)
        free(tmp);
    }
    if(symbol == '\n' || symbol == EOF){
      if(index > 0){
        twisted_buffer[index] = 0;
        if(!strcmp("exit", twisted_buffer)) break;
        if(bloom_check(&bloom, twisted_buffer, index + 1) && btree_contains(tree, twisted_buffer)){
          puts("YES");
        }else{
          puts("NO");
        }
        index = 0 ;
      }
    }else{
      twisted_buffer[index++] = symbol;
    }
  }while(symbol != EOF);
  free(twisted_buffer);
  btree_free(tree);
  return 0;
}
