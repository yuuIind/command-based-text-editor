//
// Created by Hakan on 25.12.2021.
//

#ifndef TERMPROJECT_TXTEDITOR_H
#define TERMPROJECT_TXTEDITOR_H

#include "stringSLList.h"
#include "textStack.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class txtEditor {
public:
    void openFile(const char* filename);
    void saveFile(const char* filename);
    void insertText(int line, const char* s);
    void deleteText(int line);
    void move(int n, int m);
    void replace(int line, const char* s);
    void nextPage();
    void prevPage();
    void undo();
    void printpage();
private:
    stringSLList linelist;
    textStack commandHistory;
    int pageNumber;
};

#endif //TERMPROJECT_TXTEDITOR_H
