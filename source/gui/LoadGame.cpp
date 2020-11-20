#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "LoadGame.hpp"


namespace GameGUI {

    LoadGame::LoadGame() {
        InitializeComponent();
    }

    void LoadGame::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "LoadGame.xaml");
    }

}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::LoadGame, "GameGUI.LoadGame")