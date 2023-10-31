#include <cstddef>
#include <vector>
#include <forward_list>
#include <iostream>
using namespace std;
namespace pr {

template <typename K, typename V>

class HashTable{
    public :
    class Entry{
        public:
        const K key;
        V value;
        Entry(const K& key, const V& value):key(key), value(value){}
    };

    public:
    std::vector <std::forward_list<Entry>> bucket ;
    size_t sz;
    //Nombre d'entrées


    public :
    HashTable(size_t szb) : bucket(szb){
        sz = 0;
    }
    const std::vector <std::forward_list<Entry>>& getBucket(){return bucket;}

    // (Les mécanismes de la classe canonique sont implémentés par défaut par le compilateur, pas besoin de les réécrire.)

    /*Fonction qui rend l'adresse de la valeur associée à la clé key si on la trouve, nullptr sinon*/
    V* get (const K & key){
        size_t ind = (std::hash<K>() (key)) % bucket.size();    //Hasher standard

        /*Trouver le mot dans la hashmap*/
        for (auto& e : bucket[ind]){
            if (e.key == key){
                return &e.value;
            }
        }
        return nullptr;
    }
    /*Fonction qui ajoute l'association (key, value) à la table.
    * La fonction rend vrai si la valeur associée à key a été mise à jour dans la table,
    * et faux si on a réalisé une insertion (la clé n'était pas encore dans la table).*/
    bool put (const K & key, const V value){
        size_t ind = std::hash<K>() (key) % bucket.size();

        for(auto & e : bucket[ind]){
		    if (e.key == key){
                e.value = value;
                return true;
            }
    	}
        /*On ne l'a pas trouvé dans le bucket, il faut créer l'association dans la table*/
        bucket[ind].emplace_front(key,value);           //emplace évite de créer un temporaire
        ++sz;                 //La taille de la Hashtable augmente
        return false;           //On a créé une insertion
    }
    /*Fonction qui indique la taille de la hashtable (nombre d'entrées effectives dedans)*/
    size_t size() const{return sz;}

    class iterator {
        public:
            iterator(HashTable<K, V>& hashTable, bool end = false)
                : hashTable(hashTable), currentBucket(0) {
                if (!end) {
                    listIt = hashTable.bucket[currentBucket].begin();
                }
                else {
                    listIt = hashTable.bucket[currentBucket].end();
                }
                findNextEntry();
            }

            iterator& operator++() {
                ++listIt;
                findNextEntry();
                return *this;
            }

            bool operator!=(const iterator& other) const {
                return currentBucket != other.currentBucket || listIt != other.listIt;
            }

            typename HashTable<K, V>::Entry& operator*() {
                return *listIt;
            }

        private:
            void findNextEntry() {
                while (currentBucket < hashTable.bucket.size()) {
                    if (listIt == hashTable.bucket[currentBucket].end()) {
                        ++currentBucket;
                        if (currentBucket < hashTable.bucket.size()) {
                            listIt = hashTable.bucket[currentBucket].begin();
                        }
                    } else {
                        break;
                    }
                }
            }

            HashTable<K, V>& hashTable;
            size_t currentBucket;
            typename std::forward_list<typename HashTable<K, V>::Entry>::iterator listIt;
        };

    typename std::vector<std::forward_list<Entry>>::iterator begin() {
        return bucket.begin();
    }

    typename std::vector<Entry>::iterator end() {
        return bucket.end();
    }


	};
	template<typename Iterator>
    		Iterator find(Iterator lit,Iterator end){
    	}

	};
