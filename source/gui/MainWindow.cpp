#include "NsGui/IntegrationAPI.h"
#include "NsCore/ReflectionImplementEmpty.h"

#include "MainWindow.hpp"
#include "ViewModel.hpp"


namespace GameGUI {
    MainWindow::MainWindow() {
        Loaded() += MakeDelegate(this, &MainWindow::OnLoaded);
        InitializeComponent();
    }

    void MainWindow::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    void MainWindow::OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&) {
        SetDataContext(Noesis::MakePtr<ViewModel>());
    }

    NS_BEGIN_COLD_REGION

    NS_IMPLEMENT_REFLECTION_(GameGUI::MainWindow, "GameGUI.MainWindow")
}