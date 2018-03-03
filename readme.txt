Code Farms Inc.

     --------------------------------------------------------------
     Data Object Library (known also as orgC++) Ver.8.5 (Nov.21, 2011)
     --------------------------------------------------------------
     The first version fully operational with Windows 7, including 64 bits

DOCUMENTATION
-------------

Please, download the free documentation from www.codefarms.com


INSTALLATION AND REGRESSION TESTS
---------------------------------

STEP 1: Extract the the source.

	You typically recieve the source as a single file, ver57.zip.
        Under UNIX, use:       unzip -a -L ver57.zip
        Under DOS window, PD:  pkunzip -d ver57.zip
        MS Windows:            click on WinZip, select ver57.zip
             
        In either case, you get directory tree 'orgc' with all the source
        and the regression tests in it.
        Documentation in the html format is not included, you have to
        download it separately, e.g. as a free download from www.codefarms.com

STEP 2: Compiling the code generator (zzprep) and the library. 

        We used to support a multitude of operating systems and compilers.
        As C++ reached maturity, the quirks of individual compilers disappeared,
        and we actively support only the four main compilers:

        system    compile-script environment_file regression-test library
        ---------------------------------------------------------------
        MS VC++   orgc\msft.bat  lib\envmsft.h   test\mregr.bat    lib\mllib.lib
        Linux/g++ orgc/lgmake     lib/env3g.h    test/lgregr       lib/zzglib.a
        Sun/CC    orgc/jscmake    lib/env3s.h    test/cregr        lib/zzclib.a
        Sun/g++   orgc/jsgmake    lib/env3g.h    test/gregr        lib/zzglib.a
        Win7/64   orgc\msft64.bat lib\msft64.bat test\vs64regr.bat lib\mllib.lib
        Win XP    orgc\msft.bat   lib\msft.bat   test\vsregr.bat   lib\mllib.lib
        ---------------------------------------------------------------

        For example, in order to recompile and set the environment for VC++,
        type this in DOS window:
            cd orgc
            msft.bat   ... recompiles everything in about 30 sec

        For more details how to compile for Microsoft VC++, see msft.txt.

        IMPORTANT: If you get compile errors, do not attempt to "debug"
          the library. The library is quite complex, and solid. The problem
          is likely caused by an incorrect setup of the environment.
          Any fixes will only aggravate the problem. 
          Contact: support@codefarms.com

        If you work with a different compiler, adjust one of the main four
        scripts, or contact us for assistence. The original scripts
        for various compilers are still included, but may be out of date
        - see OTHER COMPILERS below.

STEP 3: Environment file

        The compilation script sets automatically file lib/environ.h which
        defines then a default for all your programs using this library.
        Earlies versions of DOL required users to set this file. This
        is not required any more, its setting is transparent to the user.
      
STEP 4: Regression test

        The library comes with a full regression test, which tests all 
        the features and functions of the library against correct results.
        The test consists of about 60 independent programs, which can be
        also used as working examples of how to use the library.
        For example, if you are looking for examples of how to use hash
        tables, type   grep HYPER_HASH test*.c    in the orgc/test directory.

        Note that the C version of the library is not supported anymore, even
        though some C programs (using ZZ_ORG_... instead of ZZ_HASH_...)
        are still included in the regression test, and are prefectly working.

        If you want to run the regression test (optional), invoke the 
        appropriate script, for example for VC++ do this:
             cd test
             mregr

        It takes about 5 minutes to run all 60 programs, and you should not
        get any error messages or differences between the res* files (results
        of individual tests) and the out* files(correct, precalculated results).

   
STEP 5: Using the library

        The use of the library is similar for different computers and compilers.
        If your program is all in one file, myProgr.cpp, including the class
        definitions, it is quite simple (VC++ compilation):

        c:\orgc\zzprep myProgr.cpp
        cl myProgr.cpp c:\orgc\lib\mllib.lib

        If your program consists of multiple files, for example a.h, a.cpp,
        b.h, b.cpp, c.h, and c.cpp, you do this:
    
        copy a.h temp.h	
        type b.h >> temp.h
        type c.h >> temp.h
        c:\orgc\zzprep temp.h				[call code generator]
        cl a.cpp b.cpp c.cpp c:\orgc\lib\mllib.lib	[compile, link to DOL]
   
        COMMENTS:
        a. File temp.h is the concatenation of all your header files, and must
           include all the ZZ_HYPER_ statements.
        b. The call to zzprep must use either the full path (as above) or
           the relative path, such as ..\..\orgc\zzprep
        c. One of your cpp files must start with #define ZZmain
        d. The call to zzprep creates two files with default names
           zzincl.h and zzfunc.c.
        e. All your files must have    #define "zzincl.h".
        f. File zzfunc.c must be either included at the end of one of your cpp
           files, or it can be compiled separately by creating a three-line
           cpp file:
             #include "zzincl.h"
             #include "temp.h"
             #include "zzfunc.c"



OTHER COMPILERS
---------------
The original scripts for various compilers are still included, but may be
obsolete. They should be used only as a general guidance for adjusting
the main four scripts. The lib-compile scripts can also tell you which
environment file to use.

Note that in these old versions, there were two separate compile scripts:
One to compile the orgc directory, and one to compile the lib directory.


    system/compiler     orgc-compile   lib-compile   test-regression
    ----------------------------------------------------------------
(1) PC/Borland C++      make.bat	b4pmakel.bat	bcb4_reg.bat
    Sil.Graphics/IRIX   jssgmake	jssgmake	cregr
    PC/Zortech C++      zmake.bat	z3pmakel.bat	z3pregrl.bat
    Macintosh           jmmake		jmcmake		mregr
    DEC ULTRIX C++      jdmake		jdcmake		dcregr
    Watcom C++          wtmake.bat	wtcmake.bat	wtpregr.bat
    HP9000 C++				jshmake		hregr
    VMS VAX C++(old)			makevms.com	vregr.com

    IBM RS6000: like Sun, but add #define IBM to files lib/env*s.h
    OS2:        use the DOS script and the apropriate compiler
  
    If you are modifying any of these files, look at what environmental file
    (env*.h) and library name it is using.


(1) supplied in Feb.2002 by a user - not maintained/guaranteed by Code Farms


MULTI-THREADING
---------------
When running under WinNT and Visual C++ using multiple threads,
instead of compiling the lib directory with msft.bat, use mthread.bat.
Also, your program must be compiled with the /MT option.
For a description of a test on how to run multi-threading under WinNT,
see file threads.nt

SPECIAL VERSIONS OF DOL
-----------------------
Two special versions of the library are available through special order:
(A) IRIX (SiliconGraphics) 64bit version.
(B) Version where user can modify the ZZ-prefix of all library variables.
    This permits to operate multiple versions of DOL under one system
    without the limitation that only one subsystem can save data to disk.



FILES IN THIS DIRECTORY:
------------------------
  zzintern.h - structures and general defines for this directory
  zzprep.c - preprocessor/code generator
  zzutil.c - utility functions
  zzcomb.c - program that generates file of combined macros (zzcomb.h)
  zzhelp.c - program for interactive help (discarded)
  zzroff.c - simplified version of nroff for DOS or MAC (discarded)
The code generator was originally written in C, and is applicable even
when using the C++ version of the library.


ADDITIONAL INFORMATION:
-----------------------
User Guide, available free from www.codefarms.com
File 'upd.txt' has comments on recent version updates.

U++
----
In order to use this library with U++, compile it first with VC++
by typing 'msft' in this directory.
Then
   cd lib
   upp
will produce *.o files to which you have to link when building an U++
application.
