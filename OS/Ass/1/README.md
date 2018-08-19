# OS Assignment 1

Zubair Abid

20171076


General Usage:
--------------

(On compilation with gcc os1.c/gcc os2.c respectively)

`./a.out [filename]` for both files. ([filename] must be the same for both)



Question 1:
-----------

Takes a file, makes a case and order reversed copy of it in an Assignment/ subdirectory.

### Syscalls Used:

 - write(): As a replacement for printf, and to write to the file
 - open(): In order to open the files and return a file descriptor
 - mkdir(): To make the directory
 - creat(): To make a file
 - lseek(): To control the pointer to the file for buffer reading backwards
 - read(): To read from the file


Question 2:
-----------

Takes the file copy created in the last question and symlinks to it in its parent directory. It
then checks for the symlink's, file's, directory's existence, verifies that the file created is 
in fact a reversed version of the original input file, and then checks the permissions of all
files and directories generated.

### Syscalls Used:

 - write(): As a replacement for printf
 - lstat(): To verify existence and permissions of all files and directory
 - symlink(): To make a symbolic link
 - open(): In order to open the files and return a file descriptor
 - lseek(): To control the pointer to the file for buffer reading backwards
 - read(): To read from the file
