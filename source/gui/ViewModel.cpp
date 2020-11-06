#include "NsCore/ReflectionImplement.h"
#include "NsCore/ReflectionImplementEnum.h"
#include "NsCore/Log.h"
#include "NsGui/UIElement.h"
#include "NsApp/Application.h"
#include "spdlog/spdlog.h"

#include "ViewModel.hpp"


namespace GameGUI {
    ViewModel::ViewModel() {
        m_newGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnNewGame));

        m_state = State::Main;
    }

    const NoesisApp::DelegateCommand* ViewModel::GetNewGame() const {
        return &m_newGame;
    }

    void ViewModel::OnNewGame(BaseComponent*) {
        SetState(State::Start);
        spdlog::warn("New Game");
    }

    State ViewModel::GetState() const {
        return m_state;
    }

    void ViewModel::SetState(State value) {
        if (m_state != value) {
            m_state = value;
            OnPropertyChanged("State");
        }
    }

    NS_BEGIN_COLD_REGION

    NS_IMPLEMENT_REFLECTION(ViewModel) {
        NsProp("NewGame", &ViewModel::GetNewGame);
        NsProp("State", &ViewModel::GetState, &ViewModel::SetState);
    }

}

NS_IMPLEMENT_REFLECTION_ENUM(GameGUI::State, "GameGUI.State"){
    NsVal("Main", GameGUI::State::Main);
    NsVal("Start", GameGUI::State::Start);
    NsVal("Settings", GameGUI::State::Settings);
}