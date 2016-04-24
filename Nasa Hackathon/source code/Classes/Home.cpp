#include "Home.h"

USING_NS_CC;


Scene* Home::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Home::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Home::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    centerX = visibleSize.width/2 + origin.x;
    centerY = visibleSize.height/2 + origin.x;
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    initialSetting();
    createBottomButtonGroup();
    
    return true;
}

void Home::initialSetting(){
    login = 0;
    selectedButton = LEARN_SLECTED;
}

void Home::createBottomButtonGroup(){
   
    learningButton = Button::create("learning_button_selected.png");
    learningButton->setPosition(Vec2(80+learningButton->getBoundingBox().size.width/2,learningButton->getBoundingBox().size.height/2+25));

    
    plusButton = Button::create("plus_button.png");
    plusButton->setPosition(Vec2(centerX,plusButton->getBoundingBox().size.height/2+25));
    
    eventButton = Button::create("event_button.png");
    eventButton->setPosition(Vec2( 50+centerX + eventButton->getBoundingBox().size.width/2 + plusButton->getBoundingBox().size.width/2,eventButton->getBoundingBox().size.height/2+25));

    addChild(eventButton,TOP_LEVEL);
    addChild(plusButton,TOP_LEVEL);
    addChild(learningButton,TOP_LEVEL);
    showLearnBoard();
    
    learningButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                showLearnBoard();
                break;
            default:
                break;
        }
    });
    
    plusButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                showPostBoard();
                break;
            default:
                break;
        }
    });
    
    eventButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                showEventBoard();
                break;
            default:
                break;
        }
    });
}

void Home::createPostDialog(){
    if (postDialog != nullptr) {
        postDialog->runAction(MoveTo::create(0.3, Vec2(centerX,1.1*centerY)));
    }else{
        postDialog = Button::create("post_dialog.png","post_dialog.png");
        postDialog->setPosition(Vec2(centerX,3*centerY));
        addChild(postDialog,TOP_LEVEL);
        postDialog->runAction(MoveTo::create(0.3, Vec2(centerX,1.1*centerY)));
        postDialog->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                {
                    postDialog->runAction(MoveTo::create(0.3, Vec2(centerX,3*centerY)));
                }
                    break;
                default:
                    break;
            }
        });
    }
    

}

void Home::showPostBoard(){
    if(login == 0){
        showLoginDialog();
    } else{
        createPostDialog();
    }
};

void Home::showLoginDialog(){
    loginBack = Sprite::create("login_back.png");
    loginBack->setPosition(Vec2(centerX,3*centerY));
    
    
    auto facebookLogin = Button::create("facebook_login.png");
    facebookLogin->setPosition(Vec2(1.03*centerX,0.5*centerY));
    
    auto googleLogin = Button::create("google_login.png");
    googleLogin->setPosition(Vec2(1.03*centerX,0.25*centerY));
    
    loginBack->addChild(facebookLogin);
    loginBack->addChild(googleLogin);
    addChild(loginBack,TOP_LEVEL);
    loginBack->runAction(MoveTo::create(0.3, Vec2(centerX,1.2*centerY)));
    facebookLogin->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto animationDone = CallFunc::create( [this]() {
                    createPostDialog();
                });

                loginBack->runAction(Sequence::create(MoveTo::create(0.3, Vec2(centerX,3*centerY)),animationDone,NULL));
                login = 1;
                
            }
                break;
            default:
                break;
        }
    });
    
    googleLogin->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto animationDone = CallFunc::create( [this]() {
                    createPostDialog();
                });
                
                loginBack->runAction(Sequence::create(MoveTo::create(0.3, Vec2(centerX,3*centerY)),animationDone,NULL));
                login = 1;
            }
                break;
            default:
                break;
        }
    });

}

void Home::showLearnBoard(){
    if(selectedButton != LEARN_SLECTED){
        selectedButton = LEARN_SLECTED;
        learningButton->loadTextureNormal("learning_button_selected.png");
        eventButton->loadTextureNormal("event_button.png");
        if (eventBack!=nullptr) {
            eventBack->setVisible(false);
        }
    }
    
    if(learnBack == nullptr){
        learnBack = Button::create("space.png","space.png");
        learnBack->setPosition(Vec2(centerX,1.1*centerY));
        
        auto questionMark = Button::create("help.png");
        questionMark->setPosition(Vec2(0.25*centerX,1.65*centerY));
        
        messageBack = Button::create("talk.png");
        messageBack->setPosition(Vec2(1.2*centerX,1.65*centerY));

        sendButton = Button::create("send.png");
        sendButton->setPosition(Vec2(1.7*centerX,1.65*centerY));
        
        
        learnBack->addChild(questionMark,2);
        learnBack->addChild(messageBack,2);
        learnBack->addChild(sendButton,2);
        
        messageBack->setVisible(false);
        sendButton->setVisible(false);
        questionMark->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    if(messageBack->isVisible()){
                        messageBack->setVisible(false);
                        sendButton->setVisible(false);
                    } else {
                        messageBack->setVisible(true);
                        sendButton->setVisible(true);
                    }
                    break;
                default:
                    break;
            }
        });
        
        addChild(learnBack,BOTTOM_LEVEL);
        learnBack->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    showTeachDialog();
                    break;
                default:
                    break;
            }
        });

    } else{
        learnBack->setVisible(true);
    }
};

void Home::showTeachDialog(){
    if(teachBack ==nullptr){
        
        teachBack = Sprite::create("dialog_back.png");
        teachBack->setPosition(Vec2(centerX,3*centerY));
        learnBack->addChild(teachBack);
        teachBack->runAction(MoveTo::create(0.3, Vec2(centerX,0.8*centerY)));
        auto closeButton = Button::create("close.png");
        closeButton->setPosition(Vec2(1.87*centerX,1.5*centerY));
        closeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    teachBack->runAction(MoveTo::create(0.3, Vec2(centerX,3*centerY)));
                    break;
                default:
                    break;
            }
        });
        
        
        
        auto quizeButton = Button::create("quiz_button.png");
        quizeButton->setPosition(Vec2(centerX,0.15*centerY));
        teachBack->addChild(quizeButton);
        
        teachScrollBack = ScrollView::create();
        teachScrollBack->setAnchorPoint(Vec2(0.5,0.5));
        teachScrollBack->setDirection(ScrollView::Direction::VERTICAL);
        teachScrollBack->setBounceEnabled(true);
        teachScrollBack->setEnabled(true);
        teachScrollBack->setContentSize(Size(2*centerX,1.2*centerY));
        teachScrollBack->setPosition(Point(centerX,0.85*centerY));
        
        auto earthInfo0 = Sprite::create("earth_0.png");
        auto earthInfo1 = Sprite::create("earth_1.png");
        auto earthInfo2 = Sprite::create("earth_2.png");
        
        
        float totalHeihgt = earthInfo0->getContentSize().height+earthInfo1->getContentSize().height +earthInfo2->getContentSize().height;
        
        earthInfo0->setPosition(Vec2(centerX,totalHeihgt-earthInfo0->getContentSize().height/2));
        
        earthInfo1->setPosition(Vec2(centerX,totalHeihgt-earthInfo0->getContentSize().height-earthInfo1->getContentSize().height/2));
        
       
        earthInfo2->setPosition(Vec2(centerX,earthInfo2->getContentSize().height/2));
        
        teachScrollBack->setInnerContainerSize(Size(centerX,totalHeihgt));
        teachScrollBack->setVisible(true);
        if (quiz1!=nullptr) {
            quiz1->setVisible(false);
        }
        teachBack->addChild(teachScrollBack);
        teachScrollBack->addChild(earthInfo0);
        teachScrollBack->addChild(earthInfo1);
        teachScrollBack->addChild(earthInfo2);

        teachBack->addChild(closeButton);
        quizeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                {
                    teachScrollBack->setVisible(false);
                    quiz1 = Sprite::create("q1.png");
                    quiz1->setPosition(Vec2(centerX,0.78*centerY));
                    teachBack->addChild(quiz1);
                }
                    break;
                default:
                    break;
            }
        });
    } else {
        teachBack->runAction(MoveTo::create(0.3, Vec2(centerX,0.8*centerY)));
        if(quiz1!=nullptr){
            quiz1->setVisible(false);
        }
        teachScrollBack->setVisible(true);

    }
}


void Home::showEventBoard(){
    if(selectedButton != EVENT_SLECTED){
        selectedButton = EVENT_SLECTED;
        learningButton->loadTextureNormal("learning_button.png");
        eventButton->loadTextureNormal("event_button_selected.png");
        learnBack->setVisible(false);
    }
    
    if(eventBack == NULL){
        eventBack = Sprite::create("black_back.png");
        eventBack->setPosition(Vec2(centerX,centerY));
        
        topBarBack = Sprite::create("event_top_back_bar.png");
        topBarBack->setPosition(Vec2(centerX,2*centerY-topBarBack->getBoundingBox().size.height/2));
        
        seletedMenu = NEWS_SLECTED;
        topBarMenu = Button::create("news.png");
        topBarMenu->setPosition(Vec2(centerX, 2*centerY-topBarBack->getBoundingBox().size.height/2));
        
        getNewsFromServer();
        
        topBarMenu->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    switchToNewsOrSquare();
                    break;
                default:
                    break;
            }
        });

        
        eventBack->addChild(topBarBack);
        eventBack->addChild(topBarMenu);
        
        addChild(eventBack,BOTTOM_LEVEL);
        showNewsPage();

    } else {
        eventBack->setVisible(true);
    }
};

void Home::getNewsFromServer(){
//    HttpRequest *httpRequest = new HttpRequest();
//    httpRequest->setRequestType(HttpRequest::Type::GET);
//    string basic(BASIC_URL);
//    string url = basic + "getNasaPostNews?";
//    httpRequest->setUrl(url.c_str());
//    httpRequest->setResponseCallback(CC_CALLBACK_2(Home::onPostInfoLoad, this));
//    HttpClient::getInstance()->send(httpRequest);
//    httpRequest->release();
}

void onPostInfoLoad(HttpClient *sender, HttpResponse *response){
    if (response && response->getResponseCode() == 200 && response->getResponseData()) {
        // need to store nickname and id
        vector<char> * buffer = response->getResponseData();
        char * concatenated = (char *) malloc(buffer->size() + 1);
        std::string s2(buffer->begin(), buffer->end());
        strcpy(concatenated, s2.c_str());
        // JSON Parser. Include "spine/Json.h".
        Json * json = Json_create(concatenated);
        int code = Json_getInt(json, "code", 0);
        int value = Json_getInt(json, "value", -1);
        // Delete the JSON object
        Json_dispose(json);
        
        if (code == 200) {
            
        }
    } else {
        //showTips("Network error. Retry next time.",0.1f,3.0f);
    }
}
void Home::switchToNewsOrSquare(){
    if (seletedMenu == NEWS_SLECTED) {
        seletedMenu = SQUARE_SLECTED;
        topBarMenu->loadTextureNormal("square.png");
        showSquarePage();
    } else {
        seletedMenu = NEWS_SLECTED;
        topBarMenu->loadTextureNormal("news.png");
        showNewsPage();
    }
}

void Home::showNewsPage(){
    if (postBoard!=nullptr) {
        postBoard->setVisible(false);
    }
    if(newsBoard ==nullptr){
        newsBoard = ScrollView::create();
        newsBoard->setAnchorPoint(Vec2(0.5,0.5));
        newsBoard->setDirection(ScrollView::Direction::VERTICAL);
        newsBoard->setBounceEnabled(true);
        newsBoard->setEnabled(true);
        newsBoard->setContentSize(Size(2*centerX,1.65*centerY));
        newsBoard->setPosition(Point(centerX,0.98*centerY));
        
        auto postNews1 = Sprite::create("post_news1.png");
        auto postNews2 = Sprite::create("post_news2.png");
        auto postNews3 = Sprite::create("post_news3.png");
        
        float totalHeight =postNews1->getContentSize().height+
        postNews2->getContentSize().height+
        postNews3->getContentSize().height;
        newsBoard->setInnerContainerSize(Size(centerX,totalHeight));

        postNews1->setPosition(Vec2(centerX,totalHeight-postNews1->getContentSize().height/2));
        postNews2->setPosition(Vec2(centerX,totalHeight-postNews1->getContentSize().height-postNews2->getContentSize().height/2));
        postNews3->setPosition(Vec2(centerX,postNews3->getContentSize().height/2));
        
        newsBoard->addChild(postNews1);
        newsBoard->addChild(postNews2);
        newsBoard->addChild(postNews3);
        eventBack->addChild(newsBoard);
    } else {
        newsBoard->setVisible(true);
    }
}

void Home::showSquarePage(){
    if(newsBoard!=nullptr){
        newsBoard->setVisible(false);
    }
    
    if(postBoard ==nullptr){
        postBoard = ScrollView::create();
        postBoard->setAnchorPoint(Vec2(0.5,0.5));
        postBoard->setDirection(ScrollView::Direction::VERTICAL);
        postBoard->setBounceEnabled(true);
        postBoard->setEnabled(true);
        postBoard->setContentSize(Size(2*centerX,1.65*centerY));
        postBoard->setPosition(Point(centerX,0.98*centerY));
        
        auto userPost1 = Sprite::create("user_post1.png");
        auto userPost2 = Sprite::create("user_post2.png");
        
        float totalHeight =userPost1->getContentSize().height+
        userPost2->getContentSize().height;
        
        postBoard->setInnerContainerSize(Size(centerX,totalHeight));
        
        userPost1->setPosition(Vec2(centerX,totalHeight-userPost1->getContentSize().height/2));
        userPost2->setPosition(Vec2(centerX,userPost2->getContentSize().height/2));
        
        postBoard->addChild(userPost1);
        postBoard->addChild(userPost2);
        eventBack-> addChild(postBoard);
    } else {
        postBoard->setVisible(true);
    }

}

void Home::showTips(string message,float size, float duration){
    
    tips = Label::createWithTTF(message, "fonts/alex_murphy_solid.ttf", size*centerY);
    
    tips->setPosition(centerX,0.5*centerY);
    addChild(tips);
    auto animationDone = CallFunc::create( [this]() {
        removeChild(tips);
    });
    
    tips->runAction(Sequence::create(FadeOut::create(duration),animationDone, NULL) );
}



