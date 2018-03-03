REM This is a helper batch file for BCB4_REG.
REM This batch file compiles and compares each test case
REM
REM Syntax:
REM   TestSourceFile.c   [ InputFile or "inREDIR" InputFile or noInput ] [
OutputFile or "outREDIR" OutputFile ] ComparisonFile {nodelete}
REM 
REM Allowed permutations:
REM   TestSourceFile.c          InputFile           OutputFile
ComparisonFile
REM   TestSourceFile.c  inREDIR InputFile           OutputFile
ComparisonFile
REM   TestSourceFile.c          InputFile  outREDIR OutputFile
ComparisonFile
REM   TestSourceFile.c  inREDIR InputFile  outREDIR OutputFile
ComparisonFile
REM   TestSourceFile.c  noInput                     OutputFile
ComparisonFile
REM   TestSourceFile.c  noInput            outREDIR OutputFile
ComparisonFile
REM
REM   Any of the above lines can optionally have a "nodelete" parameter
follow the ComparisonFile
REM
REM
REM Where
REM  TestSourceFile.c is the pre-ZZprep'ed file to be tested
REM  inREDIR is the literal "inREDIR" on the command line
REM  noINPUT is the literal "noINPUT" on the command line
REM  InputFile is the input filename
REM  outREDIR is the literal "outREDIR" on the command line
REM  OutputFile is the output filename
REM  ComparisonFile is the file that contains exactly what OutputFile should
contain
REM  nodelete is the literal "nodelete" on the command line
REM
REM Written by Curtis Krauskopf -- based on a regression test by Jiri
Soukup.


echo %1: >> results.log
echo %1: >> compile.log
copy %1 tmp.cpp
..\ZZprep tmp.cpp zzincl.h
call bcb4 tmp.cpp
if X%2==XinREDIR goto inRedir
if X%2==XnoInput goto noInput
tmp %2 %3
diff %3 %4 >> results.log
if X%5==Xnodelete goto nodeletefinish
goto alldone


:inRedir
REM file.c inREDIR inputfile [ OutputFile or "outREDIR" OutputFile ]
ComparisonFile
if X%4==XoutREDIR goto outREDIR
REM file.c inREDIR inputfile OutputFile ComparisonFile
tmp < %3 %4
diff %4 %5 >> results.log
if X%6==Xnodelete goto nodeletefinish
goto alldone


:outREDIR
REM file.c inREDIR inputfile outREDIR OutputFile ComparisonFile
tmp < %3 > %5
diff %5 %6 >> results.log
if X%7==Xnodelete goto nodeletefinish
goto alldone


:noInput
REM file.c noInput [ OutputFile or "outREDIR" OutputFile ] ComparisonFile
if X%3==XoutREDIR goto out2
REM file.c noInput OutputFile ComparisonFile
tmp %3
diff %3 %4 >> results.log
if X%5==Xnodelete goto nodeletefinish
goto alldone


:out2
REM file.c noInput outREDIR OutputFile ComparisonFile
tmp > %4
diff %4 %5 >> results.log
if X%6==Xnodelete goto nodeletefinish
goto alldone


:alldone
del tmp.*
:nodeletefinish
