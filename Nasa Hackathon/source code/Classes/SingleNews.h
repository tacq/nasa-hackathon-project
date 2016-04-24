//
//  SingleNews.hpp
//  nasa
//
//  Created by 张仁龙 on 4/23/16.
//
//

#ifndef SingleNews_h
#define SingleNews_h

#include <stdio.h>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class SingleNews{
private:
    Layer *layer;
    Sprite *newsPic;
    Label *newIntro;
    Sprite *divideLine;

public:
    
    SingleNews(Layer *_layer);
    
    
    
    
};

#endif /* SingleNews_hpp */
