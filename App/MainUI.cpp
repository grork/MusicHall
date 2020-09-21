#include "pch.h"
#include "MainUI.h"
#include "MainUI.g.cpp"

using namespace winrt;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::System;

namespace winrt::Codevoid::MusicHall::implementation
{
    MainUI::MainUI()
    {
        InitializeComponent();
        
        // Attach global handlers to the Core Window so we can toggle the debug
        // buttons visibility when control is held
        auto currentWindow = Window::Current().CoreWindow();
        m_coreWindowKeyDownRevoker = currentWindow.KeyDown(winrt::auto_revoke, { this, &MainUI::HandleWindowKeyDown });
        m_coreWindowKeyUpRevoker = currentWindow.KeyUp(winrt::auto_revoke, { this, &MainUI::HandleWindowKeyUp });
        m_coreWindowPointerReleasedRevoker = currentWindow.PointerReleased(winrt::auto_revoke, { this, &MainUI::HandlePointerReleased });

        m_navigationManager = SystemNavigationManager::GetForCurrentView();
        m_navigationManager.AppViewBackButtonVisibility(AppViewBackButtonVisibility::Collapsed);
        m_navigationManagerBackRequestedRevoker = m_navigationManager.BackRequested(winrt::auto_revoke, { this, &MainUI::HandleBackRequested });
    }

    void MainUI::HandlePlaceholderButtonClick(IInspectable const& source, RoutedEventArgs const& /*args*/)
    {
        auto button = source.try_as<ButtonBase>();
        if (button == nullptr)
        {
            return;
        }

        this->NavigateToPlaceholderPage(unbox_value_or(button.Tag(), L"Unknown"));
    }

    void MainUI::HandleNavigateToControlsTestPageButtonClick(IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        TypeName albumsType{ L"Codevoid.MusicHall.ControlsTestPage", TypeKind::Primitive };
        this->Navigate(albumsType, nullptr);
    }

    void MainUI::HandleFrameNavigation(IInspectable const& /*sender*/, NavigationEventArgs const& /*args*/)
    {
        if (this->NavigationFrame().CanGoBack())
        {
            m_navigationManager.AppViewBackButtonVisibility(AppViewBackButtonVisibility::Visible);
        }
        else
        {
            m_navigationManager.AppViewBackButtonVisibility(AppViewBackButtonVisibility::Collapsed);
        }
    }

    void MainUI::Navigate(TypeName const& pageType, IInspectable const& parameter)
    {
        this->NavigationFrame().Navigate(pageType, parameter);
    }

    void MainUI::HandleWindowKeyDown(CoreWindow const& /*sender*/, KeyEventArgs const& args)
    {
        // Only want to show debug view when control is pressed
        if (args.VirtualKey() != VirtualKey::Control)
        {
            return;
        }

        VisualStateManager::GoToState(*this, L"ShowDebugButtons", false);
    }

    void MainUI::HandleWindowKeyUp(CoreWindow const& /*sender*/, KeyEventArgs const& args)
    {
        // Only want to hide the debug control if it was ctrl that was released
        if (args.VirtualKey() != VirtualKey::Control)
        {
            return;
        }

        VisualStateManager::GoToState(*this, L"HideDebugButtons", false);
    }

    void MainUI::HandlePointerReleased(CoreWindow const& /*sender*/, PointerEventArgs const& args)
    {
        // We want to handle the button on release of the back button, not
        // when it's pressed down. This mimics the common behaviour in browsers
        auto pointerProperties = args.CurrentPoint().Properties();
        if (pointerProperties.PointerUpdateKind() != PointerUpdateKind::XButton1Released)
        {
            return;
        }

        args.Handled(true);
        this->NavigateBackIfPossible();
    }

    void MainUI::HandleBackRequested(IInspectable const&, BackRequestedEventArgs const& args)
    {
        // Make sure the system sees that we handled it, so that it doesn't
        // also invoke the system handler (E.g. in tablet mode go back to the
        // previous app)
        args.Handled(this->NavigateBackIfPossible());
    }

    bool MainUI::NavigateBackIfPossible()
    {
        if (!this->NavigationFrame().CanGoBack())
        {
            return false;
        }

        this->NavigationFrame().GoBack();
        return true;
    }

    void MainUI::NavigateToPlaceholderPage(hstring const& placeholderText)
    {
        Interop::TypeName pageType{ L"Codevoid.MusicHall.PlaceholderPage", TypeKind::Primitive };
        this->Navigate(pageType, box_value(placeholderText));
    }
}
