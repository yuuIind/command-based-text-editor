# command-based-text-editor

LAST EDIT: Mostly works. However, it doesn't work as intended in some cases. 


CSE211 Term Project

The task in this project is to write a command-based text editor. This text
editor will print the contents of a file to the screen, page by page. Each page
consist of 10 lines. The contents of the file should be kept in certain data structures,
and certain commands should be supported. These are described in detail below:

Commands:
The following are the valid commands the user can enter.

1- open filename: 
Opens the file whose name is provided in the field `filename` and loads its contents.
The changes, that are done to the content of file, are not written to the file.

2- save filename: 
Writes the contents of the document to the file whose name is provided in the `filename` field.

3- insert n text: 
Inserts a new line to position n.
Number of lines > n : place it between n-1'th and n'th lines.
Number of lines < n : fill the gap with blank lines.

4- delete n: 
Deletes the n'th line.

5- move n m: 
Moves the n'th line to m'th line.

6- replace n text: 
Replaces the text inside line n with the string provided in `text`.

7- next: 
Displays the next page.

8- prev: 
Displays the previous page.

9- undo: 
Reverts the last taken action. No limit




