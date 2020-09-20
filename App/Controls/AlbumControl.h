#pragma once

#include "AlbumControl.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    /// <summary>
    /// Displays supplied information in a way that resembles a real world album
    /// </summary>
    struct AlbumControl : AlbumControlT<AlbumControl>
    {
        AlbumControl()
        { DefaultStyleKey(winrt::box_value(L"Codevoid.MusicHall.AlbumControl")); }

        winrt::hstring AlbumName();
        void AlbumName(winrt::hstring const& value);
        static Windows::UI::Xaml::DependencyProperty AlbumNameProperty();

    private:
        static Windows::UI::Xaml::DependencyProperty s_albumNameProperty;
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct AlbumControl : AlbumControlT<AlbumControl, implementation::AlbumControl>
    {
    };
}
