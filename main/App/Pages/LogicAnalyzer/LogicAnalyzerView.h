#ifndef __LogicAnalyzer_VIEW_H
#define __LogicAnalyzer_VIEW_H

#include "../Page.h"

namespace Page
{

class LogicAnalyzerView
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
