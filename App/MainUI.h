#pragma once

#include "MainUI.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct MainUI : MainUIT<MainUI>
    {
        MainUI();

        void Navigate(Windows::UI::Xaml::Interop::TypeName const& pageType, Windows::Foundation::IInspectable const& parameter);
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct MainUI : MainUIT<MainUI, implementation::MainUI>
    {
    };
}
