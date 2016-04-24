//
//  SinglePost.hpp
//  nasa
//
//  Created by 张仁龙 on 4/23/16.
//
//

#ifndef SinglePost_h
#define SinglePost_h

#include <stdio.h>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class SinglePost{
private:
    Layer *layer;
    Sprite *newsPic;
    Label *newIntro;
    Sprite *divideLine;
    
public:
    
    SinglePost(Layer *_layer);
   
};

#endif /* SinglePost_hpp */
