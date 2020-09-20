#pragma once

#include "PlaceholderPage.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct PlaceholderPage : PlaceholderPageT<PlaceholderPage>
    {
        PlaceholderPage();
        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        winrt::hstring PlaceholderText();

    private:
        winrt::hstring m_placeholderText;
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct PlaceholderPage : PlaceholderPageT<PlaceholderPage, implementation::PlaceholderPage>
    {
    };
}
