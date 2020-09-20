#include "pch.h"
#include "PlaceholderPage.h"
#include "PlaceholderPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;

namespace winrt::Codevoid::MusicHall::implementation
{
    PlaceholderPage::PlaceholderPage()
    {
        InitializeComponent();
    }

    void PlaceholderPage::OnNavigatedTo(NavigationEventArgs const& e)
    {
        m_placeholderText = unbox_value_or<hstring>(e.Parameter(), L"Unknown Parameter");
    }

    hstring PlaceholderPage::PlaceholderText()
    {
        return m_placeholderText;
    }
}