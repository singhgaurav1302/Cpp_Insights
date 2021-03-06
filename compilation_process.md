# Four Stages of Compilation
1. Preprocessing (-E, .i)
2. Compilation (-S, .s)
3. Assembler (-c, .o)
4. Linker (, .out)

### Preprocessing:
Macros (#defines), include files (#include \<files\>), conditional compilation (#ifdef, #ifdefine) are expanded.

`Output of this stage is a file with extension .i`

`g++ -E sample.cpp`

### Compilation:
In this stage preprocessed file is converted into assembly language corresponding to 
hardware or system on which it will run

`Output of this stage is file with extension .s`

`g++ -S sample.i`

### Assembler:
In this stage assembly level code is converted into machine language. 
The code is converted into 1's and 0's

`Output of this stage is object files with extension .o`

`g++ -c sample.s`

### Linker:
At this stage mutiple .o files can be linked together, all external functions or 
library function symbols are resolved and then executable is produced.

`g++ sample.s -o sample.out`
