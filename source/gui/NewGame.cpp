#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "NewGame.hpp"


namespace GameGUI {
    NewGame::NewGame() {
        InitializeComponent();
    }

    void NewGame::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "NewGame.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::NewGame, "GameGUI.NewGame")