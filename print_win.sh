#/bin/bash
#for ((x = 0; x < 20; x++)); do
#printf %s -
cols=$(tput cols)
printf '%*s\n' "${COLUMNS:-$cols}" '' |  tr ' ' -
for ((x = 0; x < 4; x++)); do
	printf '%s%*s%s\n' "|" "${COLUMNS:-$((cols - 1))}" "|"
done
printf '%*s\n' "${COLUMNS:-$cols}" '' |  tr ' ' -
echo