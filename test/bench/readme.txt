INSTRUCTION for Windows 7, 32 bits:

From the DOS (CMD) window, run
tt.bat (compiles the code without disk IO)
rr1.bat first run (creates the data)
rr2.bat second run (creates the same data again, and removes 1/4 of books).
This will verify that you have a working code to start with.

Insert persistence into file library.cpp and files tmp\*.h.
Comment out #define HOLLOW library.cpp.
tt.bat (compiles this time with your disk IO)
rr1.bat first run (creates the data, and saves it to disk)
rr2.bat second run.

If everything runs, please zip everything including the tmp subdirectory,
change the name from xxx.zip to xxxzip, and email it to me.
Thank you, Jiri Soukup
============================================================================
DETAILS:

library.cpp 

Sections, where you should read/write to the disk are marked with
// <<<<<<<<<<<<<<<<<<
All data structures are implemented transparently under ZZ_... ZZds;
you won't find any explicit pointers in the application classes.

ds.def

The data organization is defined in this file, which is like a database schema.
This file is the key to understanding this code. 
When expanding the library templates, the library manager also creates
the UML class diagram, but I don't atttach it. At the moment we have a problem 
with the diagram generator, and I don't want to delay sending this to you.

Directory tmp contains already expanded library classes.

rr1.bat and rr2.bat

The syntax is:
library  -c -a -b 1000000 -n 1
-c for create, -o for open existing data, 
-a to include book abstracts
-b xxx for problem with xxx books
-n xxx problem number, will show in the file name.

Directory doc has documentation for the INCODE library in case you are
curious. You don't have to look at it at all when preparing the benchmark.
