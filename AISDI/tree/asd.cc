/** 
@file asd.cc

Plik do modyfikacji w w ramach cwiczenia 4 z AISDI.
Zawiera niekompletne implementacje metod klasy TreeMap.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY TreeMap.
    
@author
Pawel Cichocki, Michal Nowacki

@date  
last revision
- 2005.12.01 Pawel Cichocki: TreeNodeDetail class
- 2005.12.01 Michal Nowacki: lab #4
- 2005.11.17 Michal Nowacki: lab #3, copy operator and constructor
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

#ifdef _SUNOS
#include "/materialy/AISDI/tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

/// A helper class.
class TreeMapDetail //Helper
{
protected:
   friend class TreeMap;
   friend class TreeMap::iterator;
   friend class TreeMap::const_iterator;

   int size(TreeNode* n)      //liczymy size rekurencyjnie
   {
      int i = 0;
      if(n->right)      //jesli istnieje prawa galaz to dodaj liczbe elementow tej podgalezi
        i += size(n->right);
      if(n->left)       //jesli istnieje lewa galaz to dodaj liczbe elementow tej podgalezi
         i += size(n->left);
      return ++i;
   }

   void copy(TreeNode* source, TreeMap* target)       //kopiujemy drzewko rekurencyjnie
   {
      target->insert(source->data);
      if(source->left)
         copy(source->left, target);
      if(source->right)
         copy(source->right, target);
   }

   void is_equal(TreeNode* first, TreeNode* another, bool &equal)    //sprawdzamy czy rowne strukturalnie rekurencyjnie
   {
      if ((first == NULL) && (another == NULL))
         return;

      if (first == NULL || another == NULL || first->data.first != another->data.first || first->data.second != another->data.second)
      {  // jesli nie spelnia zadnego warunku to false
         equal = false;
         return;
      }

      is_equal(first->left, another->left, equal);
      is_equal(first->right, another->right, equal);
   }

   void clearMap(TreeNode* temp)
   {
      if(temp->right) clearMap(temp->right);
      if(temp->left) clearMap(temp->left);
      delete temp;
   }

};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap()
{
   root = new TreeNode(std::make_pair(0, "\0"), NULL, NULL, NULL);
   detail = new TreeMapDetail();
};

/// Content of existing TreeMap object is copied into the new object. 
TreeMap::TreeMap( const TreeMap& m )
{
   root = new TreeNode(std::make_pair(0, "\0"), NULL, NULL, NULL);
   detail = new TreeMapDetail();
   detail->copy(m.root->left, this);
};

TreeMap::~TreeMap()
{
   clear();
   delete root;
};

// Inserts an element into the map.
// @returns A pair whose bool component is true if an insertion was
//          made and false if the map already contained an element
//          associated with that key, and whose iterator component coresponds to
//          the address where a new element was inserted or where the element
//          was already located.
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<Key, Val>& entry)
{
   iterator found = find(entry.first);       //szukamy czy juz istnieje

   if(found == end())                     //jesli nie istnieje to wstaw
      return std::make_pair<TreeMap::iterator, bool>(unsafe_insert(entry), true);
   else
      return std::make_pair<TreeMap::iterator, bool>(found, false);
}

// Inserts an element into the map.
// This method assumes there is no value asociated with
// such a key in the map.

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
   TreeNode* temp = root->left;        //pierwszy element

   while(temp)
   {
      if (entry.first < temp->data.first)     //jezeli wstawiamy z lewej
      {
         if (temp->left == NULL)  //tutaj wstawiamy
         {
            temp->left = new TreeNode(entry, temp, NULL, NULL);
            return iterator(temp->left);
         }
         temp = temp->left;
         continue;
      }

      if (entry.first > temp->data.first) //wstawiamy z prawej
      {
         if (temp->right == NULL)       //wstawiamy
         {
            temp->right = new TreeNode(entry, temp, NULL, NULL);
            return iterator(temp->right);
         }
         temp = temp->right;  //kolejny obieg petli
      }
   }
   //wstawiamy na poczatek
   root->left = new TreeNode(entry, root, NULL, NULL);
   return iterator(root->left);
}

// Returns an iterator addressing the location of the entry in the map
// that has a key equivalent to the specified one or the location succeeding the
// last element in the map if there is no match for the key.
TreeMap::iterator TreeMap::find(const Key& k)
{
   if(empty())
      return end();     //jezeli puste drzewo to nie szukaj

   TreeNode* temp = root->left;
   while(temp)
   {
      if (k == temp->data.first) return iterator(temp);
      else if (k < temp->data.first) temp = temp->left;
      else temp = temp->right;
   }

   return end();     //jesli nie znalezlismy

}

TreeMap::const_iterator TreeMap::find(const Key& k) const
{
   if(empty())
      return end();     //jezeli puste drzewo to nie szukaj

   TreeNode* temp = root->left;
   while(temp)
   {
      if (k == temp->data.first) return const_iterator(temp);
      else if (k < temp->data.first) temp = temp->left;
      else temp = temp->right;
   }
   return end();     //jesli nie znalezlismy
}

// Inserts an element into a map with a specified key value
// if one with such a key value does not exist.
// @returns Reference to the value component of the element defined by the key.
TreeMap::Val& TreeMap::operator[](const Key& k)
{
   return insert(std::make_pair(k, "\0")).first->second;
}

// Tests if a map is empty.
bool TreeMap::empty( ) const
{
   return (root->left == NULL);
}

// Returns the number of elements in the map.
TreeMap::size_type TreeMap::size( ) const
{
   if(empty())
      return 0;

   return detail->size(root->left);
}

// Returns the number of elements in a map whose key matches a parameter-specified key.
TreeMap::size_type TreeMap::count(const Key& _Key) const
{
   if(find(_Key) != end())       //jesli znajdziemy klucz (jesli end() to znaczy ze nie znalezlismy)
      return 1;  // this is not a multimap

   return 0;
}

// Removes an element from the map.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator i)
{
   TreeNode* temp = i.node;

   if(temp->left == NULL)   //wezel ma jedno lub zero dzieci
   {
      if(temp->parent->left == temp)      //jezeli temp jest lewym dzieckiem to podczep pod lewy rodzica
         temp->parent->left = temp->right;
      else
         temp->parent->right = temp->right;  //w innym przypadku pod prawy
   }
   else //jedno dziecko
      if (temp->right == NULL)
      {
         if (temp->parent->left == temp)
             temp->parent->left = temp->left;
         else
             temp->parent->right = temp->left;
      }
      else     //wezel ma dwojke dzieci
   {
      //musimy przestawic najmniejszy element w prawym poddrzewie, wiec go szukamy
      TreeNode *min_right = temp->right;
      while(min_right->left)
         min_right = min_right->left;

      temp->data = min_right->data;     //jak znajdziemy to przepisujemy wartosci

      if(min_right->parent->left == min_right)         //ustawiamy prawidlowo wskazniki
         min_right->parent->left = min_right->right;
      else
         min_right->parent->right = min_right->right;

      delete min_right;
      return ++i;
   }

   delete temp;
   return ++i;
}

// Removes a range of elements from the map.
// The range is defined by the key values of the first and last iterators
// first is the first element removed and last is the element just beyond the last elemnt removed.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l)
{
   if(f == end())
      return f;

   while(f!=l)
   {
      erase(f++);
   }
   return l;
}

// Removes an element from the map.
// @returns The number of elements that have been removed from the map.
//          Since this is not a multimap itshould be 1 or 0.
TreeMap::size_type TreeMap::erase(const Key& key)
{
   TreeNode *temp = root->left;     //poczatek
   iterator it = find(key);
   if(it != end())      //jesli nie pokazuje na koniec to znaczy ze znalezlismy
   {
      erase(it);
      return 1;
   }
   return 0;
}

// Erases all the elements of a map.
void TreeMap::clear( )
{
   if(!empty())
      detail->clearMap(root->left);
}

bool TreeMap::struct_eq(const TreeMap& another) const
{
   if(empty() && another.empty()) return true;     //jesli obie sa puste to OK
   if(empty() || another.empty()) return false;    //jesli jedna jest pusta to false

   if(size() != another.size()) return false;      //rozne rozmiary to false

   bool equal = true;

   detail->is_equal(root->left, another.root->left, equal);
   return equal;
}

bool TreeMap::info_eq(const TreeMap& another) const
{
   if(empty() && another.empty()) return true;     //jesli obie sa puste to OK
   if(empty() || another.empty()) return false;    //jesli jedna jest pusta to false

   if(size() != another.size()) return false;      //rozne rozmiary to false

   for(iterator it = begin(); it != end(); it++)
   {
      if(another.find(it->first) == another.end()) return false;
   }
   return true;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator++()
{
   if(!node->parent) return *this;       //jesli koniec

   if(node->right)
   {                     //jesli nie jestesmy w lisciu
      node = node->right;
      while(node->left) node = node->left;
      return *this;
   }

   if(node->parent->left == node)        //jesli jestesmy w lewym lisciu
      node = node->parent;
   else
   {                                //jesli jestesmy w prawym lisciu
      while(node->parent->right == node) node = node->parent;
      node = node->parent;
   }

   return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int)
{
   if(!node->parent) return *this;       //jesli koniec

   TreeNode *temp = node;
   if(node->right)
   {                     //jesli nie jestesmy w lisciu
      node = node->right;
      while(node->left) node = node->left;
      return temp;
   }

   if(node->parent->left == node)        //jesli jestesmy w lewym lisciu
      node = node->parent;
   else
   {                                //jesli jestesmy w prawym lisciu
      while(node->parent->right == node) node = node->parent;
      node = node->parent;
   }

   return temp;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--()
{
   if(node->left)
   {
      node = node->left;
      while(node->right) node = node->right;
      return *this;
   }

   if(node->parent->right == node)       //jesli jestesmy w prawym lisciu
      node = node->parent;
   else
   {                                //jesli jestesmy w lewym lisciu
      while(node->parent->left == node) node = node->parent;
      node = node->parent;
   }

   return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int)
{
   TreeNode* temp = node;

   if(node->left)
   {
      node = node->left;
      while(node->right) node = node->right;
      return temp;
   }

   if(node->parent->right == node)       //jesli jestesmy w prawym lisciu
      node = node->parent;
   else
   {                                //jesli jestesmy w lewym lisciu
      while(node->parent->left == node) node = node->parent;
      node = node->parent;
   }

   return temp;
}


/// Assignment operator copy the source elements into this object.
TreeMap& TreeMap::operator=(const TreeMap& other)
{
   if(root == other.root) return *this;
   clear();
   detail->copy(other.root->left, this);
   return *this;
}
      
/// Returns an iterator addressing the first element in the map
TreeMap::iterator TreeMap::begin()
{ 
   if(empty()) return iterator(root);

   TreeNode* temp = root->left;

   while(temp->left) temp = temp->left;

   return iterator(temp);
}

TreeMap::const_iterator TreeMap::begin() const
{
   if(empty()) return const_iterator(root);

   TreeNode* temp = root->left;

   while(temp->left) temp = temp->left;

   return const_iterator(temp);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::iterator TreeMap::end()
{
   return iterator(root);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::const_iterator TreeMap::end() const
{ 
   return const_iterator(root);
}
//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print(const std::pair<int, std::string>& p)
{
   std::cout <<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// The big mean test function ;)
void test()
{
   // A typedef used by the test.
   typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   //typedef TreeMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;  
   
   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";

   for_each(m.begin(), m.end(), print );
   //system("PAUSE");

}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /materialy/AISDI/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 4: wchodze do funkcji main." << std::endl;

//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}
