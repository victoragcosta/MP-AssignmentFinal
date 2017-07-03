modulos=( valid_index grafo usuarios avaliacao product product_search transaction transaction_search)
comando=( make clean )
testes=( testes_usuarios testes_avaliacao product_tests search_tests transaction_tests transaction_search_tests )
for ((i=0;i<2;i++)); do
	if [ "$1" == ${comando[i]} ]; then
		for ((j=0;j<8;j++)); do
			cd ${modulos[j]}
			if [ "${comando[i]}" == "make" ]; then
				make
			fi
			if [ "${comando[i]}" == "clean" ]; then
				make clean
			fi
			cd ../
		done
	fi
done
if [ "$1" == "exec" ]; then
	for ((i=0;i<6;i++)); do
		echo -e "////////////////\nExecutando: ${testes[i]}\n////////////////"
		cd ${modulos[$(($i+2))]}
		./${testes[i]}
		cd ../
	done
fi
