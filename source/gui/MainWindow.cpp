#include "NsGui/IntegrationAPI.h"
#include "NsCore/ReflectionImplementEmpty.h"

#include "MainWindow.hpp"


namespace GameGUI {
    MainWindow::MainWindow() {
        Loaded() += MakeDelegate(this, &MainWindow::OnLoaded);
        InitializeComponent();
    }

    void MainWindow::InitializeComponent() {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    void MainWindow::OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&) {
        view = Noesis::MakePtr<ViewModel>();
        SetDataContext(view);
    }

    Noesis::Ptr<ViewModel> MainWindow::view;

    NS_BEGIN_COLD_REGION

    NS_IMPLEMENT_REFLECTION_(GameGUI::MainWindow, "GameGUI.MainWindow")
}