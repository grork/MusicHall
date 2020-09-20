#include "pch.h"
#include "AlbumControl.h"
#include "AlbumControl.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Codevoid::MusicHall::implementation
{
    DependencyProperty AlbumControl::s_albumNameProperty =
        DependencyProperty::Register(
            L"AlbumName",
            xaml_typename<hstring>(),
            xaml_typename<MusicHall::AlbumControl>(),
            PropertyMetadata({ box_value(L"") })
        );
    hstring AlbumControl::AlbumName()
    {
        return unbox_value<winrt::hstring>(GetValue(s_albumNameProperty));
    }
    void AlbumControl::AlbumName(hstring const& value)
    {
        SetValue(s_albumNameProperty, box_value(value));
    }

    DependencyProperty AlbumControl::AlbumNameProperty()
    {
        return s_albumNameProperty;
    }
}
