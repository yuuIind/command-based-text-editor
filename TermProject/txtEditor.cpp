//
// Created by Hakan on 25.12.2021.
//

#include "txtEditor.h"


void txtEditor::openFile(const char* filename) {
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout << "Couldn't open the file.\nPlease try again." << endl;
        return;
    }
    else {
        cout << "File is opened successfully." << endl;
    }
    string line;
    while (getline(file,line)) {
        linelist.addToTail(line.c_str());
    }
    commandHistory.deleteAll(); // command history is emptied
    pageNumber = 1;
}

void txtEditor::saveFile(const char *filename) {
    ofstream fileFinal(filename);
    if(!fileFinal.is_open()){
        cout << "Couldn't open the file.\nPlease try again." << endl;
        return;
    }
    int listLen = linelist.listLen();
    for(int i = 1; i <= listLen; i++){
        fileFinal<<linelist.returnText(i)<<"\n";
    }
    commandHistory.deleteAll(); // command history is emptied
}

void txtEditor::insertText(int line, const char *s) {
    if (line<1){
        cout<<"Error: Could not insert the text\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    linelist.insertNode(s,line); //text is inserted
    commandHistory.pushToStack(1,line,s,-1);//operation saved in command history
    if(line <= 10){
        pageNumber = 1;
    }
    else {
        pageNumber = ((line-1) / 10) + 1; //i.e for line = 15 => (15-1)/10 + 1 = 1.4  + 1  = 2.4 ==> pageNumber = 2 (lines between 11 and 20)
    }
    linelist.printLinesFromTo((10*(pageNumber - 1) + 1), (10*pageNumber)); //prints the page operation is performed
}

void txtEditor::deleteText(int line) {
    if(line<1){
        cout<<"Error: Could not delete the line\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    string s;
    s = linelist.deleteNode(line); //deleted line's text is saved and line is deleted
    if(s != " \n"){ //if delete operation is successful:
        commandHistory.pushToStack(2, line, s.c_str(), -1);//operation and deleted text saved in command history
    }
    else {//if its not; prints the last page and the operation isnt saved in command history
        line = linelist.listLen();
    }
    if(line <= 10){
        pageNumber = 1;
    }
    else {
        pageNumber = ((line-1) / 10) + 1; //i.e for line = 15 => (15-1)/10 + 1 = 1.4  + 1  = 2.4 ==> pageNumber = 2 (lines between 11 and 20)
    }
    linelist.printLinesFromTo((10*(pageNumber - 1) + 1), (10*pageNumber)); //prints the page operation is performed
}

void txtEditor::move(int n, int m) {
    if((n<1) || (m<1)){//if n or m is smaller than 1
        cout<<"Error: Could not move the line\n";
        cout<<"Def: Inappropriate line number entry\n";
        return;
    }
    if (n > linelist.listLen()) {//if n is an empty line
        cout<<"Error: Could not move the line\n";
        cout<<"Def: An empty line can not be moved\n";
        return;
    }
    linelist.moveNode(n, m); //moves line n to m'th line
    commandHistory.pushToStack(3, n, "", m); //operation saved into command history
    if(m <= 10){
        pageNumber = 1;
    }
    else {
        pageNumber = ((m-1) / 10) + 1; //i.e for line = 15 => (15-1)/10 + 1 = 1.4  + 1  = 2.4 ==> pageNumber = 2 (lines between 11 and 20)
    }
    linelist.printLinesFromTo((10*(pageNumber - 1) + 1), (10*pageNumber)); //prints the page operation is performed
}

void txtEditor::replace(int line, const char *s) {
    string prevText = linelist.returnText(line); //stores the current text
    if (prevText == " \n"){ //if line is empty prints an error message
        cout<<"Error: Could not replace line"<<endl<<"Def: Inappropriate line number entry."<<endl;
        return;
    }
    linelist.replace(s, line); //replace with new text
    commandHistory.pushToStack(4, line, prevText.c_str(), -1); //operation and current text saved in command history
    if(line <= 10){
        pageNumber = 1;
    }
    else {
        pageNumber = ((line-1) / 10) + 1; //i.e for line = 15 => (15-1)/10 + 1 = 1.4  + 1  = 2.4 ==> pageNumber = 2 (lines between 11 and 20)
    }
    linelist.printLinesFromTo((10*(pageNumber - 1) + 1), (10*pageNumber)); //prints the page operation is performed
}

void txtEditor::nextPage() {
    int lastPage = ( (linelist.listLen()) / 10 ) + 1;//E.g listLen = 27 ==> lastPage = (27/10) + 1 = (2) + 1 = 3; Last page = 3
    if(lastPage < (pageNumber + 1)){ //if current page is last page than returns an error message and prints current page
        cout<<"Error: Could not change the page"<<endl<<"Def: Current page is the last page"<<endl;
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
        cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
        return;
    }
    pageNumber += 1; //else prints the next page
    linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
    cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
    commandHistory.pushToStack(5,-1," \n",-1);
}

void txtEditor::prevPage() {
    if(pageNumber == 1){ //can't print a page that doesn't exist
        cout<<"Error: Could not change the page"<<endl<<"Def: Current page is the first page"<<endl;
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
        cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
        return;
    }
    pageNumber -= 1;
    linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
    cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
    commandHistory.pushToStack(6,-1," \n",-1);
}

void txtEditor::undo() {
    if(commandHistory.returnCommand() == -1) { //if stack is empty
        cout<<"Error: Could not undo the changes"<<endl<<"Def: Command history is empty"<<endl;
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
        cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
    }
    else if(commandHistory.returnCommand() == 1) { //if top is insert
        linelist.deleteNode(commandHistory.returnLine1()); //deletes the inserted line
        commandHistory.popFromStack(); // the insert operation on top is popped from commandHistory
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber)); //prints the page
    }
    else if (commandHistory.returnCommand() == 2) {// if top is delete
        int line = commandHistory.returnLine1();
        string s = commandHistory.returnText();
        linelist.insertNode(s.c_str(), line); //inserts the deleted line
        commandHistory.popFromStack(); // the delete operation on top is popped from commandHistory
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber)); //prints the page
    }
    else if (commandHistory.returnCommand() == 3) { //if top is move
        int n = commandHistory.returnLine2(); // the m becomes n
        int m = commandHistory.returnLine1(); // then n becomes m
        linelist.moveNode(n, m); // then move nodes again
        commandHistory.popFromStack(); // the move operation on top is popped from commandHistory
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber)); //prints the page
    }
    else if (commandHistory.returnCommand() == 4) {
        int line = commandHistory.returnLine1();
        string s = commandHistory.returnText();// this returns the text before the replace operation changes the line
        linelist.replace(s.c_str(), line); // replace once again
        commandHistory.popFromStack(); // the replace operation on top is popped from commandHistory
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber)); //prints the page
    }
    else if (commandHistory.returnCommand() == 5) {
        commandHistory.popFromStack(); // the next operation on top is popped from commandHistory
        if(pageNumber == 1){ //can't print a page that doesn't exist
            cout<<"Error: Could not change the page"<<endl<<"Def: Current page is the first page"<<endl;
            linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
            cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
            return;
        }
        pageNumber -= 1;
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
        cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
    }
    else if (commandHistory.returnCommand() == 6) {
        commandHistory.popFromStack(); // the prev operation on top is popped from commandHistory
        int lastPage = ( (linelist.listLen()) / 10 ) + 1;//E.g listLen = 27 ==> lastPage = (27/10) + 1 = (2) + 1 = 3; Last page = 3
        if(lastPage < (pageNumber + 1)){ //if current page is last page than returns an error message and prints current page
            cout<<"Error: Could not change the page"<<endl<<"Def: Current page is the last page"<<endl;
            linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
            cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
            return;
        }
        pageNumber += 1; //else prints the next page
        linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber));
        cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
    }
}

void txtEditor::printpage() {
    linelist.printLinesFromTo((10*(pageNumber-1) + 1),(10*pageNumber)); //prints the current page
    cout<<"\n\n--- PAGE "<<pageNumber<<" ---\n\n";
}