//
// Created by Hakan on 25.12.2021.
//
#include "txtEditor.h"
int main () {
    txtEditor Editor;
    string inputTxt;
    string inputCommand;
    string inputLine;

    cout << "Please enter text below.\n------------\nCommands:\n\nOpen a file: 'open'\nSave changes: 'save'\nInsert a line: 'insert'\nDelete a line: 'delete'\nMove a line: 'move'\nReplace a line: 'replace'\nTo see next page: 'next'\nTo see previous page: 'prev'\nTo undo a change: 'undo'\nTo exit: 'exit'\n------------";
    while (true){
        cout << "\nInput: ";
        getline (cin, inputCommand);
        if (inputCommand == "exit") {
            break;
        }
        if (inputCommand == "open"){
            cout<<"Please enter file name. E.g., fileName.txt\n";
            getline (cin, inputTxt);
            Editor.openFile(inputTxt.c_str());
            Editor.printpage();
        }
        else if (inputCommand == "save"){
            cout<<"Please enter file name. E.g., fileName.txt\n";
            getline (cin, inputTxt);
            Editor.saveFile(inputTxt.c_str());
            Editor.printpage();
        }
        else if (inputCommand == "insert"){
            cout<<"Please enter line number and text. E.g., 3 this Text will be inserted to line 3\n";
            getline (cin, inputLine, ' ');
            getline (cin, inputTxt);
            Editor.insertText(stoi(inputLine),inputTxt.c_str());
        }
        else if (inputCommand == "delete"){
            cout<<"Please enter line number. E.g., 3\n";
            getline (cin, inputLine);
            Editor.deleteText(stoi(inputLine));
        }
        else if (inputCommand == "move"){
            cout<<"Please enter current line number and target line. E.g., 3 5\n";
            getline (cin, inputLine, ' ');
            getline (cin, inputTxt);
            Editor.move(stoi(inputLine),stoi(inputTxt));
        }
        else if (inputCommand == "replace"){
            cout<<"Please enter line number and text. E.g., 3 line 3 will be replaced with this text\n";
            getline (cin, inputLine, ' ');
            getline (cin, inputTxt);
            Editor.replace(stoi(inputLine),inputTxt.c_str());
        }
        else if (inputCommand == "next"){
            Editor.nextPage();
        }
        else if (inputCommand == "prev"){
            Editor.prevPage();
        }
        else if (inputCommand == "undo"){
            Editor.undo();
        }
    }
}
