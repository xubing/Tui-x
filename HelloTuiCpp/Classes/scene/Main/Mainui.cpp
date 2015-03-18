#include "Mainui.h"
#include "tui/TuiManager.h"
#include "tui/tagMap/Tag_main.h"
#include "dialog/MsgBox.h"

NS_MAIN_BEGIN

void Mainui::onLoadScene()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main/mainui.plist");
	TuiManager::getInstance()->parseScene(this,"panel_main",PATH_MAIN);

	Vec2 area = Arp(Vec2(618, 10));
	CWidgetWindow *panel = (CWidgetWindow*)getControlByTag(PANEL_MAIN);
	panel->setTouchAreaEnabled(true);
    panel->setTouchArea(cocos2d::Rect(area.x, area.y, 92, 36));

	//注册事件
	CControlView *ctlv = (CControlView*)this->getControlByTag(CTLV_LEFT);
	ctlv->setOnControlListener(this,ccw_control_selector(Mainui::event_ctlv_left));

	CButton *pBtnOk = (CButton*)this->getControlByTag(BTN_OK);
	pBtnOk->setOnClickListener(this,ccw_click_selector(Mainui::event_btn_ok));

	CButton *pBtnGo = (CButton*)this->getControlByTag(BTN_GO);
	pBtnGo->setOnClickListener(this,ccw_click_selector(Mainui::event_btn_go));

	CButton *pBtnPhone = (CButton*)this->getControlByTag( BTN_SHOWPHONE);
	pBtnPhone->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_showphone));

	CButton *pBtnBag = (CButton*)this->getControlByTag( BTN_BAG);
	pBtnBag->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_bag));

	CButton *pBtnRecombine = (CButton*)this->getControlByTag( BTN_RECOMBINE);
	pBtnRecombine->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_recombine));

	CToggleView *pTgvA = (CToggleView*)this->getControlByTag( TGV_A);
	pTgvA->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvA_check));

	CToggleView *pTgvB = (CToggleView*)this->getControlByTag( TGV_B);
	pTgvB->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvB_check));
    
    CEditBox *pEditBox = (CEditBox*)this->getControlByTag( EDIT_LOGIN);
    pEditBox->setDelegate(this);
    
	CSceneManager::getInstance()->runSuspendScene(LoadScene("Guideui"));
}

void Mainui::editBoxReturn(CEditBox *pEditBox)
{

}

void Mainui::event_ctlv_left( Ref* pSender, float fx, float fy )
{
	Sprite *pIcon = (Sprite*)this->getControlByTag(ANIM_COIN);
	pIcon->setPosition(pIcon->getPosition() + Arp(Vec2(fx, fy)));
}

void Mainui::event_tgvA_check(Ref *pSender, bool bChecked)
{

}

void Mainui::event_tgvB_check(Ref *pSender, bool bChecked)
{

}

void Mainui::event_btn_ok(Ref* pSender)
{
	CSceneManager::getInstance()->runUIScene(LoadScene("Main::MsgBox"));
}

void Mainui::event_btn_showphone(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("ShowPhone::ShowPhoneui")));
}

void Mainui::event_btn_go(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Store::Storeui")));
	
}

void Mainui::event_btn_bag(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Bag::Bagui")));
}

void Mainui::event_btn_recombine(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Recomebineui")));
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/

void Mainui::onMessage(unsigned int uMsg, Ref* pMsgObj, void* wParam, void* lParam)
{
	switch (uMsg)
	{
	case FINISH_GUIDE:
	{
		CWidgetWindow *panel = (CWidgetWindow*)getControlByTag(PANEL_MAIN);
		panel->setTouchAreaEnabled(false);
	}
		break;
	default:
		break;
	}
}

NS_MAIN_END