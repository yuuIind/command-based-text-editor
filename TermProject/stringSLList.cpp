//
// Created by Hakan on 25.12.2021.
//

#include "stringSLList.h"
#include <iostream>
#include <string>

using namespace std;

stringSLList::~stringSLList() { //destructor
    for (stringSLLNode *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        listLength -= 1;
        head = p;
    }
}

void stringSLList::addToHead(const char* s) { //add a new node to head
    head = new stringSLLNode(s, head);
    if (tail == 0){ //if list is empty
        tail = head;
    }
    listLength += 1;
}

void stringSLList::addToTail(const char* s) { //add a new node to tail
    if (tail != 0) {      // if list not empty;
        tail->next = new stringSLLNode(s);
        tail = tail->next;
    }
    else {
        head = new stringSLLNode(s);
        tail = head;
    }
    listLength += 1;
}

string stringSLList::deleteFromHead() {//delete the head node
    if(head == 0){//if list is empty
        return " \n";
    }
    string s = head->text;
    stringSLLNode* tmp = head;
    if(head == tail){ //if there is only one node
        head = tail = 0;
    }
    else {
        head = head->next;
    }
    delete tmp;
    listLength -= 1;
    return s;
}

string stringSLList::deleteFromTail() {//delete the tail node
    string s = tail->text;
    if (head == tail) {   // if only one node on the list;
        delete head;
        head = tail = 0;
    }
    else {
        stringSLLNode* tmp;// if more than one node in the list
        for (tmp = head; tmp->next != tail; tmp = tmp->next);// finds the predecessor of tail
        delete tail;
        tail = tmp;      // the predecessor of tail becomes tail;
        tail->next = 0;
    }
    listLength -= 1;
    return s;
}

void stringSLList::insertNode(const char *s, int line) {//insert a node to nth place (n = line)
    if(head !=0) {//if the list is NOT empty
        if(line==1){ //if inserted into head
            addToHead(s);
        }
        else{ // if it is NOT inserted into head
            if(line <= listLength) {
                int lineNumber = 0;
                for(stringSLLNode *tmp = head;tmp != 0; tmp = tmp->next){
                    lineNumber +=1;
                    if(lineNumber == (line-1)){ //if line is smaller than lenght of list
                        tmp->next = new stringSLLNode(s,tmp->next);//insert betwen (n-1)th and nth nodes [n = line]
                        listLength +=1;
                        return; //since insertion completed, function returns
                    }
                }
            }
            else {
                for (int i = listLength; i < (line-1); i++) { //if the line is greater than the lenght of list
                    addToTail("");//fills the gap with blank lines
                }
                addToTail(s); //inserts s to nth node (n = line)
            }
        }
    }
    else { //if the list is empty
        addToTail(s);
    }
}
string stringSLList::deleteNode(int line) {//deletes the nth node and return its text
    if(head !=0) { //if list is NOT empty
        if (line == 1) { //if head is the one deleted
            return deleteFromHead();
        }
        else{// if head is NOT the one deleted
            stringSLLNode *prev, *tmp;
            tmp = head;
            //after this loop:
            //prev = (n-1)th node (n = line)
            // tmp = nth node (n = line)
            for (int i = 0; i < (line-1); i++) {
                prev = tmp;
                if(tmp->next != 0) {
                    tmp = tmp->next;
                }
                else{ //if line is greater than the list's length
                    cout<<"Error: Could not delete the line\n";
                    cout<<"Def: line is empty\n";
                    return " \n";
                }
            }
            string s = tmp->text;
            prev->next = tmp->next; // link (n-1)th node with (n+1)th node
            tmp->next = 0; // Safety First!
            delete tmp; //delete the nth node
            listLength -= 1;
            return s; // returns the nth node's text
        }
    }
    else { //if the list is empty
        cout<<"Error: Could not delete the line\n";
        cout<<"Def: file is empty\n";
    }
    return " \n";
}

void stringSLList::moveNode(int n, int m) { //moves nth node to the mth node
    if(n == m) { //n and m is same then returns without doing anything
        return;
    }
    else if (m <= listLength) { //if both nth and mth nodes exist
            string s = deleteNode(n); //text of nth node is saved and nth node is deleted
            insertNode(s.c_str(),m);//text of nth node is inserted mth line
    }
    else if (m > listLength){//if m is greater than the length of list (n <= length of list)
        for(int i = listLength; i<(m-1); i++) { //it fills the gap with blank line
            addToTail("");
        }
        string s = deleteNode(n);
        addToTail(s.c_str()); //then adds it to the end
    }
}

void stringSLList::replace(const char *s, int line) {//replace the line'th node's text with s
    if(line<1){
        cout<<"Error: Could not replace the line\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    if (line > listLength){ // if the line is blank returns without doing anything
        cout<<"Error: Could not replace the line\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    else {
        stringSLLNode* tmp = head;// if line is smaller than list's length
        for( int i = 1; i<line; i++) {
            tmp = tmp->next;
        }
        tmp->text = s;
    }
}

void stringSLList::printLines(int line) { //print the all nodes' text till line'th node
    if(line<1){ //lines start from 1
        cout<<"Error: Could not print the line(s)\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    stringSLLNode* tmp = head;
    if(line > listLength){ //line is greater than the list's length
        for (int i = 1; i <= listLength; i++) { //first prints all list
            cout<<tmp->text<<endl;
            tmp = tmp->next;
        }
        for(int i = listLength; i < line; i++){ //then prints blank line for the gap
            cout<<"\n";
        }
    }
    else{
        for (int i = 1; i <= line; i++) { //line is !NOT! greater than the list's length
            cout<<tmp->text<<endl;
            tmp = tmp->next;
        }
    }
}

void stringSLList::printLinesFromTo(int lineF, int lineT) { //prints the lines from lineF to lineT (lineF < lineT)
    if ((lineF <1) || (lineT <1)){ //if lines are smaller than 1 it returns
        cout<<"Error: Could not print the lines."<<endl<<"Def: Inappropriate line number entry."<<endl;
        return;
    }
    if(lineF > lineT){
        cout<<"Error: Could not print the lines."<<endl<<"Def: Inappropriate line number entry."<<endl;
        return;
    }
    //stringSLLNode* tmp = head;
    if (lineF>listLength){ //if linef greater than the list of length
        for(int i = lineF; i < lineT; i++){ //then prints blank line for the gap
            cout<<"\n";
        }
    }
    else if(lineT > listLength){ //lineF is greater than the list's length
        stringSLLNode* tmp = head;
        for (int i = 1; i < lineF; i++) {
            tmp = tmp->next;
        }
        for (int i = lineF; i <= listLength; i++) { //first prints all list
            cout<<tmp->text<<endl;
            tmp = tmp->next;
        }
    }
    else{
        stringSLLNode* tmp = head;
        for (int i = lineF; i <= lineT; i++) { //lineF and lineT is !NOT! greater than the list's length
            for (int i = 1; i < lineF; i++) {
                tmp = tmp->next;
            }
            cout<<tmp->text<<endl;
            tmp = tmp->next;
        }
    }
}

string stringSLList::returnText(int line) {
    if(line < 1){
        return " \n";
    }
    if (line > listLength){
        return " \n";
    }
    stringSLLNode* tmp = head;
    for(int i = 1; i < line; i++){
        tmp = tmp->next;
    }
    return tmp->text;
}