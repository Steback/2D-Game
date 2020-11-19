#ifndef VIEWMODEL_HPP
#define VIEWMODEL_HPP


#include "NsGui/DependencyProperty.h"
#include "NsCore/Noesis.h"
#include "NsCore/Ptr.h"
#include "NsCore/ReflectionDeclare.h"
#include "NsCore/ReflectionDeclareEnum.h"
#include "NsApp/DelegateCommand.h"
#include "NsApp/NotifyPropertyChangedBase.h"


namespace GameGUI {
    enum class State {
        MainMenu,
        NewGame,
        LoadGame,
        Loading,
        Game,
        Pause,
        EndGame,
        Exit,
    };

    class ViewModel final : public NoesisApp::NotifyPropertyChangedBase {
        public:
            ViewModel();
            void SetState(State value);
            void SetEndGameText(const char* text);

        private:
            const NoesisApp::DelegateCommand* GetNewGame() const;
            const NoesisApp::DelegateCommand* GetLoadGame() const;
            const NoesisApp::DelegateCommand* GetBack() const;
            const NoesisApp::DelegateCommand* GetPlay() const;
            const NoesisApp::DelegateCommand* GetGame() const;
            const NoesisApp::DelegateCommand* GetPause() const;
            const NoesisApp::DelegateCommand* GetResumeGame() const;
            const NoesisApp::DelegateCommand* GetSaveGame() const;
            const NoesisApp::DelegateCommand* GetExit() const;

            void OnNewGame(BaseComponent* param);
            void OnLoadGame(BaseComponent* param);
            void OnBack(BaseComponent* param);
            void OnPlay(BaseComponent* param);
            void OnGame(BaseComponent* param);
            void OnPause(BaseComponent* param);
            void OnResumeGame(BaseComponent* param);
            void OnSaveGame(BaseComponent* param);
            void Exit(BaseComponent* param);

            const char* GetEndGameText() const;
            State GetState() const;

        private:
            NoesisApp::DelegateCommand m_newGame;
            NoesisApp::DelegateCommand m_loadGame;
            NoesisApp::DelegateCommand m_play;
            NoesisApp::DelegateCommand m_back;
            NoesisApp::DelegateCommand m_game;
            NoesisApp::DelegateCommand m_pause;
            NoesisApp::DelegateCommand m_resumeGame;
            NoesisApp::DelegateCommand m_saveGame;
            NoesisApp::DelegateCommand m_exit;

        private:
            State m_state;
            Noesis::String endGameText;

            NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
    };

}

NS_DECLARE_REFLECTION_ENUM(GameGUI::State)


#endif