#!/bin/sh

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
#unset DYLD_FORCE_FLAT_NAMESPACE
if [ $1 = "all" ]
then
	/usr/bin/time -l ./test0 2> /tmp/tmp
	cat /tmp/tmp
else
	$@
fi