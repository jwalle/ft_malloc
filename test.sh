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

	title
	tput civis
	read -s tmp
	tput cnorm