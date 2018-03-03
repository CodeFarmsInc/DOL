cd multi/main
vprep
cd -
cd jdir
vmm
cd -
cd pdir
vmm
cd -
cd sdir
vmm
cd -
cd main
vmm
define sys$input inp
define sys$output res
run main
diff res out
cd -
cd -
