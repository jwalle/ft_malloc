#!/bin/tcsh
setenv DYLD_LIBRARY_PATH .
setenv DYLD_INSERT_LIBRARIES libft_malloc.so
setenv DYLD_FORCE_FLAT_NAMESPACE 1 
../lemin2/lem-in < ../lemin2/maps/house.map
#./test2 20
#./test T 3 2 1
