red="\e[0;31m"
nocolor="\e[0m"

jhalford-corr () {
	PATH_jhalford=~/42-correction-jhalford
	if [[ -z "$1" ]]; then
		green="\e[0;32m"

		echo $green 
		echo "                --- Utilisation ---"
		echo "   placez vous dans le dosser du jour a corriger (cd /path/to/j03)"
		echo "      tapez la commande '"$nocolor"jhalford-corr j03 ex05"$green"'"
		echo "             pour corriger le j03 ex05"
		echo "                     ou alors"
		echo "      tapez la commande '"$nocolor"jhalford-corr j03"$green"'"
		echo "           pour corriger toute la journée"
		echo "                -------------------"
		return
	fi

	if [ $1 = reinstall ]; then
		source $PATH_jhalford/setup.sh
		return
	fi
	source $PATH_jhalford/update-git.sh
	cp $PATH_jhalford/$1.c .
	cp $PATH_jhalford/Makefile .
	echo $red
	echo "                ---- ATTENTION ----"
	echo "         lisez les codes que vous corrigez !"
	echo "cette suite de tests ne remplace pas un être humain !"
	echo "                -------------------"
	echo $nocolor
	if [ -n "$2" ]; then
		gcc -I $PATH_jhalford $1.c -D $2 && ./a.out
	else
		make $1
	fi
	if [ $PWD != $PATH_jhalford ]; then
		rm $1.c Makefile
	fi
	rm a.out
}
