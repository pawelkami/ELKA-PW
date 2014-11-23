﻿/** 
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
///
COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/home/common/dyd/aisdi/liniowe/ListMap.h" 
#else
#include "./ListMap.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
  std::pair<int, std::string> para(0, "\0");
  first = new ListNode(para);           //alokacja pamieci na straznika
  first->next = first;
  first->prev = first;                  //ustawienie wskaznikow w strazniku
}

ListMap::ListMap(const ListMap &m)
{
  std::pair<int, std::string> para(0, "\0");
  first = new ListNode(para);           //alokacja pamieci na straznika

  ListNode *tmp = m.first->next;        //wskaznik do przeszukiwania pierscienia
  ListNode *tmp2 = first, *n;           //wskaznik do przeszukiwania pierscienia

  for(; tmp != m.first; tmp = tmp->next)
  {
    n = new ListNode(tmp->data, NULL, tmp2);    //nowy element pierscienia
    tmp2->next = n;                             //ustawienie wskaznika pop. el.
    tmp2 = tmp2->next;                          //zapisanie wskaznika ost. el.
  }//for

  tmp2->next = first;           //polaczenie ostatniego el. ze straznikiem
  first->prev = tmp2;
}

ListMap & ListMap::operator=(const ListMap &m)
{
  clear();
  for(iterator i=m.begin();i!=m.end();i++)
    unsafe_insert(*i);
  return *this;
}

ListMap::~ListMap()
{
  clear();                              //usuniecie wszystkich elementow
  delete first;                         //usuniecie straznika
}

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony 
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first==entry.first)
    {
      iterator i = tmp;                        //iterator, ktory zwrocimy
      return std::make_pair(i, (bool)false);
    }
    if(tmp->data.first>entry.first) break;     //znalezlismy miejsce do wstawienia elementu
  }//for
  
  ListNode *n = new ListNode(entry, tmp, tmp->prev);        //dodajemy element
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  iterator i = n;                                           //iterator, ktory zwrocimy
  return std::make_pair(i, (bool)true);                     //zwracamy iterator na dod. el.
}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first && tmp->data.first<entry.first; tmp = tmp->next) {}
  //idziemy po pierscieniu do straznika albo do wartosci o kluczu wiekszym od entry
  
  ListNode *n = new ListNode(entry, tmp, tmp->prev);        //dodajemy element
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  iterator i = tmp;
  return i;                                                 //zwracamy iterator
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy 
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
  iterator i;

  for(i=begin() ; i!=end() && i->first!=k ; ++i) {}
  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k

  return i;
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
  iterator i;

  for(i=begin() ; i!=end() && i->first!=k ; ++i) {}
  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k

  return (const_iterator)i;
}

// Udostêpnia wartoæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeli 
// nie istnia³.
// @returns Referencje do wartoci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == k)           //znalezlismy element o podanym kluczu
    {
      ListMap::Val &ref = tmp->data.second;
      return ref;                      //zwracamy referencje
    }
    if(tmp->data.first > k) break;     //elementu o podanym kluczu nie ma
  }//for
  
  std::pair<int, std::string> dane(k, "lol");   //dane dla nowego elementu
  ListNode *n = new ListNode(dane, tmp, tmp->prev);         //dodajemy element
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  ListMap::Val &ref = n->data.second;
  return ref;                          //zwracamy referencje do wartosci w ListNode
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
  return first==first->next;                            //straznik wskazuje na siebie
}

// Zwraca iloæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
  unsigned long sum = 0;
  for(ListNode *tmp = first->next; tmp != first; tmp = tmp->next)
    sum++;                             //dodanie aktualnego elementu
  return sum;                          //zwrocenie wyniku
}

// Zwraza iloæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
  iterator i;

  for(i=begin(); i!=end(); ++i)
    if(i->first == _Key) return 1;
  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k

  return 0;                            //nie znaleziono takiego klucza
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == i->first)    //znalezlismy element o podanym kluczu
    {
      ++i;                             //zwiekszamy iterator do zwrocenia
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;     //ustawienie wskaznikow
      delete tmp;                      //zwolnienie pamieci
      return i;                        //zwracamy iterator na nastepny element
    }
    if(tmp->data.first > i->first) break;   //elementu o podanym kluczu nie ma
  }//for

  return end();                        //nic nie usunieto
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okrela pierwszy element do usuniêcia, a last okrela element 
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
  iterator i;                          //pomocniczy iterator
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  //sprawdzamy czy nie mamy iteratorow wskazujacych na ten sam element
  if(f->first == l->first) return l;

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == f->first) break;    //znalezlismy element
    if(tmp->data.first > f->first) return l;  //nie ma takiego elementu
  }//for

  ListNode *tmp2 = tmp->next;
  tmp = tmp->prev;      //cofamy sie do ost. elementu, ktorego nie kasujemy

  for(;; tmp2 = tmp2->next) 
  {
    delete tmp2->prev;                                      //usuniecie
    if(tmp2 == first) break;                                //koniec listy
    if(tmp2->data.first >= l->first && l->first) break;     //doszlismy za l
  }//for

  tmp->next = tmp2;                                  //ustawienie wskaznikow
  tmp2->prev = tmp;

  return l;                                          //zwrocenie iteratora
}

// Usuwa element z mapy.
// @returns Iloæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == key)         //znalezlismy element o podanym kluczu
    {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;     //ustawienie wskaznikow
      delete tmp;                      //zwolnienie pamieci
      return 1;                        //usunelismy jeden obiekt
    }
    if(tmp->data.first > key) break;   //elementu o podanym kluczu nie ma
  }//for

  return 0;                            //nic nie usunieto

}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear()
{
  ListNode *tmp = first->next;

  while(tmp != first) 
  {
    tmp = tmp->next;                   //nastepny element
    delete tmp->prev;                  //usunecie poprzedniego
  }//while

  first->next = first;                 //ustawienie wskaznikow
  first->prev = first;
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeli wewnêtrzne struktury map s¹ identyczne.:
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
   //assert(0);                                 WTF?!
   return true;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeli mapy zwieraj¹ takie same pary klucz-wartoæ.
bool ListMap::info_eq(const ListMap& another) const
{
  ListNode *tmp = first;                //wskaznik przeszukujacy pierwsza mape
  ListNode *tmp2 = another.first;       //wskaznik przeszukujacy druga mape

  //dwie puste mapy
  if(tmp->next == tmp && tmp2->next == tmp2) return true;

  //jedna pusta mapa
  if(tmp->next == tmp || tmp2->next == tmp2) return false;

  while(1)                              //petla sprawdzajaca
  {
    tmp = tmp->next;                    //przejscie do kolejnych elementow
    tmp2 = tmp2->next;

    //rozne zawartosci elementow
    if(tmp->data != tmp2->data) return false;
    
    //elementy sie zgadzaja, jesli obie mapy sie koncza, to sa takie same
    if(tmp->next == first && tmp2->next == another.first) return true;

    //jesli tylko jedna kolejka sie konczy to mapy sa rozne
    if(tmp->next == tmp || tmp2->next == tmp2) return false;
  }//while(1)
}


// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
   /*if(node != ListMap::first)*/ node = node->next;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
//   if(node == ListMap::first) return *this;
   const_iterator tmp = *this;
   node = node->next;
   return tmp;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   /*if(node != ListMap::first->next)*/ node = node->prev;
   node = node->prev;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
//   if(node == ListMap::first->next) return *this;
   const_iterator tmp = *this;
   node = node->prev;
   return tmp;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{ 
   return iterator(first->next); 
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{ 
   return const_iterator(first->next); 
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.   
ListMap::iterator ListMap::end()
{ 
   return iterator(first); 
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.   
ListMap::const_iterator ListMap::end() const
{ 
   return const_iterator(first); 
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk³ad map'y z implementacj¹ podobn¹ do std::map.
/// To jest jedynie przyk³ad!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszuj¹c¹.
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

   typedef std::pair<Key, Val>* iterator;   ///< Ka¿dy wskanik jest te¿ iteratorem.

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
      return val;   // Ma³o sensowne, ale to jest tylko przyk³¹d
   }
};
      

//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

//Funkcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>
/*
/// Testy u¿ytkownika
void test()
{
   // A typedef used by the test.
   //typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   typedef ListMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;  
   std::cout << "m.empty()? " << m.empty() << std::endl;
   
   m[2] = "Merry";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[4] = "Jane";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[8] = "Korwin";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[4] = "Magdalena";
   std::cout << "m.size()? " << m.size() << std::endl;

   TEST_MAP n = m;

   std::cout << "n==m? " << n.info_eq(m) << std::endl;
   std::cout << "n.empty()? " << n.empty() << std::endl;
   std::cout << "m.empty()? " << m.empty() << std::endl;
   for_each(m.begin(), m.end(), print );
   for_each(n.begin(), n.end(), print );
   //system("PAUSE");
}*/


//////////////////////////////////////////////////////////////////////////////
// Testy Z HNN!!!
//////////////////////////////////////////////////////////////////////////////

bool test1(){ // 1 - ok, 0 - zle
   bool ret(0);
   ListMap mapa;
   mapa[1] = "czaslaw";
   mapa[2] = "maciek";
   mapa[3] = "bozena";
   mapa[4] = "rysiek"; // z Klanu
   ListMap kopia = mapa;

   std::cout << "\nTestowanie erase na nie swojej mapie: ";
   ListMap::iterator kopia_it(kopia.begin());   // bierzemy iterator kopii
   mapa.erase(kopia_it);                        // i ka¿emy nim skasowac cos z mapy
   ret = mapa.struct_eq(kopia);                 // blad jesli cos sie skasowalo
   std::cout << (ret ? "Dobrze" : "Zle") << "\n";

   if(ret == 0){
      std::cout << "\n\nmapa:\n";
      for_each(mapa.begin(), mapa.end(), print);
      std::cout << "\nkopia:\n";
      for_each(kopia.begin(), kopia.end(), print);
   }
   return ret;
}

#include <sstream>
#include <string>

#define OK { std::cout<<++licznikOkejek<<" [OK] "; }
bool test2()
{
  int licznikOkejek=0;
  //typedef std::map<int, std::string> TEST_MAP;
  typedef ListMap TEST_MAP;
  std::cout << "Testy uzytkownika" << std::endl;

  TEST_MAP m;
  std::pair<int, std::string> a(1, "lukasz");
  std::pair<int, std::string> b(2, "robert");
  std::pair<int, std::string> c(3, "tomek");
  std::pair<int, std::string> d(4, "agata");
  std::pair<int, std::string> e(5, "michal");
  std::pair<int, std::string> f(6, "ania");
  m.insert(a);
  m.insert(b);
  m.insert(c);
  m.insert(d);
  m.insert(e);
  m.insert(f);
  if (!(m.insert(a).second == false))
    std::cout << "Wstawianie drugiego takiego samego elementu...   [BLAD]"
        << std::endl;
  else OK
  TEST_MAP::const_iterator i;
  for (i = m.begin(); i != m.end(); ++i)
    ;
  if (!(i == m.end()))
    std::cout << "Przechodzenie iteratorem ++iterator...   [BLAD]" << std::endl;
  else OK
  if (!((m.find(1) != i) && (m.find(2) != i) && (m.find(3) != i) && (m.find(4)
      != i) && (m.find(5) != i) && (m.find(6) != i) && (m.find(0) == i)))
    std::cout << "Sprawdzanie dzialania funkcji find...   [BLAD]" << std::endl;
  else OK
  if (!(m[1] == "lukasz"))
    std::cout << "Operator[]...   [BLAD]" << std::endl;
  else OK
  if (!(m.size() == 6))
    std::cout << "Sprawdzanie dzialania funkcji size...   [BLAD]" << std::endl;
  else OK
  if (!((m.count(6) == 1) && (m.count(0) == 0)))
    std::cout << "Sprawdzanie dzialania funkcji count...   [BLAD]" << std::endl;
  else OK
  //m.erase(m.find(1));
  //m.erase(m.find(6));
  //m.erase(m.find(4));
  TEST_MAP n(m);
  ////
  if (!((n.struct_eq(m)) && (n.info_eq(m))))
    std::cout
        << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla poprawnych...   [BLAD lub zalezy od implementacji]"
        << std::endl;
  else OK
  n.clear();
  ////
  if (!(!((n.struct_eq(m)) && (n.info_eq(m)))))
    std::cout
        << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla niepoprawnych...   [BLAD]"
        << std::endl;
  else OK
  n.insert(a);
  n.insert(f);
  n.insert(b);
  n.insert(c);
  n.insert(d);
  n.insert(e);
  ////
  if (!(n.info_eq(m)))
    std::cout
        << "Sprawdzanie dzialania funkcji info_eq dla poprawnych...   [BLAD]"
        << std::endl;
  else OK
  ////
  if (!n.struct_eq(m))
    std::cout
        << "Sprawdzanie dzialania funkcji struct_eq dla poprawnych...   [BLAD lub zalezy od implementacji]"
        << std::endl;
  else OK

  std::stringstream wynik;
  std::string jest, powinnobyc="6.5.4.4.3.3.5.5.";
  wynik<< n.size()<<".";
  n.erase(n.find(2));
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  n.erase(n.find(1));
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  //
  n.erase(n.find(99));
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  n.erase(6);
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  n.erase(78);
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;

  n.clear();
  n.insert(a);
  n.insert(b);
  n.insert(c);
  n.insert(d);
  n.insert(e);
  n.insert(f);
  i = n.find(6);
  TEST_MAP::iterator j = n.find(1);
  //
  n.erase(i, j);
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  i = n.find(1);
  //
  n.erase(i, i);
  wynik<< n.size()<<".";
  for (i = n.begin(); i != n.end(); ++i)
    ;
  wynik>>jest;
  if (jest != powinnobyc)
    std::cout<<"wypisalo: "<<jest<<" a powinno byc: "<<powinnobyc<<" [BLAD]"<< std::endl;
  else OK
  m.clear();
  n.clear();
  n.insert(a);
  n.insert(b);
  n.insert(c);
  n.insert(d);
  n.insert(e);
  n.insert(f);
  m.insert(a);
  m.insert(b);
  m.insert(c);
  m.insert(d);
  m.insert(e);
  m.insert(f);
  n.erase(n.find(4));
  if (!( n.erase(6) == 1 ))
    std::cout << "Usuwanie elem o kluczu 6 [BLAD]" << std::endl;
  else OK

  n.erase(1);
  //
  //n.erase(n.find(3), n.erase(n.end()));
  n.erase(n.find(3), n.end());
  if (!(n.size() == 1))
  {
    std::cout << "Usuwanie od drugiego elem do konca [BLAD lub zalezy od implementacji]" << std::endl;
    for_each(n.begin(), n.end(), print);
  }
  else OK
  n.erase(2);
  if (!(n.size() == 0))
  {
    std::cout << "Usuwanie ostatniego elementu [BLAD]" << std::endl;
    for_each(n.begin(), n.end(), print);
  }
  else OK
  //
  n.erase(n.find(0));
  for (i = m.begin(); i != m.end(); i++)
    ;
  m.clear();
  m.insert(a);
  m.insert(b);
  m.insert(c);
  m.insert(d);
  m.insert(e);
  m.insert(f);
  TEST_MAP n2(m);
  ////
  if (!((n2.struct_eq(m)) && (n2.info_eq(m))))
  {
    std::cout << "Kopiowanie kolejnosc...   [BLAD]" << std::endl;
    for_each(n2.begin(), n2.end(), print);
  }
  else OK
  std::cout<<"\nMax 15 okejek\n";
  return licznikOkejek == 15;
}

#define AXIOM(text) if(test_level>=2) std::cout<<"aksjomat: "<<text<<"\n";AXIOMTEXT=const_cast<char *>(text);
#define TST(preparation,val1,val2)     preparation;\
    if(!((val1==val2) && (val2==val1))) {                \
      std::cout<<"BLAD DLA AKSJOMATU: "<<AXIOMTEXT<<"\nTEST: "<<#preparation<<"\n"; \
      errors++;           \
    } else if(test_level>=3) \
      std::cout<<"test: "<<#preparation<<","<<"#val1"<<"#val2"<<"\n";

bool test3()
{
  // A typedef used by the test.
  //typedef std::map<int, std::string> TEST_MAP;
  //typedef SmallMap<int, std::string> TEST_MAP;
  typedef ListMap TEST_MAP;
  int test_level = 1; // im wiekszy tym wiecej gada

  TEST_MAP d1, d2; //Zmienne do testowania klasy
  const ListMap::Key k1 = 1; //Wartosci do testowania
  const ListMap::Key k2 = 2;
  const ListMap::Key k3 = 3;
  const ListMap::Val v1 = "v1_wartosc_danej"; //Wartosci do testowania
  const ListMap::Val v2 = "v2_wartosc_danej";
  const ListMap::Val v3 = "v3_wartosc_danej";

  int errors = 0;

  std::cout << "TESTOWANIE KLASY\n";

  char *AXIOMTEXT;

  AXIOM("ListMap { insert(ListMap::Key k, ListMap::Val v) } == { erase(k); unsafe_insert(k,v) }")

  TST(
      { d1.clear();d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2.erase(k1);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2.erase(k1);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2.erase(k1);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1,d2)

  //Operacja wstawiania usuwa i
  //wstawia bezwarunkowo-fizycznie
  AXIOM("ListMap { sprawdzenie_czy_wystepuje(ListMap::Key k) } == { }")
  //sprawdzenie_czy_wystepuje nie zmienia stanu obiektu

  TST(
      { d1.clear();d2=d1;(d2.find(k1) != d2.end() );},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2=d1;(d2.find(k1) != d2.end() );},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d2=d1;(d2.find(k1) != d2.end() );},d1,d2)

  AXIOM("bool { ListMap(); return sprawdzenie_czy_wystepuje(ListMap::Key k) } == false")
  //W pustym slowniku nie ma nic
  TST(
      { d1.clear();},(d1.find(k1) != d1.end() ),ListMap::Key(0))

  AXIOM("bool { unsafe_insert(ListMap::Key k, ListMap::Val v); return sprawdzenie_czy_wystepuje(k) } == TRUE")
  //Jesli ostatnio wstawiono, to nalezy
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},(d1.find(k1) != d1.end() ),ListMap::Key(1))
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},(d1.find(k1) != d1.end() ),ListMap::Key(1))

  AXIOM("bool { unsafe_insert(ListMap::Key k1, ListMap::Val v); return sprawdzenie_czy_wystepuje(ListMap::Key k2) } ==if (k1 != k2) { return sprawdzenie_czy_wystepuje(k2) }")
  //Jesli ostatnio nie wstawiono, to
  //szukaj we wczesniejszych wstawieniach
  TST(
      { d1.clear();d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));}, (d1.find(k2) != d1.end() ), (d2.find(k2) != d2.end() ))
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k3,v3));d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));}, (d1.find(k2) != d1.end() ), (d2.find(k2) != d2.end() ))

//  AXIOM("ListMap::Val { ListMap(); return operator[](ListMap::Key k) } == ListMap::Val()")
//  //W pustym ssowniku nie ma nic
//  TST(
//      { d1.clear();},d1[k1],ListMap::Val())

  AXIOM("ListMap::Val { unsafe_insert(ListMap::Key k, ListMap::Val v); return operator[](k) } == v")
  //Jesli ostatnio wstawiono, to wartosc
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1[k1],v1)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1[k1],v1)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));},d1[k1],v1)

  AXIOM("ListMap::Val { unsafe_insert(ListMap::Key k1, ListMap::Val v1); return operator[](ListMap::Key k2) } ==if (k1 != k2) { return operator[](k2) }")
  //Jesli ostatnio nie wstawiono, to
  //szukaj we wczesniejszych wstawieniach
  TST(
      { d1.clear();d2=d1;d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));}, d1[k2], d2[k2])
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d2=d1; d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));}, d1[k2], d2[k2])
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k3,v3));d2=d1; d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));}, d1[k2], d2[k2])

  AXIOM("ListMap { ListMap(); erase(ListMap::Key k) } == { ListMap() }")
  //W pustym delete nic nie skasuje
  TST(
      { d1.clear();d2=d1;d1.erase(k1);},d1,d2)

  AXIOM("ListMap { unsafe_insert(ListMap::Key k1, ListMap::Val v); erase(ListMap::Key k2) } ==if (k1 != k2) { delete(k2); unsafe_insert(k1,v) }")
  //Jesli ostatnio nie wstawiono, to
  //pozostawia w slowniku i
  //szuka we wczesniejszych wstawieniach
  TST(
      { d1.clear();d2=d1; d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));d1.erase(k2);d2.erase(k2);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2=d1; d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));d1.erase(k2);d2.erase(k2);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));},d1,d2)
  TST(
      { d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k2,v2));d2=d1; d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));d1.erase(k2);d2.erase(k2);d2.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v3));},d1,d2)

  AXIOM("ListMap { ~ListMap() } == { ListMap() }")
  //zniszczenie slownikow destruktorem odpowiada wyzerowaniu licznika wezlow
//  TST(
//      { d1.clear(); d2=d1;d1.clear();d1.insert(std::pair<ListMap::Key, ListMap::Val> (k1,v1));d2=d1; d1.clear(); d1[k1]=v1;d1[k2]=v2; d2[k3]=v3; d2[k2]=k3; d1.~TEST_MAP();d2.clear(); d2.~TEST_MAP();},CCount::getCount(),0)

  if (errors > 0)
  {
    std::cout << "LICZBA BLEDOW W ZESTAWACH TESTOWYCH: " << errors << "\n";
    return 0;
  }
  else
  {
    std::cout << "Nie wykryto bledow.\n";
    return 1;
  }
}

/// Testy u¿ytkownika
void test()
{
   int pts(0);
   std::string line(80, '-');
   std::cout << line << "Test 1:\n" << line;
   pts += test1();
   std::cout << line << "Test 2:\n" << line;
   pts += test2();
   std::cout << line << "Test 3:\n" << line;
   pts += test3();
   std::cout << line << ((pts == 3) ? "Masz moralnego plusa :)" : "Please try again :(");
   std::cout << "\nZaliczone testy: " << pts << "/3\n" << line;
}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /home/common/dyd/aisdi/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 2: wchodze do funkcji main." << std::endl;
//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}