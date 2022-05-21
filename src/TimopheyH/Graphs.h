#include <iostream>
#include <QString>
#include <QPair>
#include <QList>
#include <QSharedPointer>
#include <QStack>
#include <QQueue>

namespace graphs
{
/* реализация стэка */
class Stack
{
	struct Item
	{
		/* данный в ячейке */
		int data;
		/* указатель типа Item на следующий элемент */
		Item *next;
	};

	void push(Item **top, int d)
	{
	}

public:


};

void init();

/* 4.1. Неориентированные графы */
/* реализация в виде массива списка смежностей */
class Graph
{
public:
	/* создание графа с v вершинами без рёбер */
	Graph(int v);
	// Graph(In in); чтение графа из файла (реализовано в readGraph)
	~Graph() {};

	/* количество вершин графа */
	int vertices() const;
	/* количество ребер графа */
	int edges() const;
	void setEdges(int cnt);
	/* добавление в граф ребра v-w  */
	bool addEdge(QPair<int, int> edge, QString *error = nullptr);
	/* вершины смежные с v */
	QList<int> adjacentOfVertex(int v, QString *error = nullptr) const;
	/* строковое представление графа */
	QString toString();

private:
	/* количество вершин */
	int _vertices{ 0 };
	/* количество ребер */
	int _edges{ 0 };
	/* список списков смежных вершин */
	QList<QList<int>> _adjacent;
};

/* API обработки графов */
class SearchInGraph
{
public:
	/* поиск вершин,связанных с вершиной source (исходная вершина) */
	SearchInGraph(const Graph & graph, int source);
	~SearchInGraph() {};

	/* связана ли v с вершиной source */
	bool marked(int v);
	/* сколько вершин связано с вершиной source */
	int count();
};


/* листинг 4.1.3 поиск в глубину */
class DepthFirstSearch
{
public:
	/* поиск вершин, связанных с вершиной sourceVertex (исходная вершина) */
	DepthFirstSearch() {}; /* конструктор по умолчанию нужен при наследовании */
	DepthFirstSearch(const QSharedPointer<Graph> & graph, int sourceVertex);
	~DepthFirstSearch() {};

	/* */
	void init(const QSharedPointer<Graph> & graph, int sourceVertex);
	/* связана ли v с вершиной source */
	bool marked(int v);
	/* сколько вершин связано с вершиной source */
	int count() const;

	//private: //!!! приватные методы и переменные не могут быть наследованы
	/* Доступ к членам public открыт для всех. Доступ к членам private открыт только для других членов этого же класса */
	void dfs(const QSharedPointer<Graph> & graph, int vertex); /* посещение вершины и пометка ее как посещенной  */
	/* если использовать =0 то при вызове конструктора этого класса будет выдана ошибка компиляции
	'graphs::DepthFirstSearch': cannot instantiate abstract class. Здесь не получится использовать и базовый класс и наследуемый,
	в таких случаях следует следить за реализацией в наследуемом классе
	*/
	virtual void setEdgeTo(int w, int v)/* = 0*/;
	QList<bool> _marked;

	int _count{ 0 };
};

/* ================================= */
/* нахождение путей */
/* Алгоритм 4.1. Поиск в грубину для нахождения путей */
class DepthFirstPaths : public DepthFirstSearch
{
public:

	DepthFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex);
	~DepthFirstPaths() {};

	/* существует ли путь в графе из sourceVertex в 'v' */
	bool hasPathTo(int v, QString * error = nullptr);
	/* путь в графе из sourceVertex в 'v'; нулевой объект если не существует */
	QStack<int> pathTo(int v);
private:
	/* добавление последней вершины v на известном пути до данной вершины w */
	void setEdgeTo(int w, int v) override;
	/* исходная вершина */
	int _sourceVertex{ 0 };
	/* edgeTo[w] = v, ребро v-w это ребро, которое ВПЕРВЫЕ нас в вершину w, т.е. v-w последнее ребро на известном пути из s в w */
	QList<int>_edgeTo;
};

/* рис 4.1.19 API для реализации путей  */
class Paths
{
public:
	/* поиск путей в графе из источника sourceVertex */
	Paths(const QSharedPointer<Graph> & graph, int sourceVertex) {};
	~Paths() {};

	/* существует ли путь в графе из sourceVertex в 'v' */
	bool hasPathTo(int v) { return false; };

	/* путь в графе из sourceVertex в 'v'; нулевой объект если не существует */
	QStack<int> pathTo(int v) { return QStack<int>(); };
};


/* Алгоритм 4.2. Поиск в ширину для нахождения путей */
class BreadFirstPaths
{
	/* в ИДЕАЛЕ нужно переделать через виртуальные методы т.к. много методов дублируются */
public:
	BreadFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex);
	~BreadFirstPaths() {};

	void init(const QSharedPointer<Graph> & graph, int sourceVertex);
	/* существует ли путь в графе из sourceVertex в 'v' */
	bool hasPathTo(int v, QString * error = nullptr);
	/* путь в графе из sourceVertex в 'v'; нулевой объект если не существует */
	QStack<int> pathTo(int v);

private:
	/* добавление последней вершины v на известном пути до данной вершины w */
	bool setEdgeTo(int w, int v);
	int edgeTo(int w);
	bool setMarked(int w);
	bool marked(int w);
	/* breadth first search: поиск в глубину  */
	void bfs(const QSharedPointer<Graph> & graph, int vertex);

	/* известен ли кратчайший путь к этой вершине */
	QList<bool> _marked;
	/* Последняя вершина на известном пути к данной вершине.
	edgeTo[w] = v, ребро v-w это ребро, которое ВПЕРВЫЕ привело нас в вершину w,
	т.е. v-w последнее ребро на известном пути из s в w */
	QList<int>_edgeTo;
	/* исходная вершина */
	const int _sourceVertex;
};




class GraphProcess
{
public:
	/* обработка графа */
	GraphProcess();
	~GraphProcess() {};

	void run();

	void printPaths(const QSharedPointer<DepthFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex);
	void printPaths(const QSharedPointer<BreadFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex, const QList<QString> & names = QList<QString>());

private:
	/* рассчет степени вершины v для графа g (кол-во ребер примыкающих(смежных) к вершине) */
	int degree(const Graph & graph, int v);
	/* максимальная степень графа */
	int maxDegree(const Graph & graph);
	/* средняя степень графа */
	int avgDegree(const Graph & graph);
	/* подсчет петель */
	int numberOfSelfLoops(const Graph & graph);
	/* */
	QSharedPointer<Graph> _graph;
	QSharedPointer<DepthFirstPaths> _searchDfs;
	QSharedPointer<BreadFirstPaths> _searchBfs;

	bool readGraph(QString & pathToFile, QString * error = nullptr);

	QStringList _paths;
};

/* Символьные графы */
class SymbolGraph
{
public:
	/* создание графа на основе списка рёбер */
	SymbolGraph(const QList<QStringList> & edgesList);
	~SymbolGraph() {};
	/* присутствует ли вершина key */
	bool contains(const QString & key) { return _st.contains(key); };
	/* индекс, связанный с key */
	int index(const QString & key);
	/* ключ, связанный с индексом v */
	QString name(int v);
	/*  */
	QList<QString> keys() const { return _keys; };

	QSharedPointer<Graph> graph() { return _graph; };

private:
	/* строка -> индекс */
	QHash<QString, int> _st;
	/* индекс -> строка */
	QList<QString> _keys;
	/* граф */
	QSharedPointer<Graph> _graph;
};


class SymbolGraphProcess
{
public:
	/* обработка символьного графа */
	SymbolGraphProcess() {};
	~SymbolGraphProcess() {};

	void run();
	QList<QStringList> edgesList() { return _edgesList; };
private:
	void readGraph(const QString & pathToFile);
	QList<QStringList> _edgesList;
};


/* 4.2.1. Ориентированные графы (орграфы) */
class Digraph
{
public:
	/* создание орграфа с v вершинами без рёбер */
	Digraph(int v);
	// Digraph(In in); чтение орграфа из файла (НЕ реализовано в readGraph)
	~Digraph() {};

	/* количество вершин орграфа */
	int vertices() const;
	/* количество ребер орграфа */
	int edges() const;
	void setEdges(int cnt);
	/* добавление в орграф ребра v-w  */
	bool addEdge(QPair<int, int> edge, QString *error = nullptr);
	/* вершины смежные с v */
	QList<int> adjacentOfVertex(int v, QString *error = nullptr) const;
	/* строковое представление орграфа */
	QString toString();
	/* обращение орграфа */
	Digraph reverse();

private:
	/* количество вершин */
	int _vertices{ 0 };
	/* количество ребер */
	int _edges{ 0 };
	/* список списков смежных вершин */
	QList<QList<int>> _adjacent;
};


/* листинг 4.2.2 поиск в глубину. Достижимость в орграфах */
class DirectedDepthFirstSearch
{
public:
	DirectedDepthFirstSearch() {}; /* конструктор по умолчанию нужен при наследовании */
	/* поиск в орграфе вершин, достижимых из sources(источников) */
	DirectedDepthFirstSearch(const QSharedPointer<Digraph> & graph, QList<int> sources);

	~DirectedDepthFirstSearch() {};

	/* */
	void init(const QSharedPointer<Digraph> & graph, QList<int> sources);

	/* достижима ли вершина v */
	bool marked(int v);

	/* посещение вершины и пометка ее как посещенной  */
	void dfs(const QSharedPointer<Digraph> & graph, int vertex);

	QList<bool> _marked;
	int _gv{ 0 };

	void printReachableList();
};

/* листинг 4.2.3 */
class DirectedCycle
{
public:
	/* конструктор по умолчанию*/
	DirectedCycle() {};
	/* конструктор для поиска циклов */
	DirectedCycle(const QSharedPointer<Digraph> & graph);
	~DirectedCycle() {};

	/* содержит ли орграф ориентированный цикл */
	bool hasCycle() { return !_cycle.isEmpty(); };
	/* вершины цикла */
	QVector<int> cycle() { return _cycle; };

	/* ф-ии доступа */
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
	/* вершины цикла (если он есть) */
	QStack<int> _cycle;
	/* вершины в стеке рекурсивных вызовов */
	QList<bool> _onStack;
};

/* листинг 4.2.4 Упорядочение вершин в орграфе с помощью поиска в глубину */
class DirectedDepthFirstOrder
{
public:
	DirectedDepthFirstOrder() {};
	/*  */
	DirectedDepthFirstOrder(const QSharedPointer<Digraph> & graph);
	~DirectedDepthFirstOrder() {};

	/* ф-ии доступа */
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
	/* вершины в прямом порядке - порядок вызовов dfs */
	QQueue<int> _pre;
	/* вершины в обратном порядке - порядок обработки вершин */
	QQueue<int> _post;
	/* вершины в реверсном порядке */
	QStack<int> _reversePost;
};


class DigraphProcess
{
public:
	/* обработка орграфа */
	DigraphProcess();
	~DigraphProcess() {};

	void run();

private:
	QSharedPointer<Digraph> _diGraph;
	QSharedPointer<DirectedDepthFirstSearch> _diDfs;

	bool readGraph(QString & pathToFile, QString * error = nullptr);

	QStringList _paths;
};

// что за хрень, почему не дает использовать GraphPtr в printPaths и других местах
//using GraphPtr = const QSharedPointer<Graph>;

} //namespace graphs