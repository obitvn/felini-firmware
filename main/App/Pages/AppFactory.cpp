/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "AppFactory.hpp"
#include "_Template/Template.h"
#include "StartUp/StartUp.h"
#include "MenuList/MenuList.h"
#include "Dialplate/Dialplate.h"
#include "IICDiscovery/IICDiscovery.h"
#include "Pages/AppInfos/AppInfos.h"
#include "Pages/PowerSupply/PowerSupply.h"
#include "Pages/ServoCtrl/ServoCtrl.h"
#include "Pages/AnalogViewer/AnalogViewer.h"
#include "Pages/ColorWheel/ColorWheel.h"

#define APP_CLASS_MATCH(className)\
do{\
    if (strcmp(name, #className) == 0)\
    {\
        return new Page::className;\
    }\
}while(0)

PageBase* AppFactory::CreatePage(const char* name)
{
    APP_CLASS_MATCH(Template);
    APP_CLASS_MATCH(Startup);
    APP_CLASS_MATCH(MenuList);
    APP_CLASS_MATCH(Dialplate);
    APP_CLASS_MATCH(AppInfos);
    APP_CLASS_MATCH(IICDiscovery); //nhớ include .h bên trên
    APP_CLASS_MATCH(PowerSupply);
    APP_CLASS_MATCH(ServoCtrl);
    APP_CLASS_MATCH(AnalogViewer);
    APP_CLASS_MATCH(ColorWheel);

    return nullptr;
}
