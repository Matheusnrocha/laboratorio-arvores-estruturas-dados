#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
echo '== Compilacao C11 estrita =='
gcc -std=c11 -Wall -Wextra -pedantic -Werror src/*.c -o laboratorio
echo '== Compilacao de testes =='
gcc -std=c11 -Wall -Wextra -pedantic -Werror -I src testes/teste_estruturas.c src/arvore_binaria.c src/bst.c src/avl.c src/heap.c -o teste_estruturas
echo '== Execucao das verificacoes =='
./teste_estruturas
printf '== Entradas invalidas do menu ==\n'
printf 'abc\n999\n0\n' | ./laboratorio | grep -E 'Entrada invalida|Opcao invalida|Recursos liberados'
