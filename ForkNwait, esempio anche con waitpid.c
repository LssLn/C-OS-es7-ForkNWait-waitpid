/*
	Scrivere un programma che crei n processi figli. Ogni processo sarà identificato da un valore di i crescente.
	Ogni processo figlio terminerà con codice i+1.
	Il processo padre attenderà la terminazione di tutti i figli, visualizzandone PID e valore di ritorno, e poi termina.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int i;
    pid_t pid;
    int status[256]; //retval 
    int n;

    printf("Inserire n :",&n);
    scanf("%d",&n);
    for(i=0;i<n;i++){
        pid=fork();

        switch(pid){
            case -1:
                perror("fork fail");
                exit(EXIT_FAILURE);
                break;
            case 0:
                //figlio 
                printf("\nSono il figlio num %d, pid %d del padre %d",i,getpid(),getppid());
                exit(i+1);
            default:
                pid=wait(&status[i]);
                break;
        }
    } //finito il for, ora il padre stampa gli stati di terminazione
    printf("\nSono il padre, i figli hanno finito:");
    for(i=0;i<n;i++){
        if(WIFEXITED(status[i])){
            printf("\nStato di terminazione figlio %d : %d",i,WEXITSTATUS(status[i]));
        }else{
            printf("\nfiglio %d finito anormalmente",i);
        }
    }

}

// SE IL PADRE DEVE ASPETTARE 1 FIGLIO QUALUNQUE SI USA WAITPID FUORI DALLO SWITCH

/*
int main(){
	pid_t pid;
	int i,status;

	for(i=0;i<N;i++){
		pid=fork();

		switch(pid){
			case -1: printf("Errore nella fork!\n");
				exit(EXIT_FAILURE);
			case 0: printf("Sono il processo figlio con PID %u - PPID: %u\n",getpid(),getppid());
				exit(EXIT_SUCCESS);
			default:
				break;
		}
	}
	waitpid(pid, &status, 0);
	printf("\nSono il padre. Uno dei due processi è terminato!\n");
	if(WIFEXITED(status)){
		printf("Lo stato di terminazione è: %d\n", WEXITSTATUS(status));
	}
}
*/
