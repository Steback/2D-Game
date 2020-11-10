#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "MainMenu.hpp"


namespace GameGUI {
    MainMenu::MainMenu() {
        InitializeComponent();
    }

    void MainMenu::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "MainMenu.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::MainMenu, "GameGUI.MainMenu")