#ifndef __DAPLink_VIEW_H
#define __DAPLink_VIEW_H

#include "../Page.h"

namespace Page
{

class DAPLinkView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    lv_obj_t *switch_cont;

public:

private:
};

}

#endif // !__VIEW_H
