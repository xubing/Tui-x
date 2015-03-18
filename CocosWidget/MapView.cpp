/************************************************************************
The MIT License(MIT)

Copyright(c) 2014 Lingjijian [B-y]

342854406@qq.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
************************************************************************/
#include "MapView.h"

NS_CC_WIDGET_BEGIN

CGrid* CGrid::create( int numCols,int numRows )
{
	CGrid *ret = new CGrid();
	if (ret && ret->init(numCols,numRows))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool CGrid::init( int numCols,int numRows )
{
	_numCols = numCols;
	_numRows = numRows;
	_startNode = nullptr;
	_endNode = nullptr;
	
	_nodes = vector<VectNode>();
	for (int i = 0;i< _numCols; i++)
	{
		_nodes.push_back(VectNode());
		for (int j = 0;j< _numRows; j++)
		{
			_nodes[i].pushBack( CNode::create(i,j) );
		}
	}
	return true;
}

void CGrid::setStartNode( int x,int y )
{
	auto node = _nodes[x].at(y);
	if (_startNode != node) 
	{ 
		CC_SAFE_RETAIN(node); 
		CC_SAFE_RELEASE(_startNode); 
		_startNode = node; 
	} 
}

void CGrid::setEndNode( int x,int y )
{
	auto node = _nodes[x].at(y);
	if (_endNode != node) 
	{ 
		CC_SAFE_RETAIN(node); 
		CC_SAFE_RELEASE(_endNode); 
		_endNode = node; 
	} 
}

CNode* CNode::create( int x,int y )
{
	CNode *ret = new CNode();
	if (ret && ret->init(x,y))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool CNode::init( int x,int y )
{
	this->x = x;
	this->y = y;
	this->costMultiplier = 1;
    this->walkable = true;
	return true;
}

static AStar* s_Astar = nullptr;
AStar* AStar::getInstance()
{
	if (s_Astar == nullptr)
	{
		s_Astar = new (std::nothrow) AStar();
		if(s_Astar && s_Astar->init()){
			s_Astar->retain();
		}else{
			CC_SAFE_DELETE(s_Astar);
			s_Astar = nullptr;
		}
	}
	return s_Astar;
}

bool AStar::init()
{
	_startNode = nullptr;
	_endNode = nullptr;
	setHeuristicFunc(eDiagonal);
	return true;
}

bool AStar::findPath( CGrid *grid )
{
	_grid = grid;
	_open = VectNode();
	_close = VectNode();
	_startNode = _grid->getStartNode();
	_endNode = _grid->getEndNode();
	_startNode->g = 0;
	_startNode->h = _heuristic(_startNode);

	return search();
}

bool AStar::search()
{
	auto node = _startNode;
	while (node != _endNode)
	{
		int startX = max(0, node->x - 1);
		int endX = min(_grid->getNumCols() - 1, node->x + 1);
		int startY = max(0, node->y - 1);
		int endY = min(_grid->getNumRows() - 1,node->y + 1);

		for (int i = startX;i<= endX;i ++)
		{
			for (int j = startY;j<= endY;j ++)
			{
				auto test = _grid->getNode(i,j);
				if (test == node ||
					!test->walkable ||
					!_grid->getNode(node->x,test->y)->walkable ||
					!_grid->getNode(test->x,node->y)->walkable)
				{
					continue;
				}

				float cost = _straightCost;
				if(!((node->x == test->x) || (node->y == test->y)))
				{
					cost = _diagCost;
				}

				float g = node->g + cost * test->costMultiplier;
				float h = _heuristic(test);
				float f = g + h;
				if(isOpen(test) || isClose(test))
				{
					if(test->f > f)
					{
						test->f = f;
						test->g = g;
						test->h = h;
						test->parent = node;
					}
				}
				else
				{
					test->f = f;
					test->g = g;
					test->h = h;
					test->parent = node;
					_open.pushBack(test);
				}
			}
		}
		_close.pushBack(node);
		if(_open.size() == 0)
		{
			CCLOG("no path found");
			return false;
		}
		sort(_open.begin(), _open.end(), AStar::sortOnF);
		node = *_open.begin();
		_open.erase(_open.begin());
	}

	buildPath();
	return true;
}

bool AStar::isOpen( CNode* node )
{
	int len = _open.size();
	for(int i = 0; i < len; i++)
	{
		if(_open.at(i) == node)
		{
			return true;
		}
	}
	return false;
}

bool AStar::isClose( CNode* node )
{
	int len = _close.size();
	for(int i = 0; i < len; i++)
	{
		if(_close.at(i) == node)
		{
			return true;
		}
	}
	return false;
}

bool AStar::sortOnF( CNode* a,CNode* b )
{
	return a->f < b->f;
}

void AStar::buildPath()
{
	_path = VectNode();
	auto node = _endNode;
	_path.pushBack(node);
	while (node != _startNode)
	{
		node = node->parent;
		_path.insert(0,node);
	}
}

void AStar::setHeuristicFunc( HeuristicType type )
{
	if (type == eManhattan){
		_heuristic = [&](CNode* node){
			return abs(node->x - _endNode->x) * _straightCost + abs(node->y + _endNode->y) * _straightCost;
		};
	}else if (type == eEuclidian){
		_heuristic = [&](CNode* node){
			float dx = node->x - _endNode->x;
			float dy = node->y - _endNode->y;
			return sqrt(dx * dx + dy * dy) * _straightCost;
		};
	}else if (type == eDiagonal){
		_heuristic = [&](CNode* node){
			float dx = abs(node->x - _endNode->x);
			float dy = abs(node->y - _endNode->y);
			float diag = min(dx, dy);
			float straight = dx + dy;
			return _diagCost * diag + _straightCost * (straight - 2 * diag);
		};
	}
}

VectNode AStar::getVisited()
{
	VectNode ret;
	ret.pushBack(_open);
	ret.pushBack(_close);
	return ret;
}
//////////////////////////////////////////////////////////////////////////
CMapView::CMapView()
{

}

CMapView* CMapView::create(const Size& tViewSize)
{
	CMapView* pRet = new CMapView();
	if( pRet && pRet->initWithSize(tViewSize) )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CMapView* CMapView::create(const Size& tViewSize, const Size& tCellSize, unsigned int uCellCount,
							 Ref* pListener, SEL_DataSoucreAdapterHandler pHandler)
{
	CMapView* pRet = new CMapView();
	if( pRet && pRet->initWithParams(tViewSize, tCellSize, uCellCount, pListener, pHandler))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

NS_CC_WIDGET_END