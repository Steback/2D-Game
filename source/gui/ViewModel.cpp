#include "NsCore/ReflectionImplement.h"
#include "NsCore/ReflectionImplementEnum.h"
#include "NsCore/Log.h"
#include "NsApp/Application.h"
#include "spdlog/spdlog.h"

#include "ViewModel.hpp"
#include "../Game.hpp"


namespace GameGUI {
    ViewModel::ViewModel() {
        m_newGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnNewGame));
        m_loadGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnLoadGame));
        m_play.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnPlay));
        m_back.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnBack));
        m_game.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnGame));
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

    const NoesisApp::DelegateCommand *ViewModel::GetGame() const {
        return &m_game;
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
        spdlog::warn("Loading - {}", m_state);
    }

    void ViewModel::OnGame(BaseComponent* param) {
        SetState(State::Game);
        spdlog::warn("Play Game - {}", m_state);
    }

    void ViewModel::OnBack(BaseComponent* param) {
        SetState(State::MainMenu);
        spdlog::warn("Back Game - {}", m_state);
    }

    void ViewModel::Exit(BaseComponent* param) {
        SetState(State::Exit);
    }

    State ViewModel::GetState() const {
        return m_state;
    }

    void ViewModel::SetState(State value) {
        if (m_state != value) {
            m_state = value;
            Game::state_ = m_state;
            OnPropertyChanged("State");
        }
    }

    NS_BEGIN_COLD_REGION

    NS_IMPLEMENT_REFLECTION(ViewModel) {
        NsProp("NewGame", &ViewModel::GetNewGame);
        NsProp("LoadGame", &ViewModel::GetLoadGame);
        NsProp("Play", &ViewModel::GetPlay);
        NsProp("Back", &ViewModel::GetBack);
        NsProp("Game", &ViewModel::GetGame);
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