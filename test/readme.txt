Directory orgc/test
-------------------
FOR TABLE OF WHAT INDIVIDUAL TESTS ARE TESTING, LOOK AT tests.txt
-------------------
This directory contains test programs, regression test script files, input
files for these tests, and pre-calculated (correct) results. You do not need
this directory in order to use the library in your application. However,
we strongly recommend that you keep it, because it has at least one, and 
usually several programs showing the use of all data structures and of their
various features.

If you are concern about the size of disk space you use, after you type
'clean' in this directory, all object, executables, and temporary data
files are removed, and the entire directory takes less than 700kB.

test*.c and test*.h contain the source for all the test. Some tests consist of
        several source files, but most tests are just small, one file
        programs.
        Tests which use ZZ_HYPER_... statements are C++ tests.
        Tests which use ZZ_ORG_... statements are essentially C tests, and
        even though some of these tests are included in the regression
        suites, simply disregard their existence. 
        Not all of the test* files are used in the regression tests, some
        of them may be obsolete.
        Tests with the same number (for example test10b, test10c, test10d)
        are variations of a similar test problem.

inp*    are the input files for individual tests.

out*    are the precalculated, correct outputs, with which the reesults (res*)
        of individual tests are compared in the regression tests.

demo.cpp is a small, quick demo of the the main features of the library.
        When using VC++, type 'dem' to compile it, then 'demo' to run it.
        During a life demo, I show how easy is to modify the data structure,
        and how most errors introduced by the audience behind my back will
        be automatically detected by the library.

diff.c  is a simple program which compares two similar files, and detects
        the first line where they differ. It is used in the regression
        tests when the usual 'diff' is not available, for example under DOS.

------------------------------------------------------------------------------
The most recent and complete regression test is in msftregr.bat and msftchk.bat.
You may modify these scripts for your operating system and compiler.
For historical reasons, and as a guidance for how to adapt the regression
test to your environment, some older C++ scripts are still in this directory:

regr.test      check results            platform and compiler
------------------------------------------------------------------------------
msftregr.bat   msftchk.bat              MS Windows, VC++
cregr          ccheck                   UNIX, SUN C++
gregr                                   UNIX, G++
lgregr         lgcheck                  LINUX, G++
dcregr         dccheck                  ULTRIX, DEC C++
iregr                                   UNIX, IBM RS6000
mregr          mcheck                   MAC C++ (PWB only)
wtpregr.bat    wtpchk.bat               PC, Watcom C++
vregr.com      vmscheck.com             VMS VAX (old C version only)
BCB4_REG.BAT                            Borland
------------------------------------------------------------------------------
Example of how to save and retrieve data from disk.
---------------------------------------------------
All examples are set for MS Windows and VC++ compiler. For other platforms
and compilers, please, modify file names and the tt*.bat scripts.

BASIC SIMPLE METHOD (binary mode):
    Files: testa1.cpp, testa2.cpp, testa3.cpp, testa.h
    Compile and run the first program which creates data and saves it to disk: 
        tta1.bat
    Compile and run the second program which reads the data from the disk and
    prints it:
        tta2.bat

USING PORTABLE DATA (ASCII method):
    Files: testb1.cpp, testb2.cpp, testb3.cpp, testb.h
    Compile and run the first program which creates data and saves it to disk: 
        ttb1.bat
    Compile and run the second program which reads the data from the disk and
    prints it:
        ttb2.bat

FAST METHOD COMBINING PERSISTENCE WITH ALLOCATION (memory blasting):
    Files: testc1.cpp, testc2.cpp, testc3.cpp, testc.h
    Compile and run the first program which creates data and saves it to disk: 
        ttc1.bat
    Compile and run the second program which reads the data from the disk and
    prints it:
        ttc2.bat
------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>> IMPORTANT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Tests numbered 23: 
test23a.c test23b.c test23c.c test23d.c test23e.c test23f.c test23h.c test23j.c
are already enough to test the most important parts of the library.
They test pointer based data structures and arrays, including inheritance and
virtual functions, both on small and larger sets of data, saving to memory
in all three modes (ASCII, binary, memory blasting), and also reusing deleted 
object special free lists.
------------------------------------------------------------------------------
Some tests use type ZZint which, based on environ.h and ..\lib\types.h, is
interpreted always as int, except for Windows 7/64 bits where it represents
type (long long). When writing your programs or tests, you do not have to use
this variable, unless you plan to use your program in different environments 
such as Windows XP and Windows 7.
------------------------------------------------------------------------------
test70.c is reserved for Machacek's benchmark.
