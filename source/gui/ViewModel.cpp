#include "NsCore/ReflectionImplement.h"
#include "NsCore/ReflectionImplementEnum.h"
#include "NsCore/Log.h"
#include "NsGui/UIElement.h"
#include "NsApp/Application.h"
#include "spdlog/spdlog.h"

#include "ViewModel.hpp"
#include "../Game.hpp"
#include "../Window.hpp"


namespace GameGUI {
    ViewModel::ViewModel() {
        m_newGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnNewGame));
        m_loadGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnLoadGame));
        m_play.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnPlay));
        m_back.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnBack));
        m_exit.SetExecuteFunc(MakeDelegate(this, &ViewModel::Exit));

        m_state = State::MainMenu;
    }

    const NoesisApp::DelegateCommand* ViewModel::GetNewGame() const {
        return &m_newGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetLoadGame() const {
        return &m_loadGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetPlay() const {
        return &m_play;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetBack() const {
        return &m_back;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetExit() const {
        return &m_exit;
    }

    void ViewModel::OnNewGame(BaseComponent* param) {
        SetState(State::NewGame);
        spdlog::warn("New Game - {}", m_state);
    }

    void ViewModel::OnLoadGame(BaseComponent* param) {
        SetState(State::LoadGame);
        spdlog::warn("Load Game - {}", m_state);
    }

    void ViewModel::OnPlay(BaseComponent* param) {
        SetState(State::Loading);
        spdlog::warn("Play Game - {}", m_state);
    }

    void ViewModel::OnBack(BaseComponent* param) {
        SetState(State::MainMenu);
        spdlog::warn("Back Game - {}", m_state);
    }

    void ViewModel::Exit(BaseComponent* param) {
        SetState(State::Exit);
        Game::window->windowShouldClose(true);
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
        NsProp("Play", &ViewModel::GetPlay);
        NsProp("Back", &ViewModel::GetBack);
        NsProp("Exit", &ViewModel::GetExit);
        NsProp("State", &ViewModel::GetState, &ViewModel::SetState);
    }
}

NS_IMPLEMENT_REFLECTION_ENUM(GameGUI::State, "GameGUI.State"){
    NsVal("MainMenu", GameGUI::State::MainMenu);
    NsVal("NewGame", GameGUI::State::NewGame);
    NsVal("LoadGame", GameGUI::State::LoadGame);
    NsVal("Loading", GameGUI::State::Loading);
    NsVal("Game", GameGUI::State::Game);
    NsVal("Exit", GameGUI::State::Exit);
}