#/bin/bash
#for ((x = 0; x < 20; x++)); do
#printf %s -
cols=$(tput cols)
first=$(((cols / 2) + 7))
second=$(((cols / 2) - 7))
printf '%*s\n' "$cols" '' |  tr ' ' -
for ((x = 0; x < 1; x++)); do
	printf '%s%*s%s\n' "|" "$((cols - 1))" "|"
done
for ((x = 0; x < 1; x++)); do
	printf '%s%*s%s%*s%s\n' "|" "$first" " " "MALLOC" "$second" " " "|"
done
for ((x = 0; x < 2; x++)); do
	printf '%s%*s%s\n' "|" "$((cols - 1))" "|"
done
printf '%*s' "$cols" '' |  tr ' ' -
echo