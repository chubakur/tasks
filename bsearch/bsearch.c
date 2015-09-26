#include <stdio.h>

size_t bsearch(int* arr, int size, int x, char* found){
  size_t first_idx = 0;
  size_t last_idx = size;
  if(size == 0 || x >= arr[last_idx - 1]){
    *found = 0;
    return 0;
  }
  *found = 1;
  while(first_idx < last_idx){
    size_t middle_idx = first_idx + (last_idx - first_idx) / 2;
    if(x <= arr[middle_idx]){
      last_idx = middle_idx;
    }else{
      first_idx = middle_idx + 1;
    }
  }
  while(arr[first_idx] <= x) ++first_idx;
  return first_idx;
}
