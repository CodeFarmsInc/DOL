copy strip.bat strip
del *.c
del *.cc
del *.CPP
del *.obj
del CLEAN
copy env0ca.h temp1
copy env0cla.h temp2
copy env1c.h temp3
copy env1cl.h temp4
copy env3c.h temp5
copy env3cl.h temp6
del env*.*
copy temp1 env0ca.h
copy temp2 env0cla.h
copy temp3 env1c.h
copy temp4 env1cl.h
copy temp5 env3c.h
copy temp6 env3cl.h
del temp*
del *.com
del QMAKEL 
del SCO.*
del *.rsp
del *.lst
del *.k
del *.g
del *.M8
del *.exp
copy strip strip.bat
