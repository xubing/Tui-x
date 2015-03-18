#include "Mapui.h"
#include "tui/TuiManager.h"
#include "tui/tagMap/Tag_map.h"

void Mapui::onLoadScene()
{
	TuiManager::getInstance()->parseScene(this,"panel_map",PATH_MAP);
	_grid = CGrid::create(30,30);
	_grid->retain();
	for (int i = 0;i<200;i++)
	{
		_grid->setWalkable(
			floor(CCRANDOM_0_1() * 30),
			floor(CCRANDOM_0_1() * 30),
			false);
	}
		
	_grid->setStartNode(1,1);
	_grid->setEndNode(25,25);

	if (AStar::getInstance()->findPath(_grid))
	{
		VectNode path = AStar::getInstance()->getPath();
		for (int i = 0; i < path.size(); i++)
		{
			CCLOG("x = %d y = %d ",path.at(i)->x,path.at(i)->y);
		}
	}

	CMapView* pMapView = (CMapView*)this->getControlByTag(MAP_VIEW);
	pMapView->setDataSourceAdapter(this, ccw_datasource_adapter_selector(Mapui::event_adapt_map));
	pMapView->reloadData();
}

Ref* Mapui::event_adapt_map(Ref* pConvertCell, unsigned int uIdx)
{
	CMapViewCell* pCell = (CMapViewCell*)pConvertCell;
	if (!pCell)
	{
		pCell = new CMapViewCell();
		pCell->autorelease();

		char buf[128];
		sprintf(buf,"cell_grid%d",uIdx);
		TuiManager::getInstance()->parseCell(pCell, buf, PATH_MAP);

	}else{

	}
	return pCell;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
