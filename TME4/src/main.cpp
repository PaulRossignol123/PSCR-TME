#include "Banque.h"
#include <random>
using namespace std;
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::second
const int NB_THREAD = 10;

#include<unistd.h>
int transferWork(pr::Banque &b){
		for(int x =0;x<1000;x++){


		size_t i = rand() % 100 + 1;
		size_t j  = rand() % 100 + 1;
		int m = rand() % 100 + 1;
		b.transfert(i, j, m);

		//int time_sleep = rand() % 20;
		//sleep(time_sleep);
		return 0;
		}
}

int main () {

	pr::Banque b = pr::Banque(100,1000);
	vector<thread> threads;
	threads.reserve(NB_THREAD);
	// TODO : creer des threads qui font ce qui est demandé

	for(int cpt =0; cpt < NB_THREAD;cpt++){
		threads.emplace_back(transferWork,ref(b));

	}

	for (auto & t : threads) {
		t.join();
	}
	int x=0;
	for(int i =0;i<100;i++){
		x += b.getComptes()[i].getSolde();
	}
	cout << x << endl;
	::srand(::time(nullptr));
	return 0;
}
