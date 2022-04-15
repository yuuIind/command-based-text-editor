//
// Created by Hakan on 30.12.2021.
//

#ifndef TERMPROJECT_TEXTSTACK_H
#define TERMPROJECT_TEXTSTACK_H

#include <string>
using namespace std;

class textStackNode {
public:
    textStackNode(int operation, int linen1, const char* s, int linen2){// constructor
        command = operation;
        line = linen1;
        text = s;
        line2 = linen2;
        next = NULL;
    }
    int command; //operation: 1: insert; 2: delete; 3: move; 4: replace; 5: next; 6: prev;
    int line; //the line that operation is performed on, if line info is not needed, -1 is assigned
    string text; //the text that is entered, if text info is not  needed, " \n" is assigned
    int line2; //the second line that operation is performed on, if line info is not needed, -1 is assigned
    textStackNode* next;
};


class textStack {
public:
    textStack() {
        top = NULL;
        stacksize = 0;
    }
    ~textStack();

    bool isEmpty() {
        return top == 0;
    }

    int stackLength() {
        return stacksize;
    }

    void pushToStack(int operation, int linen1, const char* s, int linen2);
    void popFromStack();
    void deleteAll();
    int returnCommand(); //returns the last operation's value, if stack empty returns -1 (command values are on line 20)
    int returnLine1(); //returns the line, if stack empty returns -1 (more on line 21)
    int returnLine2(); //returns the line2, if stack empty returns -1 (more on line 23)
    string returnText(); // returns the s, if stack empty returns " \n" (more on line 22)
private:
    textStackNode* top;
    int stacksize;
};
#endif //TERMPROJECT_TEXTSTACK_H
