#ifndef VIEWMODEL_HPP
#define VIEWMODEL_HPP


#include "NsCore/Noesis.h"
#include "NsCore/Ptr.h"
#include "NsCore/ReflectionDeclare.h"
#include "NsCore/ReflectionDeclareEnum.h"
#include "NsApp/DelegateCommand.h"
#include "NsApp/NotifyPropertyChangedBase.h"

namespace GameGUI {
    enum class State {
        Main,
        NewGame,
        LoadGame,
    };

    class ViewModel final : public NoesisApp::NotifyPropertyChangedBase {
        public:
            ViewModel();

        private:
            const NoesisApp::DelegateCommand* GetNewGame() const;
            const NoesisApp::DelegateCommand* GetLoadGame() const;
            const NoesisApp::DelegateCommand* GetExit() const;

            void OnNewGame(BaseComponent* param);
            void OnLoadGame(BaseComponent* param);
            void Exit(BaseComponent* param);

            State GetState() const;
            void SetState(State value);

        private:
            NoesisApp::DelegateCommand m_newGame;
            NoesisApp::DelegateCommand m_loadGame;
            NoesisApp::DelegateCommand m_exit;

        private:
            State m_state;

            NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
    };

}

NS_DECLARE_REFLECTION_ENUM(GameGUI::State)


#endif