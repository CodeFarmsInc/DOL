$ goto START
$START:
$!
$ write sys$output "test0m"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test0m.c
$ cxx test0m.c
$ link test0m.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp0
$ define/user sys$output res0m
$ run test0m
$ diff res0m out0mu
$ delete afile.;*
$ delete bfile.;*
$!
$!
$ write sys$output "test0n"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test0n.c
$ cxx test0n.c
$ link test0n.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp0
$ define/user sys$output res0n
$ run test0n
$ diff res0n out0nu
$ delete sfile.;*
$!
$!
$ write sys$output "test0r"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test0r.c
$ cxx test0r.c
$ link test0r.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp0
$ define/user sys$output res0r
$ run test0r
$ diff res0r out0i
$ delete sfile.;*
$!
$!
$ write sys$output "test4d"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test4d.c
$ cxx test4d.c
$ link test4d.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res4d
$ run test4d
$ diff res4d out4d
$ delete afile.;*
$ delete bfile.;*
$!
$!
$ write sys$output "test9a"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test9a.c
$ cxx test9a.c
$ link test9a.obj, [-.LIB]zzclib.olb/lib
$ test9a := $zz$orgc:[test]test9a.exe
$ test9a inp9 res9a
$ diff res9a out9
$!
$!
$ write sys$output "multi"
$ set def [.pmulti.main]
$ @vprep.com
$ set def [-.jdir]
$ @vvmm.com
$ set def [-.pdir]
$ @vvmm.com
$ set def [-.sdir]
$ @vvmm.com
$ set def [-.main]
$ @vvmm.com
$ main inp res
$ diff res out
$!
$ set def [--]
$!
$!
$ write sys$output "test10c"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test10c.c
$ cxx test10c.c
$ link test10c.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp10
$ define/user sys$output res10c
$ run test10c
$ diff res10c out10a
$!
$!
$ write sys$output "test10d"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test10d.c
$ cxx test10d.c
$ link test10d.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp10
$ define/user sys$output res10d
$ run test10d
$ diff res10d out10b
$!
$!
$ write sys$output "test16c"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test16c.c
$ cxx test16c.c
$ link test16c.obj, [-.LIB]zzclib.olb/lib
$ test16c := $ zz$orgc:[test]test16c.exe
$ test16c inp16 res16c
$ diff res16c out16b
$ delete afile.;*
$ delete bfile.;*
$!
$!
$ write sys$output "test18e"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test18e.h
$ define/user sys$input inp18f
$ run [-]zzsplit
$ cxx test18e.c, test18f.c, test18g.c
$ link test18e.obj,test18f.obj,test18g.obj,[-.lib]zzclib.olb/lib
$ test18e := $ zz$orgc:[test]test18e.exe
$ test18e inp18a res18e
$ diff res18e out18a
$!
$!
$ write sys$output "test23f"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test23f.c
$ cxx test23f.c
$ link test23f.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res23f
$ run test23f
$ diff res23f out23f
$ delete myfile.;*
$!
$!
$ write sys$output "test25b"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test25b.c
$ cxx test25b.c
$ link test25b.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp25
$ define/user sys$output res25b
$ run test25b
$ diff res25b out25
$!
$!
$ write sys$output "test25c"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test25c.c
$ cxx test25c.c
$ link test25c.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp25
$ define/user sys$output res25c
$ run test25c
$ diff res25c out25
$!
$!
$ write sys$output "test26a"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test26a.c
$ cxx test26a.c
$ link test26a.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res26a
$ run test26a
$ diff res26a out26
$ delete afile.;*
$!
$!
$ write sys$output "test27"
$ copy [-.LIB]env3vms.h []environ.h
$ append testmp.h environ.h
$ copy test27.h tmp.
$ append test27a.h tmp.
$ zzprep tmp zzincl_a.h zzmaster zzfunc_a.c
$ cxx test27a.c
$ cxx test27aa.c
$ link test27aa.obj, test27a.obj, [-.lib]zzclib.olb/lib
$ define/user sys$output res27a
$ run test27aa
$ copy test27.h tmp.
$ append test27b.h tmp.
$ zzprep tmp zzincl_b.h zzmaster zzfunc_b.c
$ cxx test27b.c
$ cxx test27bb.c
$ link test27bb.obj, test27b.obj, [-.lib]zzclib.olb/lib
$ define/user sys$output res27b
$ run test27bb
$ copy test27a.h tmp.
$ append test27b.h tmp.
$ append test27.h tmp.
$ zzprep tmp zzincl.h
$ cxx test27.c
$ link test27.obj, test27a.obj, test27b.obj, [-.lib]zzclib.olb/lib
$ define/user sys$output res27
$ run test27
$ diff res27 out27
$ delete file.;*
$ delete afile.;*
$ delete bfile.;*
$!
$!
$ write sys$output "test28"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test28.c
$ cxx test28.c
$ link test28.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res28
$ run test28
$ diff res28 out28
$ delete myfile.;*
$!
$!
$ write sys$output "test29c"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test29c.c
$ cxx test29c.c
$ link test29c.obj, [-.lib]pager.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp29a
$ define/user sys$output res29c
$ run test29c
$ diff res29c out29a
$!
$!
$ write sys$output "test29d"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test29d.c
$ cxx test29d.c
$ link test29d.obj, [-.lib]pager.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp29b
$ define/user sys$output res29d
$ run test29d
$ diff res29d out29b
$ delete file1.;*
$ delete file2.;*
$!
$!
$ write sys$output "test31"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test31.c
$ cxx test31.c
$ link test31.obj, [-.LIB]zzclib.olb/lib
$ test31 := $ zz$orgc:[test]test31.exe
$ define/user sys$input inp31
$ define/user sys$output res31
$ test31 w
$ define/user sys$output res31
$ test31 r
$ diff res31 out31
$!
$!
$ write sys$output "test32b"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test32b.c
$ cxx test32b.c
$ link test32b.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res32b
$ run test32b
$ diff res32b out32
$ delete file1.;*
$ delete file2.;*
$!
$!
$ write sys$output "test35"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test35.c
$ cxx test35.c
$ link test35.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res35
$ run test35
$ diff res35 out35
$!
$!
$ write sys$output "test36"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test36b.c
$ cxx test36b.c
$ link test36b.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res36
$ run test36b
$ diff res36 out36
$!
$!
$ write sys$output "test39a"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test39a.c
$ cxx test39a.c
$ link test39a.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$output res39a
$ run test39a
$ diff res39a out39a
$!
$!
$ write sys$output "test42a"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test42a.c
$ cxx test42a.c
$ link test42a.obj, [-.LIB]zzclib.olb/lib
$ test42a := $ zz$orgc:[test]test42a.exe
$ test42a inp42a res42b
$ test42a inp42b res42b
$ diff res42b out42
$!
$!
$ write sys$output "test43"
$ copy [-.LIB]env3vms.h []environ.h
$ zzprep test43.c
$ cxx test43.c
$ link test43.obj, [-.LIB]zzclib.olb/lib
$ define/user sys$input inp43a
$ define/user sys$output res43
$ run test43
$ define/user sys$input inp43b
$ define/user sys$output res43
$ run test43
$ diff res43 out43
$!
$!
