#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Config.h"
#include <string>
#include "network/HttpClient.h"
#include "spine/Json.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;
using namespace network;

class Home : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Home);
    
    Button *learningButton;
    Button *plusButton;
    Button *eventButton;

private:
    Size visibleSize;
    Vec2 origin;
    float centerX;
    float centerY;
    int selectedButton;
    int seletedMenu;
    
    //event board
    Sprite *eventBack;
    Sprite *topBarBack;
    Button *topBarMenu;
    
    //learn board;
    Button *learnBack;
    
    //news
    ScrollView *newsBoard;
    ScrollView *postBoard;
    
    Label *tips;
    
    Sprite *teachBack;
    
    //post
    int login;
    Sprite *loginBack;
    Button *postDialog;
    
    Button *messageBack;
    Button *sendButton;
    
    ScrollView *teachScrollBack;
    Sprite *quiz1;
    void initialSetting();
    void createBottomButtonGroup();
    
    void showLearnBoard();
    void showPostBoard();
    void showEventBoard();
    
    void switchToNewsOrSquare();
    void showNewsPage();
    void showSquarePage();
    
    void getNewsFromServer();
    void onPostInfoLoad(HttpClient *sender, HttpResponse *response);
    
    void showTips(string message,float size, float duration);
    void showLoginDialog();
    void createPostDialog();
    
    void showTeachDialog();
};

#endif // __HELLOWORLD_SCENE_H__
