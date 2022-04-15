//
// Created by Hakan on 30.12.2021.
//

#include "textStack.h"
#include <string>

using namespace std;

textStack::~textStack() {
    for (textStackNode *p; !isEmpty(); ) {
        p = top->next;
        delete top;
        top = p;
        stacksize -= 1;
    }
}

void textStack::pushToStack(int operation, int linen1, const char* s, int linen2) {
    if(top != 0) { //if stack is not empty
        textStackNode* tmp = top;
        top = new textStackNode(operation, linen1, s, linen2);
        top->next = tmp;
        stacksize += 1;
        return;
    }
    top = new textStackNode(operation, linen1, s, linen2); //if stack is empty
    stacksize += 1;
}

void textStack::popFromStack() {
    if(top != 0) { //if stack is not empty
        textStackNode* tmp = top;
        top = top->next;
        delete tmp;
        stacksize -= 1;
        return;
    }
    //if stack is empty returns without doing anything
}

void textStack::deleteAll() {
    while (top != NULL) {
        textStackNode* tmp = top;
        top = top->next;
        delete tmp;
    }
}

int textStack::returnCommand() {
    if (top != 0) {
        return top->command;
    }
    return -1;
}

int textStack::returnLine1() {
    if (top != 0) {
        return top->line;
    }
    return -1;
}

int textStack::returnLine2() {
    if (top != 0) {
        return top->line2;
    }
    return -1;
}

string textStack::returnText() {
    if (top != 0) {
        return top->text;
    }
    return " \n";
}