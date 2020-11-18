#include "NsCore/ReflectionImplement.h"
#include "NsCore/ReflectionImplementEnum.h"
#include "NsCore/Log.h"
#include "NsApp/Application.h"
#include "spdlog/spdlog.h"

#include "ViewModel.hpp"
#include "../Game.hpp"
#include "../Audio.hpp"


namespace GameGUI {
    ViewModel::ViewModel() {
        m_newGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnNewGame));
        m_loadGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnLoadGame));
        m_play.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnPlay));
        m_back.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnBack));
        m_game.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnGame));
        m_pause.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnPause));
        m_resumeGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnResumeGame));
        m_saveGame.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnSaveGame));
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

    const NoesisApp::DelegateCommand *ViewModel::GetPause() const {
        return &m_pause;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetResumeGame() const {
        return &m_resumeGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetSaveGame() const {
        return &m_saveGame;
    }

    const NoesisApp::DelegateCommand *ViewModel::GetGame() const {
        return &m_game;
    }

    void ViewModel::OnNewGame(BaseComponent* param) {
        Game::audio->playOne("data/sounds/AudioClick.wav");
        SetState(State::NewGame);
        spdlog::warn("New Game - {}", m_state);
    }

    void ViewModel::OnLoadGame(BaseComponent* param) {
//        SetState(State::LoadGame);
        Game::audio->playOne("data/sounds/AudioClick.wav");
        spdlog::warn("Load Game - {}", m_state);
    }

    void ViewModel::OnPlay(BaseComponent* param) {
        Game::audio->playOne("data/sounds/AudioClick.wav");
        SetState(State::Loading);
        spdlog::warn("Loading - {}", m_state);
    }

    void ViewModel::OnGame(BaseComponent* param) {
        if ( m_state != State::Game && !Game::gamePaused ) {
            SetState(State::Game);
            spdlog::warn("Play Game - {}", m_state);
        }
    }

    void ViewModel::OnPause(Noesis::BaseComponent *param) {
        SetState(State::Pause);
        spdlog::warn("Pause Game - {}", m_state);
        spdlog::warn("Game Paused: {}", Game::gamePaused);
    }

    void ViewModel::OnResumeGame(Noesis::BaseComponent *param) {
        Game::audio->playOne("data/sounds/AudioClick.wav");
        SetState(State::Game);
        spdlog::warn("Play Game - {}", m_state);
        Game::gamePaused = false;
    }

    void ViewModel::OnSaveGame(Noesis::BaseComponent *param) {
        Game::audio->playOne("data/sounds/AudioClick.wav");
        spdlog::warn("Save Game!");
    }

    void ViewModel::OnBack(BaseComponent* param) {
        Game::audio->playOne("data/sounds/AudioClick.wav");
        if ( Game::gameLoaded ) {
            Game::backMainMenu = true;
        }

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
        NsProp("Pause", &ViewModel::GetPause);
        NsProp("ResumeGame", &ViewModel::GetResumeGame);
        NsProp("SaveGame", &ViewModel::GetSaveGame);
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
    NsVal("Pause", GameGUI::State::Pause);
    NsVal("Exit", GameGUI::State::Exit);
}
