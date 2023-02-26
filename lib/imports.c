#include<stdio.h>
#include<emscripten.h>

EM_JS(void, jsFunction, (int n), {
  console.log("Call from EM_JS: " + n);
});

int main() {

  printf("WASM ready!\n");
  
  emscripten_run_script("console.log('Hello from c!')");

  emscripten_async_run_script("console.log('Hello from c async!')", 2000);

  int jsValue = emscripten_run_script_int("getNum()");

  char * jsValStr = emscripten_run_script_string("getStr()");

  printf("Value from getNum: %d\n", jsValue);
  printf("Value from getStr: %s\n", jsValStr);

  jsFunction(144);

  return 1;
}


