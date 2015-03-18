#ifndef __MAP_UI_H__
#define __MAP_UI_H__

#include "../../tui/TuiBase.h"
#include "MapCfg.h"

class Mapui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Mapui);

	void onLoadScene();
protected:
	CGrid *_grid;
private:
};

#endif