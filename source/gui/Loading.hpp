#ifndef INC_2D_GAME_LOADING_HPP
#define INC_2D_GAME_LOADING_HPP


#include "NsCore/Noesis.h"
#include "NsGui/UserControl.h"


namespace GameGUI {
    class Loading : public Noesis::UserControl {
        public:
            Loading();

        private:
            void InitializeComponent();

            NS_DECLARE_REFLECTION(Loading, UserControl)
    };
}

#endif
