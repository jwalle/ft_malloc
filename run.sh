#!/bin/sh 
function title_tmp()
{
	for ((i = 1 ; i <= $1 ; i++))
	do
		echo "\033["$4";"$i"H "
	done
	for ((i = $2 ; i <= $3 ; i++))
	do
		echo "\033["$4";"$i"H "
	done
}

function title()
{
	clear
	cols=$(tput cols)
	start=$(((cols / 2) - 15))
	end=$(((cols / 2) + 15))
	echo "\033[31;44m"
	title_tmp $start $end $cols 1
	title_tmp $start $end $cols 2
	title_tmp $start $end $cols 3
	title_tmp $start $end $cols 4
	title_tmp $start $end $cols 5
	title_tmp $start $end $cols 6
	echo "\033[1;"$start"H               _ _            "
	echo "\033[2;"$start"H   /\/\   __ _| | | ___   ___ "
	echo "\033[3;"$start"H  /    \ / _\` | | |/ _ \ / __|"
	echo "\033[4;"$start"H / /\/\ \ (_| | | | (_) | (__ "
	echo "\033[5;"$start"H \/    \/\__,_|_|_|\___/ \___|"
	echo "\033[6;"$start"H                                     © made by moi"
	echo "\033[0m"
	start=$(((cols / 2) - 22))
	echo "\033[1m\033[8;"$start"HAppuyer sur Enter pour faire défiler les test\033[0m"
}
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
if [ $1 = "all" ]
then
	title
	tput civis
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mTest 0:\033[0m"
	/usr/bin/time -l ./test0 2> /tmp/tmp
	unset DYLD_FORCE_FLAT_NAMESPACE
	cat /tmp/tmp
	VAL1=$(cat /tmp/tmp | grep "page reclaims" | cut -d 'p' -f 1 | bc)
	export DYLD_FORCE_FLAT_NAMESPACE=1
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mTest 1:\033[0m"
	/usr/bin/time -l ./test1 2> /tmp/tmp
	unset DYLD_FORCE_FLAT_NAMESPACE
	cat /tmp/tmp
	VAL2=$(cat /tmp/tmp | grep "page reclaims" | cut -d 'p' -f 1 | bc)
	export DYLD_FORCE_FLAT_NAMESPACE=1
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mTest 2:\033[0m"
	/usr/bin/time -l ./test2 2> /tmp/tmp
	unset DYLD_FORCE_FLAT_NAMESPACE
	cat /tmp/tmp
	VAL3=$(cat /tmp/tmp | grep "page reclaims" | cut -d 'p' -f 1 | bc)
	export DYLD_FORCE_FLAT_NAMESPACE=1
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mBILAN Test0, Test1, Test2:\033[0m"
	echo "-> Différence entre le nombre de page reclaims entre Test0 et Test1"
	unset DYLD_FORCE_FLAT_NAMESPACE
	VAL4=$(echo $VAL2 "-" $VAL1 | bc)
	echo "\t" $VAL4
	echo "-> Différence entre le nombre de page reclaims entre Test0 et Test2"
	VAL4=$(echo $VAL3 "-" $VAL1 | bc)
	echo "\t" $VAL4
	export DYLD_FORCE_FLAT_NAMESPACE=1
	read -s tmp
	title
	echo ""
	echo "\033[1;4;44;32mTest 3:\033[0m"
	./test3
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mTest 3bis:\033[0m"
	./test3bis
	read -s tmp
	echo ""
	echo "\033[1;4;44;32mTest 4:\033[0m"
	./test4
	read -s tmp
	unset DYLD_FORCE_FLAT_NAMESPACE
	title
	echo ""
	echo "\033[1;4;44;32mTest 5:\033[0m"
	./test5
	read -s tmp
	tput cnorm
else
	$@
fi
