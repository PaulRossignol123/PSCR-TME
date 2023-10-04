#include <cstddef>
#include <vector>
#include <forward_list>

/*À FAIRE
    * Voir comment utiliser la fonction de hachage
    */


using namespace std;
namespace pr {

template <typename K, typename V>

class Hashtable{
    public :
    class Entry{
        public:
        const K key;
        V value;
        Entry(const K& key, const V& value):key(key), value(value){}
    };

    private :
    std::vector <std::forward_list<Entry>> bucket ;
    size_t sz;                    //Nombre d'entrées

    public :
    Hashtable(size_t szb) : bucket(szb){
        sz = 0;
    }
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
    };
}
