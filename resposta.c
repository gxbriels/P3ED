#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadmatriz.h"

int main() {
    // gcc resposta.c tadmatriz.c tadlista.c -o main.bin -Wall

    //Não consegui realizar a última parte para ler do arquivo e processar automaticamente.

    //Aparentemente as funções de carrega e salva estão corretas.
    // As de cálculo também.

    tadmatriz A = carrega("A.txt");
    tadmatriz B = carrega("B.txt");
    tadmatriz C = carrega("C.txt");
    tadmatriz D = carrega("D.txt");

    // Até aqui a leitura foi feita de forma correta.

    tadmatriz tranpostaD = transp(D);

    tadmatriz resultado1 = soma(A,B);
    tadmatriz teste1 = salva(resultado1,"AmaisB.txt");
    
    tadmatriz resultado2 = multi(A,B);
    tadmatriz teste2 = salva(resultado2,"AvezesB.txt");
    
    tadmatriz resultado3 = soma(C,tranpostaD);
    tadmatriz teste3 = salva(resultado3,"CmaistranspD.txt");
    
    tadmatriz resultado4 = subtrai(A,B);
    tadmatriz teste4 = salva(resultado4,"AmenosB.txt");
    
    tadmatriz negativaA = neg(A);
    tadmatriz resultado5 = multi(A,B);
    tadmatriz teste5 = salva(resultado5,"menosAvezesB.txt");

    
    tadmatriz resultado6 = multi(A,tranpostaD);
    tadmatriz teste6 = salva(resultado6,"AvezestranspD.txt");

    tadmatriz negativaB = neg(B);
    tadmatriz resultado7 = multi(B,tranpostaD);
    tadmatriz teste7 = salva(resultado7,"menosBvezestranspD.txt");    
    
    return 0;
}
