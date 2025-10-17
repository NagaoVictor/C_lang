# **C language setup the env!**



## Linux (Debian)



\- sudo apt update

\- sudo apt install *clang*



\- clang --version

&nbsp;  (OutPut)---> *clang* version X.Y.Z (tags/...)



\# ------------------------------------------------------------------------



## To test a code, simply create a file with extension C.



In Linux, you can create a text file using the nano \[NameFile].c command.



&nbsp;- nano test.c



Add the following commands inside the file.



\#include <stdio.h>

int main() {

&nbsp;	printf("Clang works on Linux");

&nbsp;	return 0;

}



Now, you run the following command to transform the text file into an executable file



&nbsp;- clang test.c -o test

&nbsp;- ./test



if Clang works on Linux appears, clang is ready to test the code



