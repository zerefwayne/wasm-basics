#include<stdio.h>
#include<string.h>

char * str = "My string variable";

char * getStr() {
  return str;
}

int main() {
  printf("WASM ready!\n");
  
  return 1;
}

