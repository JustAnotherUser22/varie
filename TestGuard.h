#ifndef HEADER1
#define HEADER1


/*con le variabili di tipo "int" il comportamento è strano: se definisco solo la variabile, anche in entrambi i file, non ci sono problemi
se la definisco in entrambi e assegno valori in un solo file tutto funziona
se la definisco in entrambi e assegno valori in entrambi i file ci sono problemi
(anche con le ward)*/
int varGuard;
//int varGuard = 7;



//senza le "ward" nei due file e senza ridefinire la struct nell'altro file ci sono problemi
//perchè mancano appunto le "ward"
struct foo {
    int member;
};


#endif
