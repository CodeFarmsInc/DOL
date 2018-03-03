$ cc msgs.c  sweap.c, property.c, bind.c , sortring.c ,time.c ,array.c ,util.c
$ lib/create zzlib *.obj
