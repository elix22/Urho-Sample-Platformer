#include "gs_pause.h"
#include "gs_playing.h"
#include "gs_main_menu.h"

using namespace Urho3D;

gs_pause::gs_pause() : game_state()
{
    globals::instance()->scene->SetUpdateEnabled(false);

    Window* window_=new Window(globals::instance()->context);
    gui_elements.push_back(window_);
    globals::instance()->ui_root->AddChild(window_);

    window_->SetMinSize(250,400);
    window_->SetLayout(LM_VERTICAL,6,IntRect(6,6,6,6));
    window_->SetAlignment(HA_CENTER,VA_CENTER);
    window_->SetName("Window");
    window_->SetColor(Color(.0,.15,.3,.5));
/*
    UIElement* titleBar=new UIElement(globals::instance()->context);
    titleBar->SetMinSize(0,24);
    titleBar->SetVerticalAlignment(VA_TOP);
    titleBar->SetLayoutMode(LM_HORIZONTAL);

    Text* windowTitle=new Text(globals::instance()->context);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetText("Hello GUI!");
    windowTitle->SetStyleAuto();
    titleBar->AddChild(windowTitle);

    Button* buttonClose=new Button(globals::instance()->context);
    buttonClose->SetName("CloseButton");
    buttonClose->SetStyle("CloseButton");
    titleBar->AddChild(buttonClose);

    window_->AddChild(titleBar);*/
    window_->SetStyleAuto();

    {
        BorderImage* button = new BorderImage(globals::instance()->context);
        button->SetName("Button");
        button->SetMinHeight(50);
        button->SetStyle("Window");
        button->SetOpacity(0.75);
        {
            Text* t = new Text(globals::instance()->context);
            t->SetFont(globals::instance()->cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"),20);
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_CENTER);
            t->SetName("Text");
            t->SetText("Pause");
            //button->AddChild(t);
            t->SetStyle("Text");
            t->SetMinHeight(VA_CENTER);
            button->AddChild(t);
        }
        window_->AddChild(button);
    }
    {
        Button* button = new Button(globals::instance()->context);
        button->SetName("Button");
        button->SetMinHeight(50);
        button->SetStyleAuto();
        button->SetOpacity(0.75);
        {
            Text* t = new Text(globals::instance()->context);
            t->SetFont(globals::instance()->cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"),16);
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_CENTER);
            t->SetName("Text");
            t->SetText("Resume game");
            //button->AddChild(t);
            t->SetStyle("Text");
            t->SetMinHeight(VA_CENTER);
            button->AddChild(t);

        }
        window_->AddChild(button);
        SubscribeToEvent(button,E_RELEASED,HANDLER(gs_pause,HandleResumePressed));
    }
    {
        Button* button = new Button(globals::instance()->context);
        button->SetName("Button");
        button->SetMinHeight(50);
        button->SetStyleAuto();
        button->SetOpacity(0.75);
        {
            Text* t = new Text(globals::instance()->context);
            t->SetFont(globals::instance()->cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"),16);
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_CENTER);
            t->SetName("Text");
            t->SetText("Exit to main menu");
            //button->AddChild(t);
            t->SetStyle("Text");
            t->SetMinHeight(VA_CENTER);
            button->AddChild(t);
        }
        window_->AddChild(button);
        SubscribeToEvent(button,E_RELEASED,HANDLER(gs_pause,HandleMainMenuPressed));
    }
    {
        Button* button = new Button(globals::instance()->context);
        button->SetName("Button");
        button->SetMinHeight(50);
        button->SetStyleAuto();
        button->SetOpacity(0.75);
        {
            Text* t = new Text(globals::instance()->context);
            t->SetFont(globals::instance()->cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"),16);
            t->SetHorizontalAlignment(HA_CENTER);
            t->SetVerticalAlignment(VA_CENTER);
            t->SetName("Text");
            t->SetText("Quit the game");
            //button->AddChild(t);
            t->SetStyle("Text");
            t->SetMinHeight(VA_CENTER);
            button->AddChild(t);
        }
        window_->AddChild(button);
        SubscribeToEvent(button,E_RELEASED,HANDLER(gs_pause,HandleQuitPressed));
    }

    GetSubsystem<Input>()->SetMouseVisible(true);
    GetSubsystem<Input>()->SetMouseGrabbed(false);

    SubscribeToEvent(E_UPDATE,HANDLER(gs_pause,update));
    SubscribeToEvent(E_KEYDOWN,HANDLER(gs_pause,HandleKeyDown));
//    SubscribeToEvent(buttonClose,E_RELEASED,HANDLER(gs_pause,HandleResumePressed));
}

gs_pause::~gs_pause()
{
    globals::instance()->scene->SetUpdateEnabled(true);
}

void gs_pause::update(StringHash eventType,VariantMap& eventData)
{
}

void gs_pause::HandleResumePressed(Urho3D::StringHash eventType,Urho3D::VariantMap& eventData)
{
    GetSubsystem<Input>()->SetMouseVisible(false);
    GetSubsystem<Input>()->SetMouseGrabbed(true);
    globals::instance()->game_states.resize(1);
}

void gs_pause::HandleMainMenuPressed(Urho3D::StringHash eventType,Urho3D::VariantMap& eventData)
{
    globals::instance()->game_states[0].reset(new gs_main_menu);
    globals::instance()->game_states.resize(1);
}

void gs_pause::HandleKeyDown(StringHash eventType,VariantMap& eventData)
{
    using namespace KeyDown;
    int key=eventData[P_KEY].GetInt();
    if(key==KEY_ESC)
    {
        GetSubsystem<Input>()->SetMouseVisible(false);
        GetSubsystem<Input>()->SetMouseGrabbed(true);
        globals::instance()->game_states.resize(1);
    }
}
