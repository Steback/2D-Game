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
        m_loadGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnLoadGame));
        m_exit.SetExecuteFunc(MakeDelegate(this, &ViewModel::Exit));

        m_state = State::Main;
    }

    const NoesisApp::DelegateCommand* ViewModel::GetNewGame() const {
        return &m_newGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetLoadGame() const {
        return &m_loadGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetExit() const {
        return &m_exit;
    }

    void ViewModel::OnNewGame(BaseComponent* param) {
        SetState(State::NewGame);
        spdlog::warn("New Game");
    }

    void ViewModel::OnLoadGame(BaseComponent* param) {
        SetState(State::LoadGame);
        spdlog::warn("Load Game");
    }

    void ViewModel::Exit(BaseComponent* param) {
        spdlog::warn("Exit");
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
        NsProp("LoadGame", &ViewModel::GetLoadGame);
        NsProp("Exit", &ViewModel::GetExit);
        NsProp("State", &ViewModel::GetState, &ViewModel::SetState);
    }
}

NS_IMPLEMENT_REFLECTION_ENUM(GameGUI::State, "GameGUI.State"){
    NsVal("Main", GameGUI::State::Main);
    NsVal("NewGame", GameGUI::State::NewGame);
    NsVal("LoadGame", GameGUI::State::LoadGame);
}