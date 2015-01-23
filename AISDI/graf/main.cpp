#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <queue>

using namespace std;

class Graph
{
public:	
	friend class Vertex;
	
	struct Edge
	{
		unsigned endV;	//koniec krawedzi
		double weight;	//waga krawedzi
		
		Edge(unsigned end, double w)
		{
			endV = end;
			weight = w;
		}	
	};
	
	class Vertex
	{
		private:
			//wspolrzedne
			double x_cord;
			double y_cord;
			
			//krawedzie
			vector<Edge> edges;

			//numer wierzcholka
			unsigned index;

			//czy zostal odwiedzony
			bool visited;

		public:
			
			Vertex(double x, double y, unsigned idx) :
			x_cord(x), y_cord(y), index(idx), visited(false) {} 
			
					
			// Dodaje krawedz
			void pushEdge(Edge e) 
			{
				vector<Edge>::iterator it;
				// Ignoruj krawedzie same na siebie	
				if (e.endV == index)
					return;
				// Jesli krawedz juz istnieje: nadpisz
				for (it = edges.begin(); it != edges.end() && it->endV != index; it++);
				if (it == edges.end())
					edges.push_back(e);
				else
					it->weight = e.weight;
				return;
			}

			bool getVisited()
			{
				return visited;
			}

			void setVisited(bool vis)
			{
				this->visited = vis;
			}

			unsigned getId()
			{
				return this->index;
			}

			vector<Edge>& getEdges()
			{
    				return edges;
			}
			
	};	//Vertex

private:
	// wierzcholki grafu
	vector<Vertex> vtx;
public:
	Vertex& getVertex(unsigned id) 
	{
		if (id >= vtx.size())
			throw "getVertex: There is no such index!";
		return vtx.at(id);
	}

	void pushVertex(double x, double y) 
	{
		vtx.push_back(Vertex(x, y, vtx.size() ));
	}

private:
    ///graf transponowany
    vector<Vertex> tVtx;

    ///Krok rekurencyjny do Kosaraju
    void recKosaraju(Vertex& vertex)
    {
    	if(vertex.getVisited())
    	{
		//juz odwiedzony
    	    return;
    	}
    	vertex.setVisited(true);	//odwiedzilismy wiec ustawiamy na true
    	for(Edge edge : vertex.getEdges())
    	{
    	    recKosaraju(getVertex(edge.endV));
    	}
    
	kosarajuStack.push(vertex.getId());
    }

	queue<int> nieparzyste; //wrzucamy tutaj dane i jezeli nieparzysta ilosc to wypiszemy
    ///Krok rekursyjny dla grafu transponowanego, zwraca, czy znalazł jakąś składową
    bool tRecKosaraju(Vertex& vertex)
    {
	    if(vertex.getVisited())
	    {
	        return false;
	    }
	    vertex.setVisited(true);
	    for(Edge edge : vertex.getEdges())
	    {
	        tRecKosaraju(gettranspVertex(edge.endV));
	    }
	
	    nieparzyste.push(vertex.getId()); //wrzucamy id wierzcholka do kolejki ktora pozniej wypiszemy    
     	    return true;
    }

    stack<int> kosarajuStack; //stos do Kosaraju

    Vertex& getVertex(int id)	//zwraca wierzcholek
    {
	return this->vtx.at(id);
    }

    Vertex& gettranspVertex(int id)	//zwraca wierzcholek z transponowanego grafu
    {
	return this->tVtx.at(id);
    }

public:
void Kosaraju()
{
    //ustaw wszystkie wierzchołki na nieodwiedzone
    for(Vertex vert : vtx)
    {
        vert.setVisited(false);
    }
    //wykonuj dla każdego nieodwiedzonego
    int vertSize = vtx.size();
    for(int i = 0; i < vertSize; i++)
    {
        //pętla liczy tablicę, getVertex potrzebuje numeru wierzchołka (od 1), tak jest bezpieczniej
        recKosaraju(getVertex(i));
    }
    //ustaw wszystkie wierzchołki grafu transponowanego na nieodwiedzone
    for(Vertex vert : tVtx)
    {
        vert.setVisited(false);
    }
    while(!kosarajuStack.empty())
    {
        int vertId = kosarajuStack.top();        
	kosarajuStack.pop();
        if(tRecKosaraju(gettranspVertex(vertId)))
	{
		if(nieparzyste.size() & 1) 	//modulo 2
		{
			while(!(nieparzyste.empty()))
			{
				int id = nieparzyste.front();
				nieparzyste.pop();
				cout << id << " ";
			}
			cout << endl; // oddzielamy kolejne skladowe
		}
		else	//jesli jest parzysta liczba wierzcholkow to czyscimy kolejke
		{
			while(!(nieparzyste.empty()))
			{
				nieparzyste.pop();
			}
		}
	}
    }
}

    void addVertex(double x, double y, int id)
    {
	Vertex v(x,y,id);
    	this->vtx.push_back(v);
    	this->tVtx.push_back(v);
    }

    	void addEdge(int from, int to, double w)
    	{
    		Edge edge(to, w);
    		Edge tEdge(from, w);
    		getVertex(from).pushEdge(edge);
    		gettranspVertex(to).pushEdge(tEdge);
    	}

};


int main()
{
	unsigned vertex_count = 0;
	Graph graph;
	
	while (!cin.eof())
	{
		string tmp, l1, l2, l3;
		string::iterator it;
		getline(cin, tmp);
		if (tmp.empty())
			continue;
		it = tmp.begin();
		while (*it != ' ')
		{
			l1.push_back(*it);
			++it;
		}
		++it;
		while (it != tmp.end() && *it != ' ')
		{
			l2.push_back(*it);
			++it;
		}

		if (it != tmp.end())
		{
			++it;
			while (it != tmp.end())
			{
				l3.push_back(*it);
				++it;
			}
		}

		if (l3.empty())
		{
            		graph.addVertex(stod(l1), stod(l2), vertex_count);
			++vertex_count;
		}
		else
		{
            		graph.addEdge(stoi(l1), stoi(l2), stod(l3));
		}
	}
	
	if(vertex_count)
	{
		graph.Kosaraju();
	}
	return 0;
}
