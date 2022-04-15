//
// Created by Hakan on 25.12.2021.
//

#ifndef TERMPROJECT_STRINGSLLIST_H
#define TERMPROJECT_STRINGSLLIST_H
#include <string>
using namespace std;

class stringSLLNode {
public:
    stringSLLNode(const char* s) {
        text = s;
        next = 0;
    }
    stringSLLNode(const char* s, stringSLLNode* ptr) { //create some nodes with some specific ->next's.
        text = s;
        next = ptr;
    }
    string text;
    stringSLLNode* next;
};

class stringSLList {
public:
    stringSLList(){
        head = tail = 0;
        listLength = 0;
    }
    ~stringSLList();
    bool isEmpty() { //if list is empty, returns true
        return head == 0;
    }
    int listLen() {
        return listLength;
    }
    void addToHead(const char* s); //adds string s to head
    void addToTail(const char* s); //adds string s to tail
    string deleteFromHead(); //deletes from head and return its text
    string deleteFromTail(); //deletes from tail and return its text
    string deleteNode(int line); //deletes the nth node and return its text
    void insertNode(const char* s, int line); //insert a node to nth place (n = line)
    void moveNode(int n, int m); // moves nth node to mth place
    void replace(const char* s, int line);//replace the line'th node's text with s
    void printLines(int line); //print the all nodes' text till line'th node
    void printLinesFromTo(int lineF, int lineT);
    string returnText(int line);
private:
    stringSLLNode* head;
    stringSLLNode* tail;
    int listLength;
};
#endif //TERMPROJECT_STRINGSLLIST_H
