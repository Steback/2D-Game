#ifndef NEWGAME_HPP
#define NEWGAME_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class NewGame : public Noesis::UserControl {
        public:
            NewGame();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(NewGame, UserControl)
    };
}


#endif