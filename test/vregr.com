define sys$input test0a.c
define sys$output zzincl.h
run [-]zzprep
cc test0a,[-.]zzlib/lib
define sys$input inp0
define sys$output res0a
run test0a
/??? there are many "diff" in this file ???>
diff res0a out0a
define sys$input test0b.c
define sys$output zzincl.h
run [-]zzprep
cc test0b,[-.]zzlib/lib
define sys$input inp0
define sys$output res0b
run test0b
diff res0b out0b
define sys$input test0p.c
define sys$output zzincl.h
run [-]zzprep
cc test0p,[-.]zzlib/lib
define sys$input inp0
define sys$output res0p
run test0p
diff res0p out0i
define sys$input test1.c
define sys$output zzincl.h
run [-]zzprep
cc test1,[-.]zzlib/lib
define sys$input inp1
define sys$output res1
run test1
diff res1 out1
define sys$input test2.c
define sys$output zzincl.h
run [-]zzprep
cc test2,[-.]zzlib/lib
define sys$input inp2
define sys$output res2
run test2
diff res2 out2
define sys$input test3a.c
define sys$output zzincl.h
run [-]zzprep
cc test3a,[-.]zzlib/lib
define sys$input inp3
define sys$output res3a
run test3a
diff res3a out3a
define sys$input test3b.c
define sys$output zzincl.h
run [-]zzprep
cc test3b,[-.]zzlib/lib
define sys$input inp3
define sys$output res3b
run test3b
diff res3b out3b
define sys$input test4.c
define sys$output zzincl.h
run [-]zzprep
cc test4,[-.]zzlib/lib
define sys$input inp4
define sys$output res4
run test4
diff res4 out4
define sys$input test5.c
define sys$output zzincl.h
run [-]zzprep
cc test5,[-.]zzlib/lib
define sys$output res5
run test5
<???
cp test7.h temp
cat test7a.c>>temp
cat test7b.c>>temp
cat test7x.c>>temp
.??>
define sys$input temp
define sys$output zzincl.h
run [-]zzprep
cc test7a,test7x,[-.]zzlib/lib
define sys$input inp7
define sys$output res7a
run test7a
cc test7b,test7x,[-.]zzlib/lib
define sys$output res7b
run test7b
diff res7a res7b
define sys$input test8.c
define sys$output zzincl.h
run [-]zzprep
cc test8,[-.]zzlib/lib
define sys$input inp8
define sys$output res8
run test8
diff res8 out8
define sys$input test9.c
define sys$output zzincl.h
run [-]zzprep
cc test9,[-.]zzlib/lib
define sys$input inp9
define sys$output res9
run test9
diff res9 out9
define sys$input test10.c
define sys$output zzincl.h
run [-]zzprep
cc test10,[-.]zzlib/lib
define sys$input inp10
define sys$output res10
run test10
diff res10 out10
define sys$input test11.c
define sys$output zzincl.h
run [-]zzprep
cc test11,[-.]zzlib/lib
define sys$output res11
run test11
diff res11 out11
define sys$input test12.c
define sys$output zzincl.h
run [-]zzprep
cc test12,[-.]zzlib/lib
define sys$input inp12a
define sys$output res12
run test12
define sys$input inp12b
define sys$output res12
run test12
diff res12 out12
define sys$input test14.c
define sys$output zzincl.h
run [-]zzprep
cc test14,[-.]zzlib/lib
define sys$input inp14
define sys$output res14
run test14
diff res14 out14
