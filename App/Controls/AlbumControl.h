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
        {
            DefaultStyleKey(winrt::box_value(L"Codevoid.MusicHall.AlbumControl"));
            this->UseSystemFocusVisuals(true);
        }

        void OnApplyTemplate();
        void OnGotFocus(Windows::UI::Xaml::RoutedEventArgs const& args);
        void OnLostFocus(Windows::UI::Xaml::RoutedEventArgs const& args);
        void OnPointerEntered(Windows::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void OnPointerExited(Windows::UI::Xaml::Input::PointerRoutedEventArgs const& args);

        void ConfigureItemForRecycling();

#pragma region AlbumName Property
        winrt::hstring AlbumName();
        void AlbumName(winrt::hstring const& value);
        static Windows::UI::Xaml::DependencyProperty AlbumNameProperty();

    private:
        static Windows::UI::Xaml::DependencyProperty s_albumNameProperty;
    public:
#pragma endregion

#pragma region ArtistName Property
        winrt::hstring ArtistName();
        void ArtistName(winrt::hstring const& value);
        static Windows::UI::Xaml::DependencyProperty ArtistNameProperty();

    private:
        static Windows::UI::Xaml::DependencyProperty s_artistNameProperty;
    public:
#pragma endregion

#pragma region AlbumArtUri Property
        Windows::Foundation::Uri AlbumArtUri();
        void AlbumArtUri(Windows::Foundation::Uri const& value);
        static Windows::UI::Xaml::DependencyProperty AlbumArtUriProperty();
        static void OnAlbumArtUriChanged(Windows::UI::Xaml::DependencyObject const& source, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
        
    private:
        void SetImageSource(Windows::Foundation::Uri const& uri);
        static Windows::UI::Xaml::DependencyProperty s_albumArtUriProperty;
        
    public:
#pragma endregion

#pragma region ReleaseYear Property
        int ReleaseYear();
        void ReleaseYear(int const value);
        static Windows::UI::Xaml::DependencyProperty ReleaseYearProperty();
        static void OnReleaseYearChanged(Windows::UI::Xaml::DependencyObject const& source, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
    private:
        static Windows::UI::Xaml::DependencyProperty s_releaseYearProperty;
    public:
#pragma endregion

#pragma region ReleaseYearAsString Property
        /// <summary>
        /// Can't bind a number directly into a text box, so project a
        /// string conversion for binding reasons. This is automatically
        /// updated when ReleaseYear is changed.
        /// </summary>
        winrt::hstring ReleaseYearAsString();
        void ReleaseYearAsString(winrt::hstring const& value);
        static Windows::UI::Xaml::DependencyProperty ReleaseYearAsStringProperty();
    private:
        static Windows::UI::Xaml::DependencyProperty s_releaseYearAsStringProperty;
#pragma endregion

    private:
        void ListenForImageLoadingStates();
        void HandleImageFailed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::ExceptionRoutedEventArgs const& args);
        void HandleImageOpened(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageFailed_revoker m_imageFailedRevoker;
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageOpened_revoker m_imageOpenedRevoker;
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct AlbumControl : AlbumControlT<AlbumControl, implementation::AlbumControl>
    {
    };
}
