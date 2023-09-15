# Java to ARM Compiler
Designed and built a robust compiler from the ground up, capable of parsing standard Java code into executable ARM assembly file, ensuring type-check and error detection aligned with Java conventions.

Employed customized, high-level data structures, including symbol table, abstract syntax tree, and production rules table to efficiently facilitate the compiler and subsequent compilation into executable binaries, which act exactly as a JVM compiler.

The main tool used is the abstract syntax tree, the lex parser, and plenty of data structures created by myself. The whole project can be seen as two main parts. Part 1 is figuring out how to typecheck all the syntax and semantic errors in the java file. I had to compare and contrast with the official java virtual machine and java grammar rules to make sure my typechecker is acting the same way and detecting the same errors (not less and not excessive).

Part 2 is translating the file into arm assembly language so that the computer can then run my assembly executable to get the same results as running the compiled java file. This part required a lot of background knowledge in arm assembly, handling loops, all sorts of array storing and accessing circumstances, different boolean circuits.

See a more in-depth summary of each part of the code in respective folders.

# How to run the compiler
Running the makefile will generate a corresponding executable (name depends on which part you're currently in). Running the executable with ./executable_name java_file_name.c will then do the corresponding task. In part 1 and part 2, the java file will be typechecked for syntax and semantic errors. In the rest parts, the java file will be parsed and the arm assembly code will be generated. I usually use raspberry pi to run the assembly code, then compare it with the the correct output (output generated using normal way of compiling java file).
