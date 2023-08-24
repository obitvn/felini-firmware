#ifndef __PowerSupply_VIEW_H
#define __PowerSupply_VIEW_H

#include "../Page.h"

namespace Page
{

class PowerSupplyView
{
public:
    void Create(lv_obj_t* root);
    void Delete();
    void ExitEditLabel(lv_obj_t *label);
    void EditLabel(lv_obj_t *label, float value);

public:


public:

private:
};

}

#endif // !__VIEW_H
