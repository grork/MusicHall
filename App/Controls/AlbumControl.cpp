#include "pch.h"
#include "AlbumControl.h"
#include "AlbumControl.g.cpp"

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media::Imaging;

namespace winrt::Codevoid::MusicHall::implementation
{

    void AlbumControl::OnApplyTemplate()
    {
        this->ListenForImageLoadingStates();
        this->SetImageSource(this->AlbumArtUri());
    }

    void AlbumControl::ListenForImageLoadingStates()
    {
        auto imageSource = this->GetTemplateChild(L"ImageSource").try_as<BitmapImage>();
        if (imageSource == nullptr)
        {
            // We don't have the image. Either because we've been called too early
            // (e.g. no template applied), or because someone left it out of the
            // teimplate. Either way, nothing to do
            return;
        }

        m_imageFailedRevoker = imageSource.ImageFailed(auto_revoke, { this, &AlbumControl::HandleImageFailed });
        m_imageOpenedRevoker = imageSource.ImageOpened(auto_revoke, { this, &AlbumControl::HandleImageOpened });
    }

    void AlbumControl::HandleImageFailed(IInspectable const& /*sender*/, ExceptionRoutedEventArgs const& /*args*/)
    {
        VisualStateManager::GoToState(*this, L"ImageLoadFailed", false);
    }

    void AlbumControl::HandleImageOpened(IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        VisualStateManager::GoToState(*this, L"ImageLoadSucceeded", false);
    }

#pragma region AlbumName Property
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
#pragma endregion

#pragma region ArtistName Property
    DependencyProperty AlbumControl::s_artistNameProperty =
        DependencyProperty::Register(
            L"ArtistName",
            xaml_typename<hstring>(),
            xaml_typename<MusicHall::AlbumControl>(),
            PropertyMetadata({ box_value(L"") })
        );

    hstring AlbumControl::ArtistName()
    {
        return unbox_value<winrt::hstring>(GetValue(s_artistNameProperty));
    }

    void AlbumControl::ArtistName(hstring const& value)
    {
        SetValue(s_artistNameProperty, box_value(value));
    }

    DependencyProperty AlbumControl::ArtistNameProperty()
    {
        return s_artistNameProperty;
    }
#pragma endregion

#pragma region AlbumArtUri Property
    DependencyProperty AlbumControl::s_albumArtUriProperty =
        DependencyProperty::Register(
            L"AlbumArtUri",
            xaml_typename<Uri>(),
            xaml_typename<MusicHall::AlbumControl>(),
            PropertyMetadata(nullptr, PropertyChangedCallback{ &AlbumControl::OnAlbumArtUriChanged })
        );

    Uri AlbumControl::AlbumArtUri()
    {
        return GetValue(s_albumArtUriProperty).try_as<Uri>();
    }

    void AlbumControl::AlbumArtUri(Uri const& value)
    {
        SetValue(s_albumArtUriProperty, value);
    }

    DependencyProperty AlbumControl::AlbumArtUriProperty()
    {
        return s_albumArtUriProperty;
    }

    /// <summary>
    /// Why are we doing manual value transfer on the property change, rather
    /// than binding naturally in the control template? Because no matter what
    /// was tried, the URI would not make it to the BitmapImage. So, manual
    /// transfer was the solution to unblock in the time being
    /// </summary>
    void AlbumControl::OnAlbumArtUriChanged(DependencyObject const& source, DependencyPropertyChangedEventArgs const& args)
    {
        auto projection_self = source.try_as<MusicHall::AlbumControl>();
        if (projection_self == nullptr)
        {
            return;
        }
        
        // See https://devblogs.microsoft.com/oldnewthing/20200828-00/?p=104138
        // for insight on the complexity here. tl;dr WinRT causes two AlbumControl
        // types to exist, and the one we have entering this function is the
        // projection, and we need the implementation.
        AlbumControl* f = get_self<AlbumControl>(projection_self);
        f->SetImageSource(args.NewValue().try_as<Uri>());
    }

    void AlbumControl::SetImageSource(Windows::Foundation::Uri const& /*uri*/)
    {
        auto imageSource = this->GetTemplateChild(L"ImageSource").try_as<BitmapImage>();
        if (imageSource == nullptr)
        {
            // We don't have the image. Either because we've been called too early
            // (e.g. no template applied), or because someone left it out of the
            // teimplate. Either way, nothing to do
            return;
        }

        imageSource.UriSource(this->AlbumArtUri());
    }
#pragma endregion

#pragma region ReleaseYear Property
    DependencyProperty AlbumControl::s_releaseYearProperty =
        DependencyProperty::Register(
            L"ReleaseYear",
            xaml_typename<int>(),
            xaml_typename<MusicHall::AlbumControl>(),
            PropertyMetadata({ box_value(1970), PropertyChangedCallback{ &AlbumControl::OnReleaseYearChanged } })
        );

    int AlbumControl::ReleaseYear()
    {
        return unbox_value<int>(GetValue(s_releaseYearProperty));
    }

    void AlbumControl::ReleaseYear(int const value)
    {
        SetValue(s_releaseYearProperty, box_value(value));
    }

    DependencyProperty AlbumControl::ReleaseYearProperty()
    {
        return s_releaseYearProperty;
    }

    void AlbumControl::OnReleaseYearChanged(DependencyObject const& source, DependencyPropertyChangedEventArgs const& args)
    {
        auto self = source.try_as<MusicHall::AlbumControl>();
        if (self == nullptr)
        {
            return;
        }

        int newValue = unbox_value<int>(args.NewValue());
        self.ReleaseYearAsString(to_wstring(newValue));
    }
#pragma endregion

#pragma region ReleaseYearAsString Property
    DependencyProperty AlbumControl::s_releaseYearAsStringProperty =
        DependencyProperty::Register(
            L"ReleaseYearAsString",
            xaml_typename<hstring>(),
            xaml_typename<MusicHall::AlbumControl>(),
            PropertyMetadata({ box_value(L"") })
        );

    hstring AlbumControl::ReleaseYearAsString()
    {
        return unbox_value<hstring>(GetValue(s_releaseYearAsStringProperty));
    }

    void AlbumControl::ReleaseYearAsString(hstring const& value)
    {
        SetValue(s_releaseYearAsStringProperty, box_value(value));
    }

    DependencyProperty AlbumControl::ReleaseYearAsStringProperty()
    {
        return s_releaseYearAsStringProperty;
    }
#pragma endregion
}
