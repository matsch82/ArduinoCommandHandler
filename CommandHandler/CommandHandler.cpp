#include "CommandHandler.h"
#include <stdio.h>
#include <string.h>

CommandHandler::CommandHandler(callback_t *cb_p, int n)
{
    _callbacks = cb_p;
    _callbackCount = n;
    _InputBuffer[INPUTBUFFERSIZE]='\0';
}

void CommandHandler::processChar(char c)
{
    static int pos;
    _InputBuffer[pos++ % INPUTBUFFERSIZE]=c;
    _InputBuffer[pos % INPUTBUFFERSIZE]='\0';
    int i=0;
    bool match = false;
    for(i=0; i<_callbackCount; i++) {
        char *keyword = _callbacks[i].keyword;
        void (*func)(void) = _callbacks[i].func;
        if(!strncmp(_InputBuffer, keyword, pos)) {
            match|= true;
            if(strlen(keyword) == pos) {
                pos=0;
                func();
                match = false;
                break;
            }
        }
    }
    if(!match) {
        _InputBuffer[0]='\0';
        pos=0;
    }
}

void CommandHandler::clearBuffer(){
  int i=0;
  for(i=0;i<INPUTBUFFERSIZE;i++) _InputBuffer[i]='\0'; 
}

