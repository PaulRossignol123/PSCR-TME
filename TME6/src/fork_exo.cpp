#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"


int ptVie = 3;


void attaque(pid_t adversaire){
	signal(SIGINT,[](int signal){
		if(signal == SIGINT){
			ptVie--;
			std::cout<< "ptVie"<< ptVie <<std::endl;
		}
		if(ptVie == 0){
			std::cout<< "sortie"<<std::endl;
			exit(1);
		}
	});
	kill(adversaire,SIGINT);
	while(true){
		std::cout<< "fin processus"<<std::endl;
		exit(0);
	}
	randsleep();
}
void defense(){
	signal(SIGINT,SIG_IGN);
	randsleep();

}
void combat(pid_t adversaire){
	while(true){
		defense();
		attaque(adversaire);
	}
}

int main () {
	int cpt =0;
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	for (int i=1, j=N; i<=N && j==N  ; i++ ) {
		if(fork()!=0){
			cpt++;
			break;
		}
		cpt =0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				cpt = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;

			}else{
				cpt++;
			}
		}

	}
	for(int i=0;i<cpt;i++){
				int tps = wait(nullptr);
				std::cout << "tps = " << tps << std::endl;

			}
	return 0;
}
