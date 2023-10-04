#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.h"

template <typename Iterator>
size_t count(Iterator begin,Iterator end){
	size_t count = 0;
	while(begin != end){
		count++;
		++begin;
	}
	return count;
}
template <typename Iterator,typename  T>
size_t count_if_equal(Iterator begin,Iterator end, const T& val){
		size_t count = 0;
	while(begin != end){
		if(*begin == val){
			count++;
		}
		++begin;
	}
	return count;
}


int main () {

	using namespace std;
	using namespace std::chrono;
	using namespace pr;
	/*
	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les cara  ctères anormaux (négation des lettres)
	std::vector<std::pair<std::string,int>> vc;

	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		bool pres = false;
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		for(auto& paire:vc){
			std::string chaine = paire.first;

			if(chaine == word){
				pres = true;
				paire.second += 1;
				break;
			}

		}
		if(pres == false){
			nombre_lu++;
			vc.push_back(std::make_pair(word,1));
		}

	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	*/
	int arr[] = {1,2,3,2,2,4,5,6};
	int val = 2;
	size_t result = count(arr, arr+sizeof(arr)/sizeof(arr[0]));
	size_t result2 = count_if_equal(arr, arr+sizeof(arr)/sizeof(arr[0]),val);
	std::cout <<"Le nombre d'éléments est :" << result << std::endl;
	std::cout <<"Le nombre d'éléments égaux à 2 est :  " << result2 << std::endl;
	size_t u = 4;
	HashTable<int,int>*h;
	return 0;
}


