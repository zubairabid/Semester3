# Shell in C

This is an implementation of a basic interactive shell done in C as an assignment for our Operating Systems course.


## Requirements as specified

###Minimum requirements to be met:

1. Display requirement

   `username@systemname:path/to/whereever $ `
2. Builtins. `echo`, `cd`, `pwd`. Don't use execvp. 
3. Make an `ls` functionality. Options to enable: -l, -a, -al/la
4. Option to execute system command, like the ones in /bin/. Implement foreground, background processes. Should have arguments.
5. pinfo. Prints information related to the running shell program process.

   `pinfo pid` should print the process related information about the process with pid.
6. Print correct information about the background process exiting safely.
7. Implement a 'remind me' functionality
8. Add a clock

### Stuff to note

1. Usage of `system` is strictly prohibited.
2. Get eror handling right
3. rollnum_assgn2.tar.gz


## Basic Outline:

An overview of how I think it'll function.

 - ? A configuration file setup which modifies behaaviour of the shell prior to opening it
 - An REPL
  - Display prompt
  - Line input 
  - Command processing
  - Command execution
  - along with error handling
 - ? An exit module closing any open processes ? 