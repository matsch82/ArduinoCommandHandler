#ifndef CommandHandler_h
#define CommandHandler_h

/**
 * Minimal Command handler for serial connection callbacks
 *
 * initilize with a array of callback strucs, each contains a keyword and a 
 * fuctionpointer to the function to call
 *
 * struct callback_t callbacks[2] = {
 *   {.keyword = "hello", .func = &hello_cb}
 * 	 {.keyword = "ping", .func = &pong_cb}
 * };
 * 
 * CommandHandler handler(callbacks, 2)
 * ...
 * void hello_cb() {Serial.print("helloworld");
 * void pong_cb() {Serial.print("pong");}
 * ...
 * char c = Serial.read();
 * hander.processChar(c);
 *
 * it will call the given function if a keyword is detected. Make sure that 
 * INPUTBUFFERSIZE > "max keyword length", you can consume answers in the 
 * callback method, overriding this buffer.
 *
 * Copyright (C) 2015 Matthias Schaff (matthias.schaff@gmail.com)
 *
 * Version 1.0 (20150923)
 *
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **/

#define INPUTBUFFERSIZE 32

struct callback_t {
    char* keyword;
    void (*func)(void);
};

class CommandHandler
{
public:
    CommandHandler(callback_t *callbacks, int n);
    void processChar(char c);
    void clearBuffer(void);
private:
    char _InputBuffer[INPUTBUFFERSIZE+1];
    int _callbackCount;
    callback_t* _callbacks;
};

#endif
