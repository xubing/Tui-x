#include "Bagui.h"
#include "tui/tagMap/Tag_bag.h"
#include "tui/TuiManager.h"

NS_BAG_BEGIN

void Bagui::onLoadScene()
{
	setCachable(true);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bag/bagui.plist");
	TuiManager::getInstance()->parseScene(this, "panel_bag", PATH_BAG);

	CGridView* pGridView = (CGridView*)this->getControlByTag( GV_BAG);
	pGridView->setDataSourceAdapter(this, ccw_datasource_adapter_selector(Bagui::event_adapt_gvBag));
	pGridView->reloadData();

	CTableView* pTblView = (CTableView*)this->getControlByTag( TBL_BAG);
	pTblView->setDataSourceAdapter(this, ccw_datasource_adapter_selector(Bagui::event_adapt_tblBag));
	pTblView->reloadData();

	CPageView* pPageView = (CPageView*)this->getControlByTag( PV_BAG);
	pPageView->setDataSourceAdapter(this, ccw_datasource_adapter_selector(Bagui::event_adapt_pageBag));
	pPageView->reloadData();

	CButton* pBtnView = (CButton*)this->getControlByTag( BTN_BACK);
	pBtnView->setOnClickListener(this, ccw_click_selector(Bagui::event_btn_back));
}

Ref* Bagui::event_adapt_gvBag(Ref* pConvertCell, unsigned int uIdx)
{
	CGridViewCell* pCell = (CGridViewCell*)pConvertCell;
	CButton *btn = nullptr;
	if (!pCell)
	{
		pCell = new CGridViewCell();
		pCell->autorelease();

		TuiManager::getInstance()->parseCell(pCell, "cell_grid", PATH_BAG);

		btn = (CButton*)pCell->getChildByTag(BTN_GRID);
		btn->setOnClickListener(this, ccw_click_selector(Bagui::event_btn_gv));
	}else{
		btn = (CButton*)pCell->getChildByTag(BTN_GRID);
	}
	btn->setUserTag(uIdx);
	return pCell;
}

Ref* Bagui::event_adapt_tblBag(Ref* pConvertCell, unsigned int uIdx)
{
	CTableViewCell* pCell = (CTableViewCell*)pConvertCell;
	if (!pCell)
	{
		pCell = new CTableViewCell();
		pCell->autorelease();

		TuiManager::getInstance()->parseCell(pCell, "cell_grid", PATH_BAG);
	}else{

	}
	return pCell;
}

Ref* Bagui::event_adapt_pageBag(Ref* pConvertCell, unsigned int uIdx)
{
	CPageViewCell *pCell = (CPageViewCell*)pConvertCell;
	if (!pCell)
	{
		pCell = new CPageViewCell();
		pCell->autorelease();

		TuiManager::getInstance()->parseCell(pCell, "cell_page", PATH_BAG);
	}else{

	}
	return pCell;
}

void Bagui::event_btn_back(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Main::Mainui")));
}

void Bagui::event_btn_gv(Ref* pSender)
{
	CButton *btn = (CButton*)pSender;
	int id = btn->getUserTag();

	CCLOG("id = %d", id);
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/


NS_BAG_END