#include "MsgBox.h"
#include "tui/TuiManager.h"
#include "tui/tagMap/Tag_main.h"

NS_MAIN_BEGIN

void MsgBox::onLoadScene()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main/mainui.plist");
	TuiManager::getInstance()->parseScene(this,"panel_msgbox",PATH_MAIN);
	//注册事件
	CButton *pBtnClose = (CButton*)getControlByTag(BTN_CLOSE);
	pBtnClose->setOnClickListener(this,ccw_click_selector(MsgBox::event_btn_close));
	
	CSlider *pSlider = (CSlider*)getControlByTag(SLIDER_TEST);
	pSlider->setOnValueChangedListener(this,ccw_valuechanged_selector(MsgBox::event_slider_test));
}

void MsgBox::event_btn_close( Ref *pSender )
{
	CSceneManager::getInstance()->popUIScene(this);
}

void MsgBox::event_slider_test(Ref *pSender,int value)
{
	char buf[128] = {0};
	sprintf(buf,"%d",value);
	CLabelAtlas *pLab = (CLabelAtlas*)this->getControlByTag(LABATLAS_NUM);
	pLab->setString(buf);

	CProgressBar *pProg = (CProgressBar*)this->getControlByTag(PROG_HP);
	pProg->setValue(value);

}


/************************************************************************/
//	GET/SET/IS
/************************************************************************/

void MsgBox::onEnterScene()
{
	CSceneExtension *pGuideui = CSceneManager::getInstance()->seekScene("Guideui");
	if (pGuideui != nullptr){
		CSceneManager::getInstance()->popSuspendScene(pGuideui);
		CCMsgManager::getInstance()->PostMessage(FINISH_GUIDE);
	}
		
}


NS_MAIN_END