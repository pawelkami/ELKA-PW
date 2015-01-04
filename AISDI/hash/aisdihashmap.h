/** 
@file aisdihashmap.h

AISDIHashMap and related functions interface.
      
@author
Pawel Cichocki

@date  
last revision
- 2006.03.24 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2006 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <utility>
#include <iterator>

#define SIZE	65536

/// Default keys' comparing function for AISDIHashMap - it uses
/// operator== by default.
/// @returns true if keys are equal, false otherwise.
/// @param key1 First key to compare. 
/// @param key2 Second key to compare. 
template <class Key>   

//funkcja porownujaca, zwracamy true jezeli klucze sa rowne
inline bool _compFunc(const Key& key1,const Key& key2)
{
   return (key1==key2);
};

//funkcja mieszajaca
unsigned hashF(const std::string& m)
{
	unsigned hash = 1500101028;
	unsigned i = 0;
	while (m[i]!='\0') hash = hash ^ ((hash << 4) ^ (hash >> 9)) ^ m[i++];
	return (hash % SIZE);
};
/// A map with a similar interface to std::map.
template<class K, class V,
         unsigned hashFunc(const K&),
         bool compFunc(const K&,const K&)=&_compFunc<K> >
class AISDIHashMap
{
public:
   typedef K key_type;
   typedef V value_type;
   typedef unsigned size_type;
   typedef std::pair<K, V> P;

   struct Node						//wezel w naszej mapie
   {
	   unsigned hash;				//hash jaki ma element
	   Node *next;
	   Node *prev;
	   P data;

	   Node(const std::pair<K,V>& d) : next(NULL), prev(NULL), data(d) {}
	   Node(const std::pair<K,V>& d, Node* n, Node* p) : next(n), prev(p), data(d) {}
   };

   Node *sentinel;				//wskaznik na straznika
   Node *hash_table[SIZE+1];			//hash table
		

   AISDIHashMap()					//konstruktor domyslny
   {
      for(int i = 0; i < SIZE; i++)			//zerujemy cala tablice
	  hash_table[i] = NULL;
  
	  sentinel = new Node(std::make_pair(K(),V()));
	  sentinel->hash = 0;
	  sentinel->next = sentinel->prev = sentinel;
   }
   
   ~AISDIHashMap()
   {
	  erase(begin(),end());
	  delete sentinel;
   }

   /// Coping constructor.
   explicit AISDIHashMap(const AISDIHashMap<K, V, hashFunc, compFunc>& a)
   {
	   sentinel = new Node(std::make_pair(std::string("\0"), V(0)));
	   sentinel -> hash = 0;

	   for(int i=0; i < SIZE; ++i)				//zerujemy tablice
	   {
		   hash_table[i] = NULL;
	   }

	   Node* tmp = a.sentinel->next;

	   while(tmp != sentinel)
	   {
	   	insert(std::make_pair(K(tmp->data.first), V()));
		tmp = tmp->next;
	   }
   }

   /// const_iterator.
   class const_iterator : public std::iterator< std::forward_iterator_tag, std::pair<K, V> >
   {
   protected:
	   friend class AISDIHashMap;
	   Node* node;
	   Node* sentinel;

   public:
	   const_iterator() {}
	   const_iterator(Node* nod, Node* s) : node(nod), sentinel(s) {}
	   const_iterator(const_iterator &i) : node(i.node), sentinel(i.sentinel) {}

	   const_iterator operator++(int)			// i++
	   {
		   if(node == sentinel) return *this;
		   const_iterator temp = *this;
		   node = node->next;
		   return temp;
	   }

	   const_iterator& operator++()				//++i
	   {
		   if(node != sentinel) node = node->next;
		   return *this;
	   }

	   const_iterator operator--(int)				//i--
	   {
		   if(node->prev == sentinel) return *this;
		   const_iterator tmp = *this;
		   node = node->prev;
		   return tmp;
	   }

	   const_iterator& operator--()					//--i
	   {
		   if(node->prev != sentinel) node = node->prev;
		   return *this;
	   }

	   inline bool operator==(const const_iterator &a) const		//TRUE jesli rowne
	   {
		   return (node == a.node);
	   }

	   inline bool operator!=(const const_iterator &a) const		//true jesli nierowne
	   {
		   return (node != a.node);
	   }

	   inline const P* operator*() const 
	   { 
		   return node->data;
	   }
	   
	   inline const P* operator->() const 
	   { 
		   return &(node->data);
	   }
   };


   /// iterator.
   class iterator : public const_iterator
   {
   private:
	   friend class AISDIHashMap;

   public:
	   iterator() {}
	   iterator(Node *n, Node* s): const_iterator(n,s) {}
	   iterator(const iterator &a)
	   {
		   this->node = a.node;
		   this->sentinel = a.sentinel;
	   }

	   inline iterator operator++(int)			//i++
	   {
		   iterator it = *this;
		   ++(*this);
		   return it;
	   }

	   inline iterator& operator++()			//++i
	   {
		   ++(*(const_iterator*)this);
		   return *this;
	   }

	   inline iterator operator--(int)			//i--
	   {
		   iterator it = *this;
		   --(*this);
		   return it;
	   }

	   inline iterator& operator--()			//--i
	   {
		   --(*(const_iterator*)this);
		   return *this;
	   }

	   inline P* operator*() const
	   {
		   return this->node->data;
	   }

	   inline P* operator->()
	   {
		   return &(this->node->data);
	   }
   };

   /// Returns an iterator addressing the first element in the map.
   inline iterator begin()
   {
	   return iterator(sentinel->next, sentinel);
   }

   inline const_iterator begin() const
   {
	   return const_iterator(sentinel->next, sentinel);
   }

   /// Returns an iterator that addresses the location succeeding the last element in a map.
   inline iterator end()
   {
		return iterator(sentinel, sentinel);
   }

   inline const_iterator end() const
   {
	   return const_iterator(sentinel, sentinel);
   }
   /// Inserts an element into the map.
   /// @returns A pair whose bool component is true if an insertion was
   ///          made and false if the map already contained an element
   ///          associated with that key, and whose iterator component coresponds to
   ///          the address where a new element was inserted or where the element
   ///          was already located.
   std::pair<iterator, bool> insert(const std::pair<K, V>& entry)
   {
	   unsigned hashed = hashFunc(entry.first);			//wyliczamy hash elementu ktory wstawiamy
	   Node* temp = hash_table[hashed];
   
	   if(temp != NULL)				//mamy juz element pod tym hashem
	   {
		   while(temp->hash == hashed && temp != sentinel)
		   {
			   if(entry.first == temp->data.first)			//mamy juz taki element
			   {  
				   return std::make_pair(iterator(temp, sentinel), false);
			   }
			   temp = temp->next;
		   }
		   Node* wsk = new Node(entry, temp, temp->prev);
		   temp->prev->next = wsk;
		   temp->prev= wsk;
		   wsk->hash = hashed;

		   return std::make_pair(iterator(wsk,sentinel), true);
		   
	   }
		
	   //jezeli nie ma elementu o takim hashu
	   Node* wsk = new Node(entry, sentinel, sentinel->prev);
	   sentinel->prev->next = wsk;
	   sentinel->prev= wsk;
	   wsk->hash = hashed;
	   hash_table[hashed] = wsk;

	   return std::make_pair(iterator(wsk,sentinel),true);

   }

   /// Returns an iterator addressing the location of the entry in the map
   /// that has a key equivalent to the specified one or the location succeeding the
   /// last element in the map if there is no match for the key.
   iterator find(const K& k)
   {
	   unsigned hashed = hashFunc(k);

	   if(hash_table[hashed] == NULL)
		   return end();

	   Node* temp = hash_table[hashed];

	   while(temp->hash == hashed && temp != sentinel)
	   {
		   if(temp->data.first == k)
			   return iterator(temp, sentinel);
		   temp = temp->next;
	   }

	   return end();
   }

   /// Returns an const iterator
   const_iterator find(const K& k) const
   {
	   unsigned hashed = hashFunc(k);		//hash pod ktorym znajduje sie element

	   if(hash_table[hashed] == NULL)		//jesli tablica pod tym hashem jest pusta to zwroc end()
		   return end();

	   Node* temp = hash_table[hashed];

	   while(temp->hash == hashed && temp != sentinel)
	   {
		   if(temp->data.first == k)
			   return const_iterator(temp, sentinel);
		   temp = temp->next;
	   }

	   return end();
   }
 
   /// Inserts an element into a map with a specified key value
   /// if one with such a key value does not exist.
   /// @returns Reference to the value component of the element defined by the key.
   V& operator[](const K& k)
   {
	   iterator it;
	   it = (insert(std::make_pair(K(k), V()))).first;
	   return it->second;
   }

   /// Tests if a map is empty.
   bool empty( ) const
   { 
	return begin() == end();
   }

   /// Returns the number of elements in the map.
   size_type size() const
   {
	  unsigned int i = 0;
	  Node* temp = sentinel->next;
	  while(temp != sentinel)
	  {
		i++;
		temp = temp->next;
	  }
	  return i; 
   }
   /// Returns the number of elements in a map whose key matches a parameter-specified key.
   size_type count(const K& _Key) const
   {
	   unsigned hashed = hashFunc(_Key);
	   int i = 0;

	   if(!hash_table[hashed]) return 0;
	
	   Node* temp = hash_table[hashed];

	   while(temp != sentinel && temp->hash == hashed)
	   {		
		   if(compFunc(temp->data.first, _Key))
			   return 1;
		   temp = temp->next;
	   }

	   return 0;
   }

   /// Removes an element from the map.
   /// @returns The iterator that designates the first element remaining beyond any elements removed.
   iterator erase(iterator i)
   {
	   if(i.node == sentinel) return end();			//gdy chcemy usunac straznika

	   unsigned hashed = i.node->hash;

	   Node* temp = i.node;

	   if(temp == hash_table[hashed])
	   {
		   if((temp->next->hash != hashed) || temp->next == sentinel)
			   hash_table[hashed] = NULL;
		   else 
			   hash_table[hashed] = temp->next;
	   }

	   temp->next->prev = temp->prev;
	   temp->prev->next = temp->next;

	   i = iterator(temp->next, sentinel);
	   delete temp;
	   return i;
   }
   
   /// Removes a range of elements from the map.
   /// The range is defined by the key values of the first and last iterators
   /// first is the first element removed and last is the element just beyond the last elemnt removed.
   /// @returns The iterator that designates the first element remaining beyond any elements removed.
   iterator erase(iterator first, iterator last)
   {
	   if(first == end()) return end();
 
	   for(iterator it = first; it != last; it++)
	   {
		   erase(it);
	   }
	   return last;
   }
   
   /// Removes an element from the map.
   /// @returns The number of elements that have been removed from the map.
   ///          Since this is not a multimap itshould be 1 or 0.
   size_type erase(const K& key)
   {
	   unsigned hashed = hashFunc(key);

	   if(!hash_table[hashed]) return 0;

	   Node *temp = hash_table[hashed];

	   if(temp->data.first == key)					//jesli klucze sie zgadzaja
	   {
		   if(temp->next->hash == hashed && temp->next != sentinel)	//jesli jest tylko jeden element pod tym hashem
		   {
			   hash_table[hashed] = temp->next;	//jesli nie to od teraz pokazuj nastepny			   
		   }
		   else
		   {
			   hash_table[hashed] = NULL;		//to wyzeruj to pole tablicy
		   }
	   } 
	   else 
	   {
          	while(temp->data.first != key)
 	   	{
         		if(temp == sentinel) return 0;               //doszlismy do konca
          		if(temp->next->hash != hashed) return 0;
          		temp = temp->next;
        	}
      }
	   
	   temp->prev->next = temp->next;
	   temp->next->prev = temp->prev;

	   delete temp;

	   return 1;
   }

   /// Erases all the elements of a map.
   void clear( )
   {
	   if(empty()) return;		//jesli pusta to nic nie trzeba usuwac
	   erase(begin(),end());		//wyczysc od poczatku do konca
	 
	   sentinel->next = sentinel->prev = sentinel;			//ustawiamy straznika

	   for(int i = 0; i < SIZE; i++)				//zerujemy tablice
		   hash_table[i] = NULL;
   }

};
