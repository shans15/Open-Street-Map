// graph.h
// Sarthak Hans
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.


#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>

using namespace std;

template <typename VertexT, typename WeightT>
class graph
{
private:
	map<VertexT, map<VertexT, WeightT>> adjList;

	//
	// _LookupVertex
	//
	// Finds the vertex in the Vertices vector and returns it's
	// index position if found, otherwise returns -1.
	//
	int _LookupVertex(VertexT v) const
	{
		return adjList.count(v) > 0;
	}

public:
	graph()
	{
		return;
	}

	//
	// NumVertices
	//
	// Returns the # of vertices currently in the graph.
	//
	int NumVertices() const
	{
		return adjList.size();
	}

	//
	// NumEdges
	//
	// Returns the # of edges currently in the graph.
	//
	int NumEdges() const
	{
		int count = 0;
		for (auto const &vertex : adjList)
		{
			count += vertex.second.size();
		}
		return count;
	}

	//
	// addVertex
	//
	// Adds the vertex v to the graph if there's room, and if so
	// returns true.  If the graph is full, or the vertex already
	// exists in the graph, then false is returned.
	//
	bool addVertex(VertexT v)
	{
		if (_LookupVertex(v))
		{
			return false;
		}
		adjList[v] = map<VertexT, WeightT>();
		return true;
	}

	//
	// addEdge
	//
	// Adds the edge (from, to, weight) to the graph, and returns
	// true.  If the vertices do not exist or for some reason the
	// graph is full, false is returned.
	//
	// NOTE: if the edge already exists, the existing edge weight
	// is overwritten with the new edge weight.
	//
	bool addEdge(VertexT from, VertexT to, WeightT weight)
	{
		if (!_LookupVertex(from) || !_LookupVertex(to))
		{
			return false;
		}
		adjList[from][to] = weight;
		return true;
	}

	//
	// getWeight
	//
	// Returns the weight associated with a given edge.  If
	// the edge exists, the weight is returned via the reference
	// parameter and true is returned.  If the edge does not
	// exist, the weight parameter is unchanged and false is
	// returned.
	//
	bool getWeight(VertexT from, VertexT to, WeightT &weight) const
	{
		if (!_LookupVertex(from) || !_LookupVertex(to))
		{
			return false;
		}
		bool exists = false;
		map<VertexT, WeightT> edges = adjList.at(from);
		for (auto const &e : edges)
		{
			if (e.first == to)
			{
				weight = e.second;
				exists = true;
			}
		}
		return exists;
	}

	//
	// neighbors
	//
	// Returns a set containing the neighbors of v, i.e. all
	// vertices that can be reached from v along one edge.
	// Since a set is returned, the neighbors are returned in
	// sorted order; use foreach to iterate through the set.
	//
	set<VertexT> neighbors(VertexT v) const
	{
		set<VertexT> set;
		if (!_LookupVertex(v))
		{
			return set;
		}
		map<VertexT, WeightT> edges = adjList.at(v);
		for (auto const &e : edges)
		{
			set.insert(e.first);
		}
		return set;
	}

	//
	// getVertices
	//
	// Returns a vector containing all the vertices currently in
	// the graph.
	//
	vector<VertexT> getVertices() const
	{
		vector<VertexT> vertices;
		for (auto const &vert : adjList)
		{
			vertices.push_back(vert.first);
		}
		return vertices;
	}

	//
	// dump
	//
	// Dumps the internal state of the graph for debugging purposes.
	//
	// Example:
	//    graph<string,int>  G(26);
	//    ...
	//    G.dump(cout);  // dump to console
	//
	void dump(ostream &output) const
	{
		output << "***************************************************" << endl;
		output << "********************* GRAPH ***********************" << endl;

		output << "**Num vertices: " << this->NumVertices() << endl;
		output << "**Num edges: " << this->NumEdges() << endl;

		output << endl;
		output << "**Vertices:" << endl;
		int numV = 0;
		for (auto &v : adjList)
		{
			output << " " << numV << ". " << v.first << endl;
			numV++;
		}

		output << endl;
		output << "**Edges:" << endl;
		for (auto &v : adjList)
		{
			for (auto &e : v.second)
			{
				output << " (" << v.first << "," << e.first << "," << e.second << ")";
			}
			output << endl;
		}
		output << "**************************************************" << endl;
	}
};