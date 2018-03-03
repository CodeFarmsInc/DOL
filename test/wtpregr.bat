del res*
del *.exe
del *.obj
del multi\main\res
copy diff.c tmp.cpp
wcl386   tmp.cpp ..\lib\wtclib.lib
copy tmp.exe diff.exe
del environ.h
copy ..\lib\env1wt.h ..\lib\environ.h
copy test0a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0a
diff res0a out0a
del tmp.*
copy test0b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0b
diff res0b out0b
del tmp.*
copy test0c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0c
diff res0c out0a
del tmp.*
copy test0d.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0d
diff res0d out0a
del tmp.*
copy test0e.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0e
diff res0e out0e
del tmp.*
copy test0f.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0f
diff res0f out0a
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test0g.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0g
diff res0g out0g
del tmp.*
copy test0h.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0h
diff res0h out0h
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test0m.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0m
diff res0m out0mu
del tmp.*
copy test0n.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0n
diff res0n out0nu
del tmp.*
copy test0r.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res0r
diff res0r out0i
del tmp.*
copy ..\lib\env1wt.h ..\lib\environ.h
copy test0k.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 > res0k
diff res0k out0k
del tmp.*
copy test1.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp1 res1
diff res1 out1
del tmp.*
copy test2.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp2 res2
diff res2 out2
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test3a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp3 res3a
diff res3a out3a
del tmp.*
copy test3b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp3 res3b
diff res3b out3b
del tmp.*
copy test4c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp4 res4c
diff res4c out4c
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test4d.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res4d
diff res4d out4d
copy ..\lib\env3wt.h ..\lib\environ.h
del tmp.*
copy test5.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res5
copy ..\lib\env1wt.h ..\lib\environ.h
del tmp.*
copy test7.h temp
type test7a.c>>temp
type test7b.c>>temp
type test7x.c>>temp
copy test7a.c tmp1.cpp
copy test7x.c tmp2.cpp
..\ZZprep temp zzincl.h
wcl386   tmp1.cpp tmp2.cpp ..\lib\wtclib.lib
tmp1 inp7 res7a
del tmp1.exe
copy test7b.c tmp1.cpp
wcl386   tmp1.cpp tmp2.cpp ..\lib\wtclib.lib
tmp1 res7b
del tmp1.exe
diff res7a res7b
copy test7.h temp
type test7c.c>>temp
type test7d.c>>temp
type test7x.c>>temp
copy test7c.c tmp1.cpp
copy test7x.c tmp2.cpp
copy test7y.c tmp3.cpp
..\ZZprep temp zzincl.h
wcl386   tmp1.cpp tmp2.cpp tmp3.cpp ..\lib\wtclib.lib
tmp1 inp7 res7c
del tmp1.exe
copy test7d.c tmp1.cpp
wcl386   tmp1.cpp tmp2.cpp tmp3.cpp ..\lib\wtclib.lib
tmp1 res7d
del tmp1.exe
diff res7c res7d
del tmp.*
copy test7.h temp
type test7a.c>>temp
type test7x.c>>temp
copy test7a.c tmp1.cpp
copy test7x.c tmp2.cpp
..\ZZprep temp zzincl.h
wcl386   tmp1.cpp tmp2.cpp ..\lib\wtclib.lib
tmp1 inp7 res7aa
del tmp1.exe
copy test7e.h temp
type test7e.c>>temp
..\ZZprep temp zzincl.h
copy test7e.c tmp1.cpp
wcl386   tmp1.cpp ..\lib\wtclib.lib
tmp1>res7e
del tmp1.exe
diff res7e out7e
copy test7f.h temp
type test7f.c>>temp
..\ZZprep temp zzincl.h
copy test7f.c tmp1.cpp
wcl386   tmp1.cpp ..\lib\wtclib.lib
tmp1>res7f
diff res7f res7aa
del tmp.*
copy test8.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp8 res8
diff res8 out8
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test9a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp9 res9a
diff res9a out9
del tmp.*
copy ..\lib\env1wt.h ..\lib\environ.h
type testmp.h >> ..\lib\environ.h
cd multi\main
..\..\..\zzprep proj.h zzincl.h
cd ..\jdir
copy j1.c tmp1.cpp
copy j2.c tmp2.cpp
wcl386 -c  tmp1.cpp tmp2.cpp ..\..\..\lib\wtclib.lib
del *.lib
wlib jLib /C +tmp1 +tmp2
del *.cpp
del *.obj
cd ..\pdir
copy ..\main\proj.h temp
type p.c>>temp
..\..\..\zzprep temp zzincl.h
copy p.c tmp.cpp
wcl386 -c   tmp.cpp ..\..\..\lib\wtclib.lib
copy tmp.obj p.obj
del tmp.*
cd ..\sdir
copy ..\main\proj.h temp
type sIncl.h>>temp
..\..\..\zzprep temp zzincl.h
copy s1.c tmp1.cpp
copy s2.c tmp2.cpp
copy s3.c tmp3.cpp
wcl386 -c   tmp1.cpp tmp2.cpp tmp3.cpp ..\..\..\lib\wtclib.lib
del *.lib
del *.cpp
wlib sLib /C +tmp1 +tmp2 +tmp3
cd ..\main
copy main.c tmp.cpp
wcl386   tmp.cpp ..\pdir\p.obj ..\..\..\lib\wtclib.lib ..\jdir\jlib.lib ..\sdir\slib.lib
tmp inp res
del tmp.*
..\..\diff res out
cd ..\..
copy test10a.c tmp.cpp
copy ..\lib\env1wt.h ..\lib\environ.h
..\ZZprep tmp.cpp zzincl.h
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp inp10 res10a
diff res10a out10a
del tmp.*
copy test10b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp inp10 res10b
diff res10b out10b
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test10c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp inp10 res10c
diff res10c out10a
del tmp.*
copy test10d.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp10 res10d
diff res10d out10b
del tmp.*
copy ..\lib\env1wt.h ..\lib\environ.h
copy test11a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res11a
diff res11a out11
del tmp.*
copy test11b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res11b
diff res11b out11
del tmp.*
copy test12a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp12a res12a
tmp inp12b res12a
diff res12a out12
del tmp.*
copy test12b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp12a res12b
tmp inp12b res12b
diff res12b out12
del tmp.*
copy test12c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp12a res12c
tmp inp12b res12c
diff res12c out12
del tmp.*
copy test14a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp14a res14a
diff res14a out14ac
tmp inp14b res14b
diff res14b out14b
del tmp.*
copy test14b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp14a res14a
diff res14a out14ac
tmp inp14b res14b
diff res14b out14b
del tmp.*
copy test15a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp15 res15a
diff res15a out15
del tmp.*
copy test15b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp15 res15b
diff res15b out15
del tmp.*
copy test15c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp15 res15c
diff res15c out15
del tmp.*
copy test15d.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp15 res15d
diff res15d out15
del tmp.*
copy test15e.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp15 res15e
diff res15e out15
del tmp.*
copy test16a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp16 res16a
diff res16a out16a
del tmp.*
copy test16b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp16 res16b
diff res16b out16b
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test16c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp16 res16c
diff res16c out16bl
copy ..\lib\env3wt.h ..\lib\environ.h
del tmp.*
copy test17f.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp17b res17f
diff res17f out17f
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test18c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp18b res18c
tmp inp18c res18c
diff res18c out18c
copy ..\lib\env1wt.h ..\lib\environ.h
del tmp.*
copy test19a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res19a
del tmp.*
copy test19b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res19b
diff res19b out19b
del tmp.*
copy test20a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res20a
diff res20a out20a
del tmp.*
copy test20b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res20b
del tmp.*
copy test20c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res20c
diff res20c out20c
del tmp.*
copy ..\lib\env1wt.h ..\lib\environ.h
copy test22a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp22 > res22a
diff res22a out22ac
del tmp.*
copy test22b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res22b
diff res22b out22b
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test23a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp23 > res23a
diff res23a out23a
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test23b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp23 > res23b
diff res23b out23a
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test23c.c tmp.cpp
copy test23x.c tmpx.cpp
..\ZZprep test23c.h zzincl.h
wcl386   tmp.cpp tmpx.cpp ..\lib\wtclib.lib
tmp < inp23 > res23c
copy test23d.c tmp.cpp
wcl386   tmp.cpp tmpx.cpp ..\lib\wtclib.lib
tmp >> res23c
copy test23e.c tmp.cpp
wcl386   tmp.cpp tmpx.cpp ..\lib\wtclib.lib
tmp >> res23c
diff res23c out23c
copy ..\lib\env3wt.h ..\lib\environ.h
copy test23f.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res23f
diff res23f out23f
copy ..\lib\env3wt.h ..\lib\environ.h
copy test23j.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp23 > res23j
diff res23j out23i
del tmp.*
copy ..\lib\env1wt.h ..\lib\environ.h
copy test24.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp inp0 res < inp24 > res24
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test25b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp25 > res25b
diff res25b out25
copy ..\lib\env1wt.h ..\lib\environ.h
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test25c.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp < inp25 > res25c
diff res25c out25
del tmp.*
copy test26a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res26a
diff res26a out26
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
type testmp.h >> ..\lib\environ.h
copy test27.h tmp
type test27a.h >> tmp
..\zzprep tmp ZZincl_a.h zzmaster zzfunc_a.c
copy test27c.c tmp2.cpp
wcl386 -c tmp2.cpp ..\lib\wtclib.lib
copy test27aa.c tmp1.cpp
wcl386   tmp1.cpp tmp2.obj ..\lib\wtclib.lib
tmp1 > res27a
copy test27.h tmp
type test27b.h >> tmp
..\zzprep tmp ZZincl_b.h zzmaster zzfunc_b.c
copy test27d.c tmp2.cpp
wcl386 -c tmp2.cpp ..\lib\wtclib.lib
copy test27bb.c tmp1.cpp
wcl386   tmp1.cpp tmp2.obj ..\lib\wtclib.lib
tmp1 > res27b
copy test27a.h tmp
type test27b.h >> tmp
type test27.h >> tmp
..\zzprep tmp zzincl.h
copy test27c.c tmp3.cpp
copy test27d.c tmp2.cpp
copy test27.c tmp1.cpp
wcl386   tmp1.cpp tmp2.cpp tmp3.cpp ..\lib\wtclib.lib
tmp1 > res27
diff res27 out27
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test28.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res28
diff res28 out28
del tmp*.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test31.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp w < inp31 > res31
tmp r > res31
diff res31 out31
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test32a.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res32a
diff res32a out32
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
copy test32b.c tmp.cpp
..\ZZprep tmp.cpp zzincl.h
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res32b
diff res32b out32
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
..\ZZprep test35.c
copy test35.c tmp.cpp
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res35
diff res35 out35
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
..\ZZprep test36b.c
copy test36b.c tmp.cpp
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res36
diff res36 out36
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
..\ZZprep test38.c
copy test38.c tmp.cpp
wcl386   tmp.cpp ..\lib\wtclib.lib
tmp > res38
diff res38 out38
del tmp.*
..\ZZprep test39a.c
copy test39a.c tmp.cpp
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp > res39a
diff res39a out39awt
del tmp.*
..\ZZprep test39b.c
copy test39b.c tmp.cpp
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp > res39b
diff res39b out39bw
del tmp.*
copy ..\lib\env3wt.h ..\lib\environ.h
..\ZZprep test41a.c
copy test41a.c tmp.cpp
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp > res41a
diff res41a out41
..\ZZprep test41b.c
copy test41b.c tmp.cpp
wcl386  tmp.cpp ..\lib\wtclib.lib
tmp > res41b
diff res41b out41
del myFile
del tmp.*
