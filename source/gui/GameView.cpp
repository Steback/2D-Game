#include "NsCore/ReflectionImplementEmpty.h"
#include "NsGui/IntegrationAPI.h"

#include "GameView.hpp"


namespace GameGUI {
    GameView::GameView() {
        InitializeComponent();
    }

    void GameView::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "GameView.xaml");
    }
}

NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(GameGUI::GameView, "GameGUI.GameView")
