#include <iostream>
#include <QString>
#include <QPair>
#include <QList>
#include <QSharedPointer>
#include <QStack>
#include <QQueue>

namespace graphs
{
/* ���������� ����� */
class Stack
{
	struct Item
	{
		/* ������ � ������ */
		int data;
		/* ��������� ���� Item �� ��������� ������� */
		Item *next;
	};

	void push(Item **top, int d)
	{
	}

public:


};

void init();

/* 4.1. ����������������� ����� */
/* ���������� � ���� ������� ������ ���������� */
class Graph
{
public:
	/* �������� ����� � v ��������� ��� ���� */
	Graph(int v);
	// Graph(In in); ������ ����� �� ����� (����������� � readGraph)
	~Graph() {};

	/* ���������� ������ ����� */
	int vertices() const;
	/* ���������� ����� ����� */
	int edges() const;
	void setEdges(int cnt);
	/* ���������� � ���� ����� v-w  */
	bool addEdge(QPair<int, int> edge, QString *error = nullptr);
	/* ������� ������� � v */
	QList<int> adjacentOfVertex(int v, QString *error = nullptr) const;
	/* ��������� ������������� ����� */
	QString toString();

private:
	/* ���������� ������ */
	int _vertices{ 0 };
	/* ���������� ����� */
	int _edges{ 0 };
	/* ������ ������� ������� ������ */
	QList<QList<int>> _adjacent;
};

/* API ��������� ������ */
class SearchInGraph
{
public:
	/* ����� ������,��������� � �������� source (�������� �������) */
	SearchInGraph(const Graph & graph, int source);
	~SearchInGraph() {};

	/* ������� �� v � �������� source */
	bool marked(int v);
	/* ������� ������ ������� � �������� source */
	int count();
};


/* ������� 4.1.3 ����� � ������� */
class DepthFirstSearch
{
public:
	/* ����� ������, ��������� � �������� sourceVertex (�������� �������) */
	DepthFirstSearch() {}; /* ����������� �� ��������� ����� ��� ������������ */
	DepthFirstSearch(const QSharedPointer<Graph> & graph, int sourceVertex);
	~DepthFirstSearch() {};

	/* */
	void init(const QSharedPointer<Graph> & graph, int sourceVertex);
	/* ������� �� v � �������� source */
	bool marked(int v);
	/* ������� ������ ������� � �������� source */
	int count() const;

	//private: //!!! ��������� ������ � ���������� �� ����� ���� �����������
	/* ������ � ������ public ������ ��� ����. ������ � ������ private ������ ������ ��� ������ ������ ����� �� ������ */
	void dfs(const QSharedPointer<Graph> & graph, int vertex); /* ��������� ������� � ������� �� ��� ����������  */
	/* ���� ������������ =0 �� ��� ������ ������������ ����� ������ ����� ������ ������ ����������
	'graphs::DepthFirstSearch': cannot instantiate abstract class. ����� �� ��������� ������������ � ������� ����� � �����������,
	� ����� ������� ������� ������� �� ����������� � ����������� ������
	*/
	virtual void setEdgeTo(int w, int v)/* = 0*/;
	QList<bool> _marked;

	int _count{ 0 };
};

/* ================================= */
/* ���������� ����� */
/* �������� 4.1. ����� � ������� ��� ���������� ����� */
class DepthFirstPaths : public DepthFirstSearch
{
public:

	DepthFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex);
	~DepthFirstPaths() {};

	/* ���������� �� ���� � ����� �� sourceVertex � 'v' */
	bool hasPathTo(int v, QString * error = nullptr);
	/* ���� � ����� �� sourceVertex � 'v'; ������� ������ ���� �� ���������� */
	QStack<int> pathTo(int v);
private:
	/* ���������� ��������� ������� v �� ��������� ���� �� ������ ������� w */
	void setEdgeTo(int w, int v) override;
	/* �������� ������� */
	int _sourceVertex{ 0 };
	/* edgeTo[w] = v, ����� v-w ��� �����, ������� ������� ��� � ������� w, �.�. v-w ��������� ����� �� ��������� ���� �� s � w */
	QList<int>_edgeTo;
};

/* ��� 4.1.19 API ��� ���������� �����  */
class Paths
{
public:
	/* ����� ����� � ����� �� ��������� sourceVertex */
	Paths(const QSharedPointer<Graph> & graph, int sourceVertex) {};
	~Paths() {};

	/* ���������� �� ���� � ����� �� sourceVertex � 'v' */
	bool hasPathTo(int v) { return false; };

	/* ���� � ����� �� sourceVertex � 'v'; ������� ������ ���� �� ���������� */
	QStack<int> pathTo(int v) { return QStack<int>(); };
};


/* �������� 4.2. ����� � ������ ��� ���������� ����� */
class BreadFirstPaths
{
	/* � ������ ����� ���������� ����� ����������� ������ �.�. ����� ������� ����������� */
public:
	BreadFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex);
	~BreadFirstPaths() {};

	void init(const QSharedPointer<Graph> & graph, int sourceVertex);
	/* ���������� �� ���� � ����� �� sourceVertex � 'v' */
	bool hasPathTo(int v, QString * error = nullptr);
	/* ���� � ����� �� sourceVertex � 'v'; ������� ������ ���� �� ���������� */
	QStack<int> pathTo(int v);

private:
	/* ���������� ��������� ������� v �� ��������� ���� �� ������ ������� w */
	bool setEdgeTo(int w, int v);
	int edgeTo(int w);
	bool setMarked(int w);
	bool marked(int w);
	/* breadth first search: ����� � �������  */
	void bfs(const QSharedPointer<Graph> & graph, int vertex);

	/* �������� �� ���������� ���� � ���� ������� */
	QList<bool> _marked;
	/* ��������� ������� �� ��������� ���� � ������ �������.
	edgeTo[w] = v, ����� v-w ��� �����, ������� ������� ������� ��� � ������� w,
	�.�. v-w ��������� ����� �� ��������� ���� �� s � w */
	QList<int>_edgeTo;
	/* �������� ������� */
	const int _sourceVertex;
};




class GraphProcess
{
public:
	/* ��������� ����� */
	GraphProcess();
	~GraphProcess() {};

	void run();

	void printPaths(const QSharedPointer<DepthFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex);
	void printPaths(const QSharedPointer<BreadFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex, const QList<QString> & names = QList<QString>());

private:
	/* ������� ������� ������� v ��� ����� g (���-�� ����� �����������(�������) � �������) */
	int degree(const Graph & graph, int v);
	/* ������������ ������� ����� */
	int maxDegree(const Graph & graph);
	/* ������� ������� ����� */
	int avgDegree(const Graph & graph);
	/* ������� ������ */
	int numberOfSelfLoops(const Graph & graph);
	/* */
	QSharedPointer<Graph> _graph;
	QSharedPointer<DepthFirstPaths> _searchDfs;
	QSharedPointer<BreadFirstPaths> _searchBfs;

	bool readGraph(QString & pathToFile, QString * error = nullptr);

	QStringList _paths;
};

/* ���������� ����� */
class SymbolGraph
{
public:
	/* �������� ����� �� ������ ������ ���� */
	SymbolGraph(const QList<QStringList> & edgesList);
	~SymbolGraph() {};
	/* ������������ �� ������� key */
	bool contains(const QString & key) { return _st.contains(key); };
	/* ������, ��������� � key */
	int index(const QString & key);
	/* ����, ��������� � �������� v */
	QString name(int v);
	/*  */
	QList<QString> keys() const { return _keys; };

	QSharedPointer<Graph> graph() { return _graph; };

private:
	/* ������ -> ������ */
	QHash<QString, int> _st;
	/* ������ -> ������ */
	QList<QString> _keys;
	/* ���� */
	QSharedPointer<Graph> _graph;
};


class SymbolGraphProcess
{
public:
	/* ��������� ����������� ����� */
	SymbolGraphProcess() {};
	~SymbolGraphProcess() {};

	void run();
	QList<QStringList> edgesList() { return _edgesList; };
private:
	void readGraph(const QString & pathToFile);
	QList<QStringList> _edgesList;
};


/* 4.2.1. ��������������� ����� (�������) */
class Digraph
{
public:
	/* �������� ������� � v ��������� ��� ���� */
	Digraph(int v);
	// Digraph(In in); ������ ������� �� ����� (�� ����������� � readGraph)
	~Digraph() {};

	/* ���������� ������ ������� */
	int vertices() const;
	/* ���������� ����� ������� */
	int edges() const;
	void setEdges(int cnt);
	/* ���������� � ������ ����� v-w  */
	bool addEdge(QPair<int, int> edge, QString *error = nullptr);
	/* ������� ������� � v */
	QList<int> adjacentOfVertex(int v, QString *error = nullptr) const;
	/* ��������� ������������� ������� */
	QString toString();
	/* ��������� ������� */
	Digraph reverse();

private:
	/* ���������� ������ */
	int _vertices{ 0 };
	/* ���������� ����� */
	int _edges{ 0 };
	/* ������ ������� ������� ������ */
	QList<QList<int>> _adjacent;
};


/* ������� 4.2.2 ����� � �������. ������������ � �������� */
class DirectedDepthFirstSearch
{
public:
	DirectedDepthFirstSearch() {}; /* ����������� �� ��������� ����� ��� ������������ */
	/* ����� � ������� ������, ���������� �� sources(����������) */
	DirectedDepthFirstSearch(const QSharedPointer<Digraph> & graph, QList<int> sources);

	~DirectedDepthFirstSearch() {};

	/* */
	void init(const QSharedPointer<Digraph> & graph, QList<int> sources);

	/* ��������� �� ������� v */
	bool marked(int v);

	/* ��������� ������� � ������� �� ��� ����������  */
	void dfs(const QSharedPointer<Digraph> & graph, int vertex);

	QList<bool> _marked;
	int _gv{ 0 };

	void printReachableList();
};

/* ������� 4.2.3 */
class DirectedCycle
{
public:
	/* ����������� �� ���������*/
	DirectedCycle() {};
	/* ����������� ��� ������ ������ */
	DirectedCycle(const QSharedPointer<Digraph> & graph);
	~DirectedCycle() {};

	/* �������� �� ������ ��������������� ���� */
	bool hasCycle() { return !_cycle.isEmpty(); };
	/* ������� ����� */
	QVector<int> cycle() { return _cycle; };

	/* �-�� ������� */
	bool marked(int v) { return v < _marked.size() ? _marked[v] : false; }
	void setMarked(int v, bool marked) { if (v < _marked.size()) { _marked[v] = marked; } }
	bool onStack(int v) { return v < _onStack.size() ? _onStack[v] : false; }
	void setOnStack(int v, bool onStack) { if (v < _onStack.size()) { _onStack[v] = onStack; } }
	int edgeTo(int v) { return v < _edgeTo.size() ? _edgeTo[v] : -1; }
	void setEdgeTo(int v, int edgeTo) { if (v < _edgeTo.size()) { _edgeTo[v] = edgeTo; } }

	void printCycle() const;
private:
	void init(const QSharedPointer<Digraph> & graph);
	void dfs(const QSharedPointer<Digraph> & graph, int v);
	QList<bool> _marked;
	QList<int> _edgeTo;
	/* ������� ����� (���� �� ����) */
	QStack<int> _cycle;
	/* ������� � ����� ����������� ������� */
	QList<bool> _onStack;
};

/* ������� 4.2.4 ������������ ������ � ������� � ������� ������ � ������� */
class DirectedDepthFirstOrder
{
public:
	DirectedDepthFirstOrder() {};
	/*  */
	DirectedDepthFirstOrder(const QSharedPointer<Digraph> & graph);
	~DirectedDepthFirstOrder() {};

	/* �-�� ������� */
	QList<int> pre() const { return _pre; };
	QList<int> post() const { return _post; };
	QStack<int> reversePost() const { return _reversePost; };
	bool marked(int v) { return v < _marked.size() ? _marked[v] : false; }
	void setMarked(int v, bool marked) { if (v < _marked.size()) { _marked[v] = marked; } }

	void print();
private:
	void init(const QSharedPointer<Digraph> & graph);
	void dfs(const QSharedPointer<Digraph> & graph, int v);
	QList<bool> _marked;
	/* ������� � ������ ������� - ������� ������� dfs */
	QQueue<int> _pre;
	/* ������� � �������� ������� - ������� ��������� ������ */
	QQueue<int> _post;
	/* ������� � ��������� ������� */
	QStack<int> _reversePost;
};


class DigraphProcess
{
public:
	/* ��������� ������� */
	DigraphProcess();
	~DigraphProcess() {};

	void run();

private:
	QSharedPointer<Digraph> _diGraph;
	QSharedPointer<DirectedDepthFirstSearch> _diDfs;

	bool readGraph(QString & pathToFile, QString * error = nullptr);

	QStringList _paths;
};

// ��� �� �����, ������ �� ���� ������������ GraphPtr � printPaths � ������ ������
//using GraphPtr = const QSharedPointer<Graph>;

} //namespace graphs