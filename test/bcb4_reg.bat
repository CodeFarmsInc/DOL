echo off
echo BCB4 ORGC Regression Test
echo.
echo Ignore "file not found" errors due to deleting files that don't exist.
echo All compiling is done in bcb4.bat.  Make compiler adjustments there.
echo.
echo Written by Curtis Krauskopf -- based on a regression test by Jiri
Soukup.
echo.
echo The results of the regression tests are in results.log.
echo The compilation log is in compile.log.  Check it for compile-time
errors.
echo.
del res*
del *.exe
del *.obj
del compile.log
call bcb4 diff.c
del environ.h
del results.log
del sfile


copy ..\lib\env3cl.h ..\lib\environ.h


call bcb4test test0m.c inp0 res0m out0mu
call bcb4test test0n.c inp0 res0n out0nu
call bcb4test test0r.c inp0 res0r out0i
REM call bcb4test test0k.c inp0 outREDIR res0k out0k


call bcb4test test1.c  inp1 res1 out1
call bcb4test test2.c  inp2 res2 out2


call bcb4test test3a.c inp3 res3a out3a
call bcb4test test3b.c inp3 res3b out3b


call bcb4test test4c.c inp4 res4c out4c
del sfile
call bcb4test test4d.c noInput outREDIR res4d out4d
del afile
del bfile


echo test5:
echo Verify manually if test5 throws a runtime error.
echo test5.c: >> results.log
echo test5.c: >> compile.log
copy test5.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
call bcb4 tmp.cpp
tmp > res5
del tmp.*
echo test 5 done.


call bcb4test test8.c inp8 res8 out8


call bcb4test test9a.c inp9 res9a out9


call bcb4test test10a.c inp10 res10a out10a
call bcb4test test10b.c inp10 res10b out10b
call bcb4test test10c.c inp10 res10c out10a
call bcb4test test10d.c inp10 res10d out10b



call bcb4test test14a.c inp14a res14a out14ac nodelete
tmp inp14b res14b
diff res14b out14b >> results.log
del tmp.*
del file1


call bcb4test test14b.c inp14a res14a out14ac nodelete
tmp inp14b res14b
diff res14b out14b >> results.log


call bcb4test test15a.c inp15 res15a out15
call bcb4test test15b.c inp15 res15b out15
call bcb4test test15c.c inp15 res15c out15
del sorttest
call bcb4test test15d.c inp15 res15d out15
call bcb4test test15e.c inp15 res15e out15
del sorttest


call bcb4test test16a.c inp16 res16a out16a
del savefile
call bcb4test test16b.c inp16 res16b out16b
call bcb4test test16c.c inp16 res16c out16b
del afile
del bfile
call bcb4test test17f.c inp17b res17f out17f


copy test18c.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
call bcb4 tmp.cpp 
tmp inp18b res18c
tmp inp18c res18c
diff res18c out18c >> results.log
del tmp.*



call bcb4test test18c.c inp18b res18c out18c nodelete
tmp inp18c res18c
echo test18c.c (#2): >> results.log
echo test18c.c (#2): >> compile.log
diff res18c out18c >> results.log


copy test19a.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
call bcb4 tmp.cpp 
tmp > res19a
del tmp.*


call bcb4test test19b.c noInput outREDIR res19b out19b
del sfile


call bcb4test test20a.c noInput outREDIR res20a out20a
del outzz


copy test20b.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
call bcb4 tmp.cpp 
tmp > res20b
del tmp.*
call bcb4test test20c.c noInput outREDIR res20c out20c
del outzz


call bcb4test test22a.c inREDIR inp22 outREDIR res22a out22ac
call bcb4test test22b.c noInput outREDIR res22b out22b
del ascfile
del binfile


call bcb4test test23a.c inREDIR inp23 outREDIR res23a out23a
call bcb4test test23b.c inREDIR inp23 outREDIR res23b out23a


copy test23c.c tmp.cpp
copy test23x.c tmpx.cpp
..\ZZprep test23c.h zzincl.h
call bcb4 tmp.cpp tmpx.cpp
tmp < inp23 > res23c


copy test23d.c tmp.cpp
call bcb4 tmp.cpp tmpx.cpp
tmp >> res23c
pause


echo test23e.c: >> results.log
echo test23e.c: >> compile.log
copy test23e.c tmp.cpp
call bcb4 tmp.cpp tmpx.cpp
tmp >> res23c
diff res23c out23c >> results.log


call bcb4test test23f.c noInput outREDIR res23f out23f
call bcb4test test23h.c inREDIR inp23 outREDIR res23h out23h


call bcb4test test23j.c inREDIR inp23 outREDIR res23j out23i


echo test24 >> compile.log
copy test24.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
call bcb4 tmp.cpp 
tmp inp0 res < inp24 > res24
del tmp.*
del afile
del bfile


call bcb4test test25b.c inREDIR inp25 outREDIR res25b out25
call bcb4test test25c.c inREDIR inp25 outREDIR res25c out25
call bcb4test test26a.c noInput       outREDIR res26a out26


echo test27: >> results.log
echo test27: >> compile.log


copy ..\lib\env3cl.h ..\lib\environ.h
type testmp.h >> ..\lib\environ.h


copy test27.h tmp
type test27a.h >> tmp
..\zzprep tmp ZZincl_a.h zzmaster zzfunc_a.c
copy test27c.c tmp2.cpp
call bcb4 -c tmp2.cpp
copy test27aa.c tmp1.cpp
call bcb4 tmp1.cpp tmp2.obj
tmp1 > res27a
copy test27.h tmp
type test27b.h >> tmp
..\zzprep tmp ZZincl_b.h zzmaster zzfunc_b.c
copy test27d.c tmp2.cpp
call bcb4 -c tmp2.cpp
copy test27bb.c tmp1.cpp
call bcb4 tmp1.cpp tmp2.obj
tmp1 > res27b
copy test27a.h tmp
type test27b.h >> tmp
type test27.h >> tmp
..\zzprep tmp zzincl.h
copy test27c.c tmp3.cpp
copy test27d.c tmp2.cpp
copy test27.c tmp1.cpp
call bcb4 tmp1.cpp tmp2.cpp tmp3.cpp
tmp1 > res27
diff res27 out27 >> results.log
del tmp.*



copy ..\lib\env3cl.h ..\lib\environ.h
call bcb4test test28.c noInput outREDIR res28 out28


del myfile
del pfile
del file1
del file2


call bcb4test test29c.c inp29a  res29c out29a
call bcb4test test29d.c inp29b res29d out29b


del file1
del file2


call bcb4test test29e.c inp29b res29e out29b


del file1
del file2


call bcb4test test29f.c inp29b res29f out29b


del sfile


call bcb4test test30.c noInput outREDIR res30 out30


del myfile



echo "test31.c:" >> results.log
echo "test31.c:" >> compile.log
copy test31.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
call bcb4 tmp.cpp
tmp w < inp31 > res31
tmp r > res31
diff res31 out31 >> results.log


del ring1.out
del ring2.out


call bcb4test test32a.c noInput outREDIR res32a out32


call bcb4test test32b.c noInput outREDIR res32b out32
call bcb4test test35.c  noInput outREDIR res35  out35
call bcb4test test36b.c noInput outREDIR res36  out36
call bcb4test test36c.c noInput outREDIR res36c out36c
call bcb4test test38.c  noInput outREDIR res38  out38 
call bcb4test test39a.c noInput outREDIR res39a  out39a 
call bcb4test test39b.c noInput outREDIR res39b  out39bl 
call bcb4test test41a.c noInput outREDIR res41a  out41 
call bcb4test test41b.c noInput outREDIR res41b  out41 


..\ZZprep test42b.c
copy test42b.c tmp.cpp
call bcb4 tmp.cpp
tmp inp42a res42b
tmp inp42b res42b
echo res42b: >> results.log
echo res42b: >> compile.log
diff res42b out42 >> results.log
del tmp.*


call bcb4test test48.c noInput outREDIR res48 out48
call bcb4test test49a.c noInput outREDIR res49a out49
call bcb4test test49b.c noInput outREDIR res49b out49
call bcb4test test49b.c noInput outREDIR res49b out49 
call bcb4test test49b.c noInput outREDIR res49b out49 
call bcb4test test50.c noInput outREDIR res50 out50 
call bcb4test test54.c noInput outREDIR res54 out54
call bcb4test test56.c noInput outREDIR res56 out56


echo "Test Results"
type results.log
