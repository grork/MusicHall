#pragma once

#include "MainUI.g.h"
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>

namespace winrt::Codevoid::MusicHall::implementation
{
    struct MainUI : MainUIT<MainUI>
    {
        MainUI();

        /// <summary>
        /// API for navigating to a supplied page type, with the supplied
        /// parameter information.
        /// </summary>
        /// <param name="pageType">Type of page to navigate to</param>
        /// <param name="parameter"
        /// Parameter to pass to the page. The type of this parameter is
        /// defined by the page itself. Consult the page your navigating to
        /// to understand what parameters are supported.
        /// </param>
        void Navigate(Windows::UI::Xaml::Interop::TypeName const& pageType, Windows::Foundation::IInspectable const& parameter);
        void HandlePlaceholderButtonClick(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void HandleNavigateToControlsTestPageButtonClick(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void HandleFrameNavigation(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        private:
            void HandleWindowKeyDown(Windows::UI::Core::CoreWindow const& sender, Windows::UI::Core::KeyEventArgs const& args);
            void HandleWindowKeyUp(Windows::UI::Core::CoreWindow const& sender, Windows::UI::Core::KeyEventArgs const& args);
            void HandleBackRequested(Windows::Foundation::IInspectable const& sender, Windows::UI::Core::BackRequestedEventArgs const& args);
            void HandlePointerReleased(Windows::UI::Core::CoreWindow const& sender, Windows::UI::Core::PointerEventArgs const& args);

            /// <summary>
            /// Helper to navigate to a placeholder page with some placeholder
            /// text. Used for simple testing.
            /// </summary>
            /// <param name="placeholderText">Text to display on the page</param>
            void NavigateToPlaceholderPage(winrt::hstring const& placeholderText);

            /// <summary>
            /// Navigates the main UI frame back one item, if there is something
            /// to navigate back to to.
            /// </summary>
            /// <returns>True if back navigation was possible; false otherwise</returns>
            bool NavigateBackIfPossible();

            // Event revoker dumpster fields
            Windows::UI::Core::SystemNavigationManager m_navigationManager{ nullptr };
            winrt::Windows::UI::Core::CoreWindow::KeyDown_revoker m_coreWindowKeyDownRevoker;
            winrt::Windows::UI::Core::CoreWindow::KeyUp_revoker m_coreWindowKeyUpRevoker;
            winrt::Windows::UI::Core::CoreWindow::PointerReleased_revoker m_coreWindowPointerReleasedRevoker;
            winrt::Windows::UI::Core::SystemNavigationManager::BackRequested_revoker m_navigationManagerBackRequestedRevoker;
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct MainUI : MainUIT<MainUI, implementation::MainUI>
    {
    };
}
