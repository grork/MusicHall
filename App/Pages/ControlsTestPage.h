#pragma once

#include "ControlsTestPage.g.h"

namespace winrt::Codevoid::MusicHall::implementation
{
    struct ControlsTestPage : ControlsTestPageT<ControlsTestPage>
    {
        ControlsTestPage();
    };
}

namespace winrt::Codevoid::MusicHall::factory_implementation
{
    struct ControlsTestPage : ControlsTestPageT<ControlsTestPage, implementation::ControlsTestPage>
    {
    };
}
