$! VMSCHECK.COM
$!
$! Checks results of the regression tests for Code Farms library.
$!
$!
$ write sys$output "test0m"
$ diff res0m out0mu
$!
$!
$ write sys$output "test0n"
$ diff res0n out0nu
$!
$!
$ write sys$output "test0r"
$ diff res0r out0i
$!
$!
$ write sys$output "test4d"
$ diff res4d out4d
$!
$!
$ write sys$output "test9a"
$ diff res9a out9
$!
$!
$ write sys$output "test10c"
$ diff res10c out10a
$!
$!
$ write sys$output "test10d"
$ diff res10d out10b
$!
$!
$ write sys$output "test16c"
$ diff res16c out16b
$!
$!
$ write sys$output "test18e"
$ diff res18e out18a
$!
$!
$ write sys$output "test23f"
$ diff res23f out23f
$!
$!
$ write sys$output "test25b"
$ diff res25b out25
$!
$!
$ write sys$output "test25c"
$ diff res25c out25
$!
$!
$ write sys$output "test26a"
$ diff res26a out26
$!
$!
$ write sys$output "test27"
$ diff res27 out27
$!
$!
$ write sys$output "test28"
$ diff res28 out28
$!
$!
$ write sys$output "test29c"
$ diff res29c out29a
$!
$!
$ write sys$output "test29d"
$ diff res29d out29b
$!
$!
$ write sys$output "test31"
$ diff res31 out31
$!
$!
$ write sys$output "test32b"
$ diff res32b out32
$!
$!
$ write sys$output "test35"
$ diff res35 out35
$!
$!
$ write sys$output "test36"
$ diff res36 out36
$!
$!
$ write sys$output "test39a"
$ diff res39a out39a
$!
$!
$ write sys$output "test42a"
$ diff res42b out42
$!
$!
$ write sys$output "test43"
$ diff res43 out43
$!
$!
