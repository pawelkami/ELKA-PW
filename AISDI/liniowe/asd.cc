/**
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>
#include <climits>

#ifdef _SUNOS
#include "/materialy/AISDI/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif


//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
	Node* wardener = new Node(P(INT_MAX,"\0"),first,first);
	wardener->internalDataPointer = wardener;
	first = wardener;
};

ListMap::ListMap( const ListMap& m )
{
   ///@todo Zaimplementować metode
	/*Node* temp;
	Node* temp2;

	first = new Node(m.first->data,first,first);
	first->internalDataPointer = first;
	temp = m.first->next;
	temp2 = first;
	
	
	for(; temp->data.first != INT_MAX; temp = temp->next, temp2 = temp2->next)
	{
		Node* new_node = new Node(temp->data,(Node*)m.first->internalDataPointer,temp2);
		new_node->internalDataPointer = NULL;
		temp2->next = new_node;
		//temp2 = temp2->next;
		//temp2->prev = new_node;
	}*/
	const_iterator it = m.end();
	Node* last;
	last = new Node(*it);
	last->next = last;
	last->prev = last;

	if(m.empty())
	{
		last->internalDataPointer = last;
		first = last;
		return;
	}

	Node *next_node = last;
	Node *new_node;

	do
	{
		--it;
		new_node = new Node(*it, next_node,NULL);
		next_node->prev = new_node;
		next_node->internalDataPointer = NULL;

		next_node = new_node;
	}
	while(it != m.begin());

	next_node->prev = next_node;
	next_node->internalDataPointer = last;
	first = next_node;
};

ListMap::~ListMap()
{
   clear();
   delete first;
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
	iterator it = find(entry.first);
	if(it != end())
        return std::make_pair(it, (bool)false);

   Node* new_node = new Node(entry);

   if(empty())
   {
	   Node* last = (Node*) first->internalDataPointer;
	   first->internalDataPointer = NULL;
	   new_node->next = first;
	   first->prev = new_node;
	   new_node->prev = new_node;
	   new_node->internalDataPointer = last;
	   first = new_node;

	   it = iterator(first);
	   return std::make_pair(it, (bool)true);
   }
   
    Node* nastepny = it.node;
	Node* poprzedni = nastepny->prev;

	new_node->internalDataPointer = NULL;
	poprzedni->next = new_node;
	new_node->prev = poprzedni;
	new_node->next = nastepny;
	nastepny->prev = new_node;
    it = iterator(new_node);

   return std::make_pair(it, (bool)true);
}

// Wstawienie elementu do mapy.
// Matoda zaklada, ze w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
	Node* new_node = new Node(entry);

	if(empty())
	{
		Node* last = (Node*) first->internalDataPointer;
		first->internalDataPointer = NULL;
		new_node->next = first;
		first->prev = new_node;
		new_node->prev = new_node;
		new_node->internalDataPointer = last;
		first = new_node;

		return iterator(new_node);
	}
	iterator it;
	for(it = begin(); it != end(); it++);
	
	Node* nastepny = it.node;
	Node* poprzedni = nastepny -> prev;

	new_node->internalDataPointer = NULL;
	poprzedni->next = new_node;
	new_node->prev = poprzedni;
	new_node->next = nastepny;
	nastepny->prev = new_node;

   it = iterator(new_node);

   return iterator(new_node);
}


 //Zwraca iterator addresujący element w mapie dla którego klucz jest równy
 //szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
   ///@todo Zaimplementować metode

   ListMap::iterator it;
   for(it = begin(); it != end(); it++)
   {
	   if(it->first == k)
			return it;
   }
   return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
   ///@todo Zaimplementować metode
	ListMap::const_iterator it = begin();
	for(; it != end(); ++it)
	{
		if(it->first == k)
			return it;
	}
    return end();
}


// Udostępnia wartość powiązaną z kluczem key. Wstawia element do mapy jeśli
// nie istniał.
// @returns Referencje do wartości powiązanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
   ///@todo Zaimplementować metode
	ListMap::iterator it;
	it = find(k);
	if(it == end())		//jesli nie znalazlo
	{
		return(insert(std::pair<Key,Val>(k,"\0")).first)->second;
	}
   return it->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
   return begin() == end();
}

// Zwraca ilość elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
   ///@todo Zaimplementować metode
   const_iterator it;
   int i=0;
   for(it=begin(); it != end(); it++)		//przejdz liste
	   i++;				//zliczaj
   return i;
}

// Zwraza ilość elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
   ///@todo Zaimplementować metode
   ListMap::const_iterator it = find(_Key);
   if(it == end())		//jesli nie znajdzie
	   return 0;
   return 1;  // this is not a multimap
}

 //Usuwa element z mapy.
 //@returns iterator adresujący pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
	if (i.node == first)
	{
		Node* last = (Node*) first->internalDataPointer;	//"za" ostatni element

		Node* to_kill = first;			//usuwamy pierwszego
		first = first->next;
		first->prev = first;
		first->internalDataPointer = last;		//internal pokazuje na koniec listy

		delete to_kill;					//usuwamy element

		return iterator(first);			//zwracamy iterator na nowy pierwszy element
	}


	Node* to_kill = i.node;
	Node* after_kill = to_kill->next;		//potrzebny do returna - wskaznik na element za usuwanym
	to_kill->prev->next = after_kill;
	after_kill->prev = to_kill->prev;
	delete to_kill;
	
	return iterator(after_kill);			//zwracamy iterator na element za usuwanym
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest określa pierwszy element do usunięcia, a last określa element
// po ostatnim usuniętym elemencie.
// @returns iterator adresujący pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
   ///@todo Zaimplementować metode
	if( f != l && f.node != NULL)		//dopoki f nie dojdzie do l i dopoki sa jeszcze elementy
		f=erase(f);
   return end();
}

// Usuwa element z mapy.
// @returns Ilość usuniętych elementów.
//          (nie jest to multimapa, więć może być to wartość 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
   ///@todo Zaimplementować metode
	ListMap::iterator it = find(key);
	if(it != erase(it))
		return 1;
   return 0;
}

// Usunięcie wszystkich elementów z mapy.
void ListMap::clear( )
{	
	if(empty())
		return;

	Node* last = (Node*) first->internalDataPointer;
	Node* to_kill = first;

	while(to_kill != last)
	{
		Node* temp = to_kill->next;
		delete to_kill;
		to_kill = temp;
	}

	last->prev = last;
	last->internalDataPointer = last;

	first = last;

}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeśli wewnętrzne struktury map są identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementować metode
	if(empty() && another.empty()) return true;		//jesli sa puste to zwroc true
	
	const_iterator tmp1 = begin();
	const_iterator tmp2 = another.begin();

	if(size() == another.size())
	{

		while(tmp1 != end() && tmp2 != another.end())			//przejdz cala liste az do konca
		{
			if(tmp1->first == tmp2->first)		//jezeli klucze sie zgadzaja to przejdz do nastepnych
			{
				tmp1++;
				tmp2++;
			}
			else 
				return false;				//jezeli klucze sie nie zgadzaja to zwroc false
		}
	}
	else
		return false;		//rozne rozmiary

	return true; // doszlo do konca wiec sa rowne
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach są identyczne.
// Zwraca true jeśli mapy zwierają takie same pary klucz-wartość.
bool ListMap::info_eq(const ListMap& another) const
{
   ///@todo Zaimplementować metode
	ListMap::const_iterator it, jt;

	if(size() != another.size()) return false;				//jezeli rozmiary rozne to rozne dane

	for(it=begin(); it != end(); it++)			//przejdz po calej liscie
	{
		jt =  another.find(it->first);			//znajdz ten sam element w drugiej liscie
		if(it->second != jt->second)			//jesli sa rozne to false
			return false;
	}
	return true;
}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
   ///@todo Zaimplementować metode
	//if(node->next == NULL) return *this;				//*this
	
	if(node)
		node=node->next;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
   ///@todo Zaimplementować metode
	ListMap::const_iterator tmp = *this;			//zapamietaj w tmp *this
	if(node)				//jesli jest co przesuwac to przesun
		node=node->next;
   return tmp;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   ///@todo Zaimplementować metode
	if(node)
		node=node->prev;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
   ///@todo Zaimplementować metode	
	ListMap::const_iterator temp = *this;
	if(node)
		node=node->prev; //postdekrementacja
   return temp;
}

/// Zwraca iterator addresujący pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
   ///@todo Zaimplementować metode
   return iterator(first);
}

/// Zwraca iterator addresujący pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
   ///@todo Zaimplementować metode
   return iterator(first);
}

/// Zwraca iterator addresujący element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
   ///@todo Zaimplementować metode
	Node* last = (Node*) first->internalDataPointer;
	return iterator(last);
}

/// Zwraca iterator addresujący element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
   ///@todo Zaimplementować metode
	Node* last = (Node*) first->internalDataPointer;
	return iterator(last);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przykład map'y z implementacją podobną do std::map.
/// To jest jedynie przykład!!!
/// Normalnie implementacja powinna opierać się o drzewo lub tablicę haszującą.
template <class Key, class Val>
class SmallMap
{
   std::pair<Key, Val> tab[2];
   int isOcupied[2];
public:

   SmallMap()
   {
      for(unsigned i=0; i<2; ++i)
      {
         isOcupied[i]=0;
      }
   }

   typedef std::pair<Key, Val>* iterator;   ///< Każdy wskaźnik jest też iteratorem.

   iterator begin() { return tab; }
   iterator end() { return tab+2; }

   Val& operator[](const Key& k)
   {
      static Val val;
      for(unsigned i=0; i<2; ++i)
      {
         if(isOcupied[i]&&tab[i].first==k)
            return tab[i].second;
      }
      // create
      for(unsigned i=0; i<2; ++i)
      {
         if(!isOcupied[i])
         {
            tab[i].first=k;
            isOcupied[i]=1;
            return tab[i].second;
         }
      }
      //std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      //assert(0);
      return val;   // Mało sensowne, ale to jest tylko przykłąd
   }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

#include <map>

/// Testy u¿ytkownika
void test()
{
   // A typedef used by the test.
   typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   //typedef ListMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;

   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";

   for_each(m.begin(), m.end(), print );
   //system("PAUSE");
}

