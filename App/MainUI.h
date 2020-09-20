#pragma once

#include "MainUI.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct MainUI : MainUIT<MainUI>
    {
        MainUI();

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct MainUI : MainUIT<MainUI, implementation::MainUI>
    {
    };
}
