#include <CommandHandler.h>

#define CALLBACK_COUNT 2

struct callback_t callbacks[CALLBACK_COUNT] = {
  {.keyword = "hello", .func = &hello},
  {.keyword = "ping", .func = &pong}
  };

CommandHandler cmdHandler(callbacks, CALLBACK_COUNT);

void hello(void){
  Serial.write("helloworld!");
}

void pong(void){
  Serial.write("pong!");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

}

void loop() {
  if (Serial.available()){
    char c = Serial.read();
    cmdHandler.processChar(c);
  }
}
