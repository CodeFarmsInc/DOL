$ cd := "set default"
$ CFLAGS := "/NOOPT/DEBUG/WARNINGS=NOINFO"
$ INCLUDE := "/INCLUDE=(SYS_FOREX:[STEP3.DEVELOP.TEAM_PSPK.DEV_WU.WORKAREA.orgc.lib])"
$ LFLAGS := "/TRACEBACK"
$
$ copy [.lib]env0vms.h []environ.h
$ cd [.lib]
$ copy env0vms.h environ.h
$ cc 'CFLAGS util.c, msgs.c, time.c
$ cd [-]
$ cc 'CFLAGS zzprep.c, zzutil.c
$ link 'LFLAGS zzprep.obj, zzutil.obj, [.lib]util.obj,msgs.obj,time.obj
$ cc 'CFLAGS  zzcomb.c
$ link 'LFLAGS zzcomb.obj, zzutil.obj, [.lib]util.obj,msgs.obj,time.obj
$ cc 'CFLAGS zzhelp.c
$ link 'LFLAGS zzhelp.obj,zzutil.obj, [.lib]util.obj,msgs.obj,time.obj
$ cc 'CFLAGS zzsplit.c
$ link 'LFLAGS zzsplit.obj
$ cc 'CFLAGS zzroff.c
$ link 'LFLAGS zzroff.obj
$
$!finished
