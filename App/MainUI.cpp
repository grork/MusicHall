#include "pch.h"
#include "MainUI.h"
#include "MainUI.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

namespace winrt::Codevoid::MusicHall::implementation
{
    MainUI::MainUI()
    {
        InitializeComponent();
    }

    void MainUI::Navigate(TypeName const& pageType, IInspectable const& parameter)
    {
        this->NavigationFrame().Navigate(pageType, parameter);
    }
}
