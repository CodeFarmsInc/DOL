del res*
rem del *.exe
del *.obj
copy ..\lib\envmsft.h environ.h
cl diff.c ..\lib\mllib.lib
del tmp.*
copy test0m.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp0 res0m
diff res0m out0m64
del afile
del bfile
copy test0n.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp0 res0n
diff res0n out0n64
del tmp.*
del sfile
copy test0r.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp0 res0r
diff res0r out0i
del tmp.*
del afile
del bfile
copy test1.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp1 res1
diff res1 out1
del tmp.*
copy test2.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp2 res2
diff res2 out2
del tmp.*
copy test3a.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp3 res3a
diff res3a out3a
del tmp.*
copy test10c.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp10 res10c
diff res10c out10a
del tmp.*
copy test10d.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp10 res10d
diff res10d out10b
del tmp.*
copy test16c.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp16 res16c
diff res16c out16b
del afile
del bfile
del tmp.*
del ascfile
del binfile
copy test23a.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp < inp23 > res23a
diff res23a out23a
del tmp.*
copy test23b.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp < inp23 > res23b
diff res23b out23a
copy test23c.c tmp.cpp
copy test23x.c tmpx.cpp
..\zzprep test23c.h zzincl.h
cl tmp.cpp tmpx.cpp ..\lib\mllib.lib
tmp < inp23 > res23c
copy test23d.c tmp.cpp
del tmp.exe
cl tmp.cpp tmpx.cpp ..\lib\mllib.lib
tmp >> res23c
copy test23e.c tmp.cpp
del tmp.exe
cl tmp.cpp tmpx.cpp ..\lib\mllib.lib
tmp >> res23c
diff res23c out23c
copy ..\lib\envmsft.h environ.h
..\zzprep test23f.c
copy test23f.c tmp.cpp
del tmp.exe
cl tmp.cpp ..\lib\mllib.lib
tmp > res23f
diff res23f out23f
copy test23h.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
del tmp.exe
cl tmp.cpp ..\lib\mllib.lib
tmp < inp23 > res23h
diff res23h out23h
copy test23j.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
del tmp.exe
cl tmp.cpp ..\lib\mllib.lib
tmp < inp23 > res23j
diff res23j out23i
del tmp.*
copy test24.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp0 res < inp24 > res24
del tmp.*
del afile
del bfile
copy test25b.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp < inp25 > res25b
diff res25b out25
del tmp.*
copy test25c.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp < inp25 > res25c
diff res25c out25
del tmp.*
copy test26a.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res26a
diff res26a out26
del afile
del tmp.*
copy ..\lib\envmsft.h environ.h
type testmp.h >> environ.h
copy test27.h tmp
type test27a.h >> tmp
..\zzprep tmp zzincl_a.h zzmaster zzfunc_a.c
copy test27c.c tmp2.cpp
cl /c tmp2.cpp 
copy test27aa.c tmp1.cpp
cl tmp1.cpp tmp2.obj ..\lib\mllib.lib
tmp1 > res27a
copy test27.h tmp
type test27b.h >> tmp
..\zzprep tmp zzincl_b.h zzmaster zzfunc_b.c
copy test27d.c tmp2.cpp
cl /c tmp2.cpp 
copy test27bb.c tmp1.cpp
cl tmp1.cpp tmp2.obj ..\lib\mllib.lib
tmp1 > res27b
copy test27a.h tmp
type test27b.h >> tmp
type test27.h >> tmp
..\zzprep tmp
copy test27c.c tmp3.cpp
copy test27d.c tmp2.cpp
copy test27.c tmp1.cpp
cl tmp3.cpp tmp2.cpp tmp1.cpp ..\lib\mllib.lib
tmp3 > res27
diff res27 out27
del file
del afile
del bfile
copy ..\lib\envmsft.h environ.h
copy test28.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res28
diff res28 out28
del tmp*.*
del sfile
del myfile
copy test31.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp w < inp31 > res31
tmp r > res31
diff res31 out31
del tmp.*
del ring1.out
del ring2.out
copy test32a.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res32a
diff res32a out32
del tmp.*
copy test32b.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res32b
diff res32b out32
del tmp.*
..\zzprep test35.c
copy test35.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res35
diff res35 out35
del tmp.*
..\zzprep test36b.c
copy test36b.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res36
diff res36 out36
del tmp.*
..\zzprep test38.c
copy test38.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res38
diff res38 out38
del tmp.*
..\zzprep test39a.c
copy test39a.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res39a
diff res39a out39ant
del tmp.*
..\zzprep test39b.c
copy test39b.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res39b
diff res39b out39bnt
del tmp.*
..\zzprep test50.c
copy test50.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res50
diff res50 out50
del tmp.*
..\zzprep test54.c
copy test54.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res54
diff res54 out54
del tmp.*
copy ..\lib\envmsft.h environ.h
..\zzprep test56.c
copy test56.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res56
diff res56 out56
copy ..\lib\envmsft.h environ.h
..\zzprep test57.c
copy test57.c tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp < inp57a > res57
tmp < inp57b > res57
tmp < inp57c > res57
diff res57 out57
copy ..\lib\envmsft.h environ.h
copy test58a.h temp.h
type test58b.h >> temp.h
type test58r.h >> temp.h
..\zzprep temp.h zzincl.h
cl test58m.cpp test58a.cpp test58b.cpp ..\lib\mllib.lib
test58m > res58
diff res58 out58
del tile.odb
copy test60a.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60a
diff res60a out60
del tile.odb
copy test60b.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60b
diff res60b out60
del tile.odb
copy test60c.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60c
diff res60c out60
del tile.odb
copy test60d.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60d
diff res60d out60
copy test61.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res61
diff res61 out61
