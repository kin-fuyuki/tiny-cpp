# Tiny

A tiny command line interpreter for organizing, you can split huge single line commands into lines and even add comments and variables!

## Features

Multi-command: You can make multiple commands in same `.tmk` file by having a line that starts with `\n` 

Comments: You can use comments in the file to your peers or future you remember what you done, also useful to separate sections of a command

Variables: If a line starts with `%` it will get all the name of it until hit the second `%` and to set variables the line has to start with `set`

Ignore space: Add `\` at the start of the line so it will not add an space before it.

(all written in this line after the `\n` and `%var%` will be ignored and be seen as comments)

## example

```
;set variables
set flags=-Os
;compiler
g++
%flags%

;files
main.cpp

;includes
-lstdc++

-I/usr/
;to not add space between /usr/ and include, you add \ so it will be "/usr/include" and not "/usr/ include"
\include

;output
-o tiny.exe

;end command
\n
;run tiny
tiny.exe
```

# WARNING, THIS PROGRAM HAS STRICT SYNTAX
## The line MUST to have `;`,`set` and `%` as first character to be detected as comment, setter and variable, so you can have it in the command (without being interpreted by Tiny) by adding a space before.


# Roadmap

- Add variables when loading a Tiny script

- Create functions

- Stuff people ask for
 
# Compatibility

This is supposed to run anywhere, if it dont work in a platform please warn me (maybe exotic systems with uncommon headers like master system or whatever might not work out of the box... idk.. if it even has a CLI lol)
