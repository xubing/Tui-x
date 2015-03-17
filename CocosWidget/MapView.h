#ifndef __CCWIDGET_MAPVIEW_H__
#define __CCWIDGET_MAPVIEW_H__

#include "GridView.h"

NS_CC_WIDGET_BEGIN

using namespace std;
class CMapView;
class CMapViewCell;
class CGrid;
class CNode;
typedef Vector<CNode*> VectNode ;

class CNode : public Ref
{
public:
	static CNode* create(int x,int y);
	bool init(int x,int y);
	int x;
	int y;
	float f;
	float g;
	float h;
	bool walkable;
	CNode *parent;
	float costMultiplier;
};

class CGrid : public Ref
{
public:
	static CGrid* create(int numCols,int numRows);
	bool init(int numCols,int numRows);
	CNode *getNode(int x,int y) { return _nodes[x].at(y); };
	void setStartNode(int x,int y);
	void setEndNode(int x,int y);
	void setWalkable(int x,int y,bool b) { _nodes[x].at(y)->walkable = b; };
	CNode* getStartNode(){ return _startNode;};
	CNode* getEndNode(){ return _endNode;};
	int getNumCols(){ return _numCols;};
	int getNumRows(){ return _numRows;};
	
private:
	CNode* _startNode;
	CNode* _endNode;
	int _numCols;
	int _numRows;
	vector<VectNode> _nodes;
};

enum HeuristicType{
	eManhattan,
	eEuclidian,
	eDiagonal,
};

class AStar : public Ref
{
public:
	AStar():
		_straightCost(1),
		_diagCost(sqrt(2)){};
	virtual bool init();
	static AStar *getInstance();

	bool findPath(CGrid *grid);
	bool search();
	void buildPath();
	VectNode getPath(){return _path;};
	void setHeuristicFunc(HeuristicType type);
	VectNode getVisited();
protected:
	bool isOpen(CNode* node);
	bool isClose(CNode* node);
	static bool sortOnF(CNode* a,CNode* b);
private:
	VectNode _open;
	VectNode _close;
	CGrid* _grid;
	CNode* _startNode;
	CNode* _endNode;
	VectNode _path;
	float _straightCost;
	float _diagCost;
	function<float(CNode*)> _heuristic;
};

//////////////////////////////////////////////////////////////////////////

class CMapViewCell : public CGridViewCell
{
public:
    CMapViewCell();
	virtual ~CMapViewCell();
};


class CMapView : public CGridView
{
public:
	CMapView();
	virtual ~CMapView();




};

NS_CC_WIDGET_END

#endif //__CCWIDGET_MAPVIEW_H__