#include <Graphs.h>

#include <QDebug>
#include <QFile>
#include <QDir>

namespace graphs
{

const QString SEPARATOR{ "===============================================" };
const QString SEPARATOR_MINI{ "===================" };

void init()
{
	//graphs::GraphProcess().run();
	//graphs::SymbolGraphProcess().run();
	graphs::DigraphProcess().run();
}

/* 4.1. ����������������� ����� */
/* �������� ����� � v ��������� ��� ���� */
Graph::Graph(int v) : _vertices(v), _edges(0)
{
	for (int i = 0; i < v; i++)
	{
		_adjacent.append(QList<int>());
	}
}

int Graph::vertices() const
{
	return _vertices;
}



int Graph::edges() const
{
	return _edges;
}

void Graph::setEdges(int cnt)
{
	_edges = cnt;
}



bool Graph::addEdge(QPair<int, int> edge, QString *error)
{
	auto v = edge.first;
	auto w = edge.second;

	if (v >= _adjacent.size() || w >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertices(%1,%2) for edge").arg(v).arg(w);
		return false;
	}
	/*
		������ ����� ������������ ������:
		���� ��� ��������� ������� 'v' � 'w', �� 'w' ������������ � ������ ������ 'v'
		� 'v' ������������ � ������ ������ 'w'
	*/
	_adjacent[v].prepend(w);
	//qDebug().noquote() << QString("_adjacent[%1].append(%2), new size %3").arg(v).arg(w).arg(_adjacent[v].size());
	_adjacent[w].prepend(v);
	//qDebug().noquote() << QString("_adjacent[%1].append(%2), new size %3").arg(w).arg(v).arg(_adjacent[w].size());

	_edges++;

	return true;
}



QList<int> Graph::adjacentOfVertex(int v, QString *error) const
{
	if (v >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertex(%1) to get adjacent").arg(v);

		return QList<int>();
	}


	return _adjacent[v];
}



QString Graph::toString()
{
	QStringList s{ QString("%1 vertices, %2 edges").arg(_vertices).arg(_edges) };
	for (int v = 0; v < _vertices; v++)
	{
		s << QString("%1:").arg(v);
		for (const auto & w : adjacentOfVertex(v))
		{
			s.last() = QString("%1%2 ").arg(s.last()).arg(w);
		}
	}
	return s.join("\n");
}



GraphProcess::GraphProcess()
{
	const QString PATH{ "D:/00 Work/Book/!C++ Books/Teaching/TeachingSolution/tmp/%1" };
	_paths << QString(PATH.arg("tinyG.txt"));
	_paths << QString(PATH.arg("tinyDG.txt"));
}

void GraphProcess::run()
{
	QString path{ _paths[1] };

	QString localError;
	if (!readGraph(path, &localError))
	{
		qDebug().noquote() << QString("Error: %1").arg(localError);
	}

	qDebug().noquote() << SEPARATOR_MINI << "Graph:" << SEPARATOR_MINI;

	auto graphToString = _graph->toString();

	qDebug().noquote() << graphToString;

	qDebug().noquote() << SEPARATOR_MINI << "Depth first search:" << SEPARATOR_MINI;

	//����� � �������
	_searchDfs = QSharedPointer<DepthFirstPaths>(new DepthFirstPaths(_graph, 0));

	qDebug().noquote() << SEPARATOR_MINI << "Paths in graph (depth-first search):" << SEPARATOR_MINI;

	printPaths(_searchDfs, _graph, 0);

	//����� � ������
	_searchBfs = QSharedPointer<BreadFirstPaths>(new BreadFirstPaths(_graph, 0));

	qDebug().noquote() << SEPARATOR_MINI << "Paths in graph (breadth first search):" << SEPARATOR_MINI;

	printPaths(_searchBfs, _graph, 0);
}



int GraphProcess::degree(const Graph & graph, int v)
{
	int degree = graph.adjacentOfVertex(v).size();
	return degree;
}



int GraphProcess::maxDegree(const Graph & graph)
{
	int max{ 0 };
	for (int v = 0; v < graph.vertices(); v++)
	{
		max = degree(graph, v) > max ? degree(graph, v) : max;
	}

	return max;
}



int GraphProcess::avgDegree(const Graph & graph)
{
	/* ����: ��� ������ ����� ��� ������ ������� */
	return 2 * graph.edges() / graph.vertices();
}



int GraphProcess::numberOfSelfLoops(const Graph & graph)
{
	int loopsCount{ 0 };
	for (int v = 0; graph.vertices(); v++)
	{
		for (const auto & w : graph.adjacentOfVertex(v))
		{
			if (v == w)
				loopsCount++;
		}
	}

	/* ������ ����� ��������� ������ */
	return loopsCount / 2;
}



bool GraphProcess::readGraph(QString & pathToFile, QString * error)
{
	qDebug().noquote() << SEPARATOR_MINI << "Reading the graph file" << SEPARATOR_MINI;

	QFile file(pathToFile);
	if (!file.exists())
	{
		if (error)
			*error = QString("File does not exist: %1").arg(pathToFile);

		return false;
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		if (error)
			*error = QString("Something wrong with access to file: %1").arg(pathToFile);

		return false;
	}

	QTextStream in(&file);

	QString line = in.readLine();
	int ln{ 0 };
	bool ok;
	auto vertices = line.toInt(&ok);

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong vertices count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Vertices count: %1").arg(vertices);

	/* �������� ���������� ����� */
	_graph = QSharedPointer<Graph>(new Graph(vertices));

	//
	line = in.readLine();
	auto edges = line.toInt(&ok);
	ln++;

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong edges count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Edges count: %1").arg(edges);

	_graph->setEdges(edges);

	while (!in.atEnd())
	{
		QString line = in.readLine();
		ln++;
		QStringList vw = line.split(" ");
		bool result{ true };

		QPair<int, int> edge;
		if (vw.size() == 2)
		{
			edge.first = vw.first().toInt(&ok);
			result = result && ok;
			edge.second = vw.last().toInt(&ok);
			result = result && ok;

			if (result)
			{
				QString localError;
				if (_graph->addEdge(edge, &localError))
				{
					qDebug().noquote() << QString("Added edge: %1-%2").arg(edge.first).arg(edge.second);
				}
				else
				{
					if (error)
						*error = localError;

					return false;
				}
			}
		}

		if (!result)
		{
			if (error)
				*error = QString("Line %1: Wrong edge parameters(%2)").arg(ln).arg(line);
			return false;
		}

	}

	qDebug().noquote() << SEPARATOR;

	return true;
}



void GraphProcess::printPaths(const QSharedPointer<DepthFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex)
{
	// �� ����������� ��� ����� ������� ������ �� ������ BreadFirstPaths � DepthFirstPaths

	for (int v = 0; v < graph->vertices(); v++)
	{
		QString result{ QString("Paths from %1 to %2: ") };
		result = result.arg(sourceVertex).arg(v);

		if (search->hasPathTo(v))
		{
			auto pt = search->pathTo(v);
			for (int i = 0; i < search->pathTo(v).size(); i++)
			{
				auto p = pt.pop();

				if (p == sourceVertex)
				{
					result += QString("%1").arg(p);
				}
				else
				{
					result += QString("-%1").arg(p);
				}
			}

			qDebug().noquote() << result;
		}
	}
}

void GraphProcess::printPaths(const QSharedPointer<BreadFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex, const QList<QString> & names)
{
	// �� ����������� ��� ����� ������� ������ �� ������ BreadFirstPaths � DepthFirstPaths

	for (int v = 0; v < graph->vertices(); v++)
	{
		QString result{ QString("Paths from %1 to %2: ") };
		if (names.size() <= sourceVertex && names.size() <= v)
		{
			result = result.arg(sourceVertex).arg(v);
		}
		else
		{
			result = result.arg(names[sourceVertex]).arg(names[v]);
		}

		if (search->hasPathTo(v))
		{
			auto pt = search->pathTo(v);
			for (int i = 0; i < search->pathTo(v).size(); i++)
			{
				auto p = pt.pop();
				auto ps = QString(p);
				if (names.size() > p)
					ps = names[p];

				if (p == sourceVertex)
				{
					result += QString("%1").arg(ps);
				}
				else
				{
					result += QString("-%1").arg(ps);
				}
			}

			qDebug().noquote() << result;
		}
	}
}

SearchInGraph::SearchInGraph(const Graph & graph, int source)
{
}

bool SearchInGraph::marked(int v)
{
	return false;
}

int SearchInGraph::count()
{
	return 0;
}


/* =========================== */
/* ����� � ������� � �� ��������������� ������ */
DepthFirstSearch::DepthFirstSearch(const QSharedPointer<Graph> & graph, int sourceVertex)
{
	init(graph, sourceVertex);
}


void DepthFirstSearch::init(const QSharedPointer<Graph> & graph, int sourceVertex)
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
	}

	dfs(graph, sourceVertex);
}

bool DepthFirstSearch::marked(int v)
{
	if (v >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) get marked value").arg(v);
		return false;
	}

	return _marked[v];
}



int DepthFirstSearch::count() const
{
	return _count;
}



void DepthFirstSearch::dfs(const QSharedPointer<Graph> & graph, int vertex)
{
	if (vertex >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) to mark of adjacent vertices").arg(vertex);
		return;
	}

	_marked[vertex] = true;
	_count++;

	qDebug().noquote() << QString("Info: Vertex(%1) marked").arg(vertex);

	for (const auto w : graph->adjacentOfVertex(vertex))
	{
		if (!marked(w))
		{
			setEdgeTo(w, vertex);
			dfs(graph, w);
		}
		else
		{
			qDebug().noquote() << QString("Info: Vertex(%1) already marked").arg(w);
		}
	}
}



void DepthFirstSearch::setEdgeTo(int w, int v)
{
}



/* ================================= */
/* ���������� ����� */
/* �������� 4.1. ����� � ������� ��� ���������� ����� */

DepthFirstPaths::DepthFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex) :
	_sourceVertex{ sourceVertex }
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_edgeTo.append(-1);
	}

	init(graph, sourceVertex);
}



bool DepthFirstPaths::hasPathTo(int v, QString * error)
{
	return marked(v);
}

void DepthFirstPaths::setEdgeTo(int w, int v)
{
	if (w >= _edgeTo.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) set _edgeTo[%1]").arg(w);
		return;
	}

	_edgeTo[w] = v;
}

QStack<int> DepthFirstPaths::pathTo(int v)
{
	QStack<int> path;
	if (!hasPathTo(v))
		return path;

	for (int x = v; x != _sourceVertex; x = _edgeTo[x])
	{
		path.push(x);
	}
	path.push(_sourceVertex);

	return path;
}




BreadFirstPaths::BreadFirstPaths(const QSharedPointer<Graph>& graph, int sourceVertex) :
	_sourceVertex(sourceVertex)
{
	init(graph, sourceVertex);
	bfs(graph, sourceVertex);
}

void BreadFirstPaths::init(const QSharedPointer<Graph>& graph, int sourceVertex)
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
		_edgeTo.append(-1);
	}
}

bool BreadFirstPaths::setEdgeTo(int w, int v)
{
	if (w >= _edgeTo.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) set _edgeTo[%1]").arg(w);
		return false;
	}

	_edgeTo[w] = v;
	return true;
}



int BreadFirstPaths::edgeTo(int w)
{
	return w < _edgeTo.size() ? _edgeTo[w] : -1;
}



bool BreadFirstPaths::setMarked(int w)
{
	if (w < _marked.size())
	{
		_marked[w] = true;
		return true;
	}

	return true;
}



bool BreadFirstPaths::marked(int w)
{
	return w < _marked.size() ? _marked[w] : false;
}



bool BreadFirstPaths::hasPathTo(int v, QString * error)
{
	return marked(v);
}



QStack<int> BreadFirstPaths::pathTo(int v)
{
	/* ���������� DepthFirstPaths::pathTo */
	QStack<int> path;
	if (!hasPathTo(v))
		return path;

	for (int x = v; x != _sourceVertex; x = _edgeTo[x])
	{
		path.push(x);
	}
	path.push(_sourceVertex);

	return path;
}



/* breadth first search: ����� � �������  */
void BreadFirstPaths::bfs(const QSharedPointer<Graph>& graph, int vertex)
{
	/*  */
	QQueue<int> queue;
	setMarked(vertex); // ������� �������� �������
	queue.enqueue(vertex); // � ��������� � � �������
	while (!queue.isEmpty())
	{
		// ���������� �� ������� ��������� �������
		int v = queue.dequeue();
		for (const auto w : graph->adjacentOfVertex(v))
		{
			// ��� ������ ������������ ������� �������:
			if (!marked(w))
			{
				// ��������� ����� � ���������� ����
				setEdgeTo(w, v);
				// �������� ��, �.�. ���� ��������
				setMarked(w);
				// � ������� �� � �������
				queue.enqueue(w);
			}
		}
	}

}


void SymbolGraphProcess::run()
{
	readGraph("D:/00 Work/Book/!C++ Books/Teaching/TeachingSolution/tmp/routes.txt");


	QSharedPointer<SymbolGraph> sGr = QSharedPointer<SymbolGraph>(new SymbolGraph(_edgesList));

	auto gr = sGr->graph();
	if (gr)
	{
		qDebug().noquote() << SEPARATOR_MINI << "Adjacent graph vertices" << SEPARATOR_MINI;

		QStringList vertices{ "JFK", "LAX" };
		for (const auto & vertex : vertices)
		{
			qDebug().noquote() << vertex;
			for (auto w : gr->adjacentOfVertex(sGr->index(vertex)))
			{
				qDebug().noquote() << "\t" << sGr->name(w);
			}
		}

		qDebug().noquote() << SEPARATOR_MINI << "Degrees of separation" << SEPARATOR_MINI;

		int s = sGr->index("HOU");
		auto bfs = QSharedPointer<BreadFirstPaths>(new BreadFirstPaths(gr, s));
		qDebug().noquote() << SEPARATOR_MINI << "Paths in graph (breadth first search):" << SEPARATOR_MINI;

		GraphProcess gp;
		gp.printPaths(bfs, gr, s, sGr->keys());

	}
}

void SymbolGraphProcess::readGraph(const QString & pathToFile)
{
	qDebug().noquote() << SEPARATOR_MINI << "Reading the symbol graph file" << SEPARATOR_MINI;

	QFile file(pathToFile);
	if (!file.exists())
	{
		qDebug().noquote() << QString("Error: File does not exist: %1").arg(pathToFile);

		return;
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug().noquote() << QString("Error: Something wrong with access to file: %1").arg(pathToFile);

		return;
	}

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		QStringList edge = line.split(" ");
		if (edge.size() == 2)
		{
			_edgesList.append(edge);
		}
	}
}



SymbolGraph::SymbolGraph(const QList<QStringList> & edgesList)
{
	/* �������� ������� */
	for (const auto & edge : edgesList)
	{
		for (const auto & vertex : edge)
		{
			if (!_st.contains(vertex))
			{
				/* ������� ������� � ��������� �� � ��������� */
				_st.insert(vertex, _st.size());
				_keys.append(QString());
			}
		}
	}

	auto it = _st.constBegin();
	while (it != _st.constEnd())
	{
		_keys[it.value()] = it.key();
		++it;
	}

	/* �������� ���������� ����� */
	_graph = QSharedPointer<Graph>(new Graph(_st.size()));
	/* ���������� ����� */
	for (const auto & edge : edgesList)
	{
		auto itStart = _st.constFind(edge.first());
		/* �� ������ ��� ����� ���� ������ ������ ����� � ������ */
		auto itEnd = _st.constFind(edge.last());
		/* ���������� ���� �� ��������� �������������� �������� */
		if (itStart != _st.constEnd() && itEnd != _st.constEnd())
		{
			int vertexIndexStart = itStart.value();
			int vertexIndexEnd = itEnd.value();
			_graph->addEdge(QPair<int, int>(vertexIndexStart, vertexIndexEnd));
		}
	}
}

int SymbolGraph::index(const QString & key)
{
	auto itIndex = _st.constFind(key);
	if (itIndex != _st.constEnd())
	{
		return itIndex.value();
	}

	return -1;
}

QString SymbolGraph::name(int v)
{
	if (_keys.size() > v && v >= 0)
	{
		return _keys[v];
	}

	return QString();
}

/* 4.2.1. ��������������� ����� */
/* �������� ����� � v ��������� ��� ���� */
Digraph::Digraph(int v) : _vertices(v), _edges(0)
{
	for (int i = 0; i < v; i++)
	{
		_adjacent.append(QList<int>());
	}
}

int Digraph::vertices() const
{
	return _vertices;
}



int Digraph::edges() const
{
	return _edges;
}

void Digraph::setEdges(int cnt)
{
	_edges = cnt;
}


/* ���������� � ���� ����� v-w  */
bool Digraph::addEdge(QPair<int, int> edge, QString *error)
{
	auto v = edge.first;
	auto w = edge.second;

	if (v >= _adjacent.size() || w >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertices(%1,%2) for edge").arg(v).arg(w);
		return false;
	}
	/*
		� ������� �� �� ��������������� ������ ������ ����� ������������ ��������
	*/
	_adjacent[v].prepend(w);

	_edges++;

	return true;
}


/* ������� ������� � v */
QList<int> Digraph::adjacentOfVertex(int v, QString *error) const
{
	if (v >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertex(%1) to get adjacent").arg(v);

		return QList<int>();
	}


	return _adjacent[v];
}



QString Digraph::toString()
{
	QStringList s{ QString("%1 vertices, %2 edges").arg(_vertices).arg(_edges) };
	for (int v = 0; v < _vertices; v++)
	{
		s << QString("%1:").arg(v);
		for (const auto & w : adjacentOfVertex(v))
		{
			s.last() = QString("%1%2 ").arg(s.last()).arg(w);
		}
	}
	return s.join("\n");
}

Digraph Digraph::reverse()
{
	Digraph result = Digraph(_vertices);
	for (int v = 0; v < _vertices; v++)
	{
		for (auto w : adjacentOfVertex(v))
		{
			/* ������ ���� �� �������� */
			result.addEdge(QPair<int, int>(w, v));
		}
	}

	return result;
}

/* ������� 4.2.2 ����� � �������. ������������ � �������� */
DirectedDepthFirstSearch::DirectedDepthFirstSearch(const QSharedPointer<Digraph>& graph, QList<int> sources) : _gv(graph->vertices())
{
	init(graph, sources);
}


void DirectedDepthFirstSearch::init(const QSharedPointer<Digraph> & graph, QList<int> sources)
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
	}
	for (auto source : sources)
	{
		if (!marked(source))
		{
			dfs(graph, source);
		}
	}
}

bool DirectedDepthFirstSearch::marked(int v)
{
	if (v >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) get marked value").arg(v);
		return false;
	}

	return _marked[v];
}


void DirectedDepthFirstSearch::dfs(const QSharedPointer<Digraph> & graph, int vertex)
{
	if (vertex >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) to mark of adjacent vertices").arg(vertex);
		return;
	}

	_marked[vertex] = true;

	qDebug().noquote() << QString("Info: Vertex(%1) marked").arg(vertex);

	for (const auto w : graph->adjacentOfVertex(vertex))
	{
		if (!marked(w))
		{
			dfs(graph, w);
		}
		else
		{
			qDebug().noquote() << QString("Info: Vertex(%1) already marked").arg(w);
		}
	}
}

void DirectedDepthFirstSearch::printReachableList()
{
	/* ������ ���������� ������ */
	QStringList reachable;
	for (int v = 0; v < _gv; v++)
	{
		if (marked(v))
		{
			reachable << QString::number(v);
		}
	}

	qDebug().noquote() << QString("Info: reachable list: %1").arg(reachable.join("; "));
}



DigraphProcess::DigraphProcess()
{
	const QString PATH{ "D:/00 Work/Book/!C++ Books/Teaching/TeachingSolution/tmp/%1" };
	_paths << QString(PATH.arg("tinyDG.txt"));
	_paths << QString(PATH.arg("tinyDAG.txt"));
}

void DigraphProcess::run()
{
	//QString path{ _paths[0] }; // ��� ����������� ������� �����
	QString path{ _paths[1] }; // ������������ ������

	QString localError;
	if (!readGraph(path, &localError))
	{
		qDebug().noquote() << QString("Error: %1").arg(localError);
	}

	qDebug().noquote() << SEPARATOR_MINI << "Directed graph:" << SEPARATOR_MINI;

	auto graphToString = _diGraph->toString();

	qDebug().noquote() << graphToString;

	qDebug().noquote() << SEPARATOR_MINI << "Directed depth first search:" << SEPARATOR_MINI;

	// ����������� ������������ �� ������ ��������� (����� � �������)
	//QList<int> sources{ /*1,*/2/*,6*/ };
	QList<int> sources{ 6 };
	_diDfs = QSharedPointer<DirectedDepthFirstSearch>(new DirectedDepthFirstSearch(_diGraph, sources));
	_diDfs->printReachableList();

	qDebug().noquote() << SEPARATOR_MINI << "Directed cycle:" << SEPARATOR_MINI;
	DirectedCycle dc(_diGraph);
	dc.printCycle();

	qDebug().noquote() << SEPARATOR_MINI << "Directed depth first order:" << SEPARATOR_MINI;
	DirectedDepthFirstOrder ddfo(_diGraph);
	ddfo.print();
}


bool DigraphProcess::readGraph(QString & pathToFile, QString * error)
{
	qDebug().noquote() << SEPARATOR_MINI << "Reading the graph file" << SEPARATOR_MINI;

	QFile file(pathToFile);
	if (!file.exists())
	{
		if (error)
			*error = QString("File does not exist: %1").arg(pathToFile);

		return false;
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		if (error)
			*error = QString("Something wrong with access to file: %1").arg(pathToFile);

		return false;
	}

	QTextStream in(&file);

	QString line = in.readLine();
	int ln{ 0 };
	bool ok;
	auto vertices = line.toInt(&ok);

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong vertices count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Vertices count: %1").arg(vertices);

	/* �������� ���������� ����� */
	_diGraph = QSharedPointer<Digraph>(new Digraph(vertices));

	//
	line = in.readLine();
	auto edges = line.toInt(&ok);
	ln++;

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong edges count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Edges count: %1").arg(edges);

	_diGraph->setEdges(edges);

	while (!in.atEnd())
	{
		QString line = in.readLine();
		ln++;
		QStringList vw = line.split(" ");
		bool result{ true };

		QPair<int, int> edge;
		if (vw.size() == 2)
		{
			edge.first = vw.first().toInt(&ok);
			result = result && ok;
			edge.second = vw.last().toInt(&ok);
			result = result && ok;

			if (result)
			{
				QString localError;
				if (_diGraph->addEdge(edge, &localError))
				{
					qDebug().noquote() << QString("Added edge: %1-%2").arg(edge.first).arg(edge.second);
				}
				else
				{
					if (error)
						*error = localError;

					return false;
				}
			}
		}

		if (!result)
		{
			if (error)
				*error = QString("Line %1: Wrong edge parameters(%2)").arg(ln).arg(line);
			return false;
		}

	}

	qDebug().noquote() << SEPARATOR;

	return true;
}



DirectedCycle::DirectedCycle(const QSharedPointer<Digraph>& graph)
{
	init(graph);
	for (int v = 0; v < graph->vertices(); v++)
	{
		if (!marked(v))
		{
			dfs(graph, v);
		}
	}
}


void DirectedCycle::printCycle() const
{
	QStringList sl;
	for (auto ce : _cycle.toList())
	{
		sl.append(QString::number(ce));
	}

	qDebug().noquote() << QString("Info: cycle: %1").arg(sl.isEmpty() ? "No" : sl.join("->"));
}

void DirectedCycle::init(const QSharedPointer<Digraph>& graph)
{
	for (size_t i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
		_onStack.append(false);
		_edgeTo.append(-1);
	}
}

void DirectedCycle::dfs(const QSharedPointer<Digraph>& graph, int v)
{
	qDebug().noquote() << QString("Info: dfs(..., %1)").arg(QString::number(v));

	if (hasCycle())
	{
		return;
	}

	setOnStack(v, true);
	setMarked(v, true);

	for (int w : graph->adjacentOfVertex(v))
	{
		if (hasCycle())
		{
			return;
		}
		else if (!marked(w))
		{
			qDebug().noquote() << QString("Info: edge to %2->%1").arg(QString::number(w)).arg(QString::number(v));
			setEdgeTo(w, v);
			dfs(graph, w);
		}
		else if (onStack(w))
		{
			qDebug().noquote() << QString("Info: on stack %1").arg(QString::number(w));

			auto hc = false;
			for (int x = v; x != w; x = edgeTo(x))
			{
				qDebug().noquote() << QString("Warn: cycle push: x=%1").arg(QString::number(x));
				_cycle.push(x);
			}
			qDebug().noquote() << QString("Warn: cycle push: w=%1").arg(QString::number(w));
			_cycle.push(w);
			qDebug().noquote() << QString("Warn: cycle push: v=%1").arg(QString::number(v));
			_cycle.push(v);

		}
	}

	setOnStack(v, false);

}

DirectedDepthFirstOrder::DirectedDepthFirstOrder(const QSharedPointer<Digraph>& graph)
{
	init(graph);
	for (int v = 0; v < graph->vertices(); v++)
	{
		if (!marked(v))
		{
			dfs(graph, v);
		}
	}
}

void DirectedDepthFirstOrder::print()
{
	{
		QStringList sl;
		for (auto ce : pre())
		{
			sl.append(QString::number(ce));
		}

		qDebug().noquote() << QString("Info: Preorder: %1").arg(sl.join("->"));
	}
	{
		QStringList sl;
		for (auto ce : post())
		{
			sl.append(QString::number(ce));
		}

		qDebug().noquote() << QString("Info: Postorder: %1").arg(sl.join("->"));
	}
	{
		QStringList sl;
		QStack<int> rp = reversePost();
		while (!rp.isEmpty())
		{
			sl.append(QString::number(rp.pop()));
		}

		qDebug().noquote() << QString("Info: Reverse postorder: %1").arg(sl.join("->"));
	}
}

void DirectedDepthFirstOrder::init(const QSharedPointer<Digraph>& graph)
{
	for (size_t i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
	}
}

void DirectedDepthFirstOrder::dfs(const QSharedPointer<Digraph>& graph, int v)
{
	//qDebug().noquote() << QString("Info: dfs(..., %1)").arg(QString::number(v));

	setMarked(v, true);

	_pre.enqueue(v);

	for (int w : graph->adjacentOfVertex(v))
	{
		if (!marked(w))
		{
			dfs(graph, w);
		}
	}
	_post.enqueue(v);
	_reversePost.push(v);
}

} //namespace graphs