# compiler-project
Designing a compiler that can parse standard java code into executable arm assembly language that achieves the exact performance of the java code.

The main tool used is the abstract syntax tree, the lex parser, and plenty of data structures created by myself. The whole project can be seen as two main parts. Part 1 is figuring out how to typecheck all the syntax and semantic errors in the java file. I had to compare and contrast with the official java virtual machine and java grammar rules to make sure my typechecker is acting the same way and detecting the same errors (not less and not excessive).

Part 2 is translating the file into arm assembly language so that the computer can then run my assembly executable to get the same results as running the compiled java file. This part required a lot of background knowledge in arm assembly, handling loops, all sorts of array storing and accessing circumstances, different boolean circuits.

See a more in-depth summary of each part of the code in respective folders.
