#ifndef INC_2D_GAME_GAMEVIEW_HPP
#define INC_2D_GAME_GAMEVIEW_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class GameView : public Noesis::UserControl {
        public:
            GameView();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(GameView, UserControl)
    };
}

#endif
