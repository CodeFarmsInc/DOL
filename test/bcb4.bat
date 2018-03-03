echo %1 %2 %3 %4 %5 %6 %7 %8 %9: >> compile.log
bcc32 -Vt -Lc:\cb4\lib -Ic:\cb4\include  %1 %2 %3 %4 %5 %6 %7 %8 %9
../lib/zzbcb4d.lib >> compile.log
