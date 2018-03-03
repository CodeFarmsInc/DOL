             -----------------------------------------
             Data Object Library - directory 'orgc/lib'
             -----------------------------------------

SOURCE FILES
------------
This directory, together with orgc/macro, are the source of the library.
Since DOL was originally (1989) written in C, functions in this directory
are plain C functions. However, they are called from, hidden, and protected
under the data structure classes that come from the orgc/macro directory.
Note that file orgc/zzcomb.h concatenates all the *.h definitions for these
classes. Their implementations are inserted by the code generator (zzprep)
into file zzfunc.c, which you then compile and link with your application.
File zzcomb.h is also included in your application through zzincl.h.

There are the following files: 

heading.h       key include file used by the entire library
offset.h	additional, small include files
buffer.h
selfid.h

pager.*  	implementation of the pager organization
virtarr.*  	virtual arrays, can be larger than permitted by the compiler
sweap.*		traversal of all objects following data structure pointers
util.*		allocation and file I/O utilities
bind.*		saving to disk, using the ASCII or binary format
blast.*		saving to disk, using memory blasting
sortring.*      sorting a ring of objects, used also for collections, aggregates
msgs.*		error messages for the entire library
time.*		handling of time stamp (special data organization)
property.*	logic behing the property feature
array.* 	arrays that monitor its size, also hash table, binary heap

When two files are present (e.g. bind.c and bind.cc), the *.cc must be used 
when compiling the library for C++.

ENVIRONMENTAL FILES
-------------------
To the library user, the use of environmental files is totally transparent, and
hidden under the recompilation scripts. In case you are interested, here
is how it works:

environ.h file in this directory is automatically created when you recompile
               the library, and it becomes automatically the default environment
               definition for your application. It is a copy of one of the
               env*.h files stored in this directory.

               You can overwrite this default by installing one of the env*.h
               files in the directory where you compile your application.
               This is useful in special situations, but is not recommended
               for regular users. Please, avoid having file environ.h
               in any of your working directories.

There are numerous env*.h files for various operating systems and compilers. 
Look at orgc/readme.txt for more details. Some of these files are obsolete,
and are kept for historical reasons - just in case.

Originally, there were four files for each environment:

env0*.h  for pure C programs,
env1*.h  for C programs compiled under C++
env2*.h  for simple C++ programs, which do not use inheritance
env3*.h  for full scale C++ applications

Since you are working with C++, the environ.h which is left in this directory
is always a copy of one of the env3*.h files.

COMPILE SCRIPTS
---------------
Compilation scripts compile the files in this directory into *.lib or *.a.
These compilation scripts are not typically used by the user - they are
invoked as a part of the overall compilation scripts. For example:

   lib\msft.bat is invoked by orgc\msft.bat	Microsoft VC++
   lib/jscmake  is invoked by orgc/jsmake 	Sun CC
   lib/jsgmake  is invoked by orgc/jsgmake	Sun g++
   lib/lgmake   is invoked by orgc/lgmake	Linux g++

for details on other (partially obsolete) scripts, see orgc/readme.txt

OTHER FILES
-----------
Files 'clean' and 'clean.bat' remove all object-, library-, and temporary files.

Note that the pager organization is itself implemented with DOL, and therefore
its recompilation includes a call to zzprep. This is a similar situation as
when using a compiler to compile its own code.
