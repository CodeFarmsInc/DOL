del *.obj
run286 cl /c /AL /Lp bind.c sweap.c array.c property.c sortRing.c time.c util.c msgs.c
run286 lib pllib  -+ time -+ property -+ bind -+ sortring -+util -+array -+sweap -+ msgs,,pllib
