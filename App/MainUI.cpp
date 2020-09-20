#include "pch.h"
#include "MainUI.h"
#include "MainUI.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Codevoid::MusicHall::implementation
{
    MainUI::MainUI()
    {
        InitializeComponent();
    }

    void MainUI::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Temporary Placeholder"));
    }
}
