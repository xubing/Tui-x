#include "Mapui.h"
#include "tui/TuiManager.h"
//#include "tui/tagMap/Tag_store.h"

void Mapui::onLoadScene()
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("store/storeui.plist");
	//TuiManager::getInstance()->parseScene(this,"panel_store",PATH_STORE);
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
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
Node * Mapui::getPanel( int tagPanel )
{
	/*
	Node *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_STORE:
		pPanel = this->getChildByTag(PANEL_STORE);
		break;
	}
	return pPanel;
	*/
	return nullptr;
}
