# General Architecture
The intent here is to create just enough separation between components that
things aren't tightly coupled, but also don't strive to be "general purpose".

## Project Level
At the project level, the `App` is intended to contain the UI / App lifecycle.
In a full implementation, there would also be a `DataStore` project which
contained the logic for the database, non-UI bound business logic (Sync, DRM
management, basic service wrapper).

For interacting with a complex service, including things like account management,
authentication, payments, service caching, there would likely be another discrete
project.

## UI Components
There are four main compoinents: `App`, `MainUI`, `AlbumControl`, and `AlbumsPage`.

### App
This is a simple lifecycle manager for the UWP model to handle app launch etc.
In this implementaiton, it has explicit knowledge of the first page to navigate
too, but in a deeper implementation this would be handed off to another component.

Note, that this class can become quite complex given it's need to handle multiple
launch scenarios (Tile, URL, Prelaunch, Background), as well as general app lifecycle
such as suspend & resume.

### MainUI
This houses the navigation `Frame`, and provides simple navigation using `NavigationView`.
It is also the entry point for many system-UI interactions (aka Back Navigation),
which requires hooks into multiple places to conform to the expecations of windows users.

In this implementation I also chose to put a 'debug' menu behind the 'ctrl' key
to make it easy to test some specific scenarios without relying on the rest of the app
infrastructure. (Test Page for controls, and a simple forward navigation)

### AlbumControl
This is a templated control that represents an 'Album'. It contains enough to represent
what is needed to display an album, and handle the basic UI affordances one expects
of an item in a grid (Keyboard Focus, Hover State, Click/Invocation).

Note that this control dervies from `ButtonBase` to get the basic click/tap/keyboard
methods for 'free', but minimizing the impact of attempting to re-style/derive from
an actual `Button`

**Note**, this is currently missing the appropriate `AutomationPeer` implementation
to provide a sensible & viable accessbility interface for screen readers and other
assitive technologies

### AlbumsPage
This is a simple wrapper page containing an [`ItemsRepeater`](https://docs.microsoft.com/en-us/uwp/api/microsoft.ui.xaml.controls.itemsrepeater?view=winui-2.4), that loads some (fake) data into a data object that
can then be bound in `DataTemplate`.

Of note, this page keeps the item layout (in `AlbumControl`) separate from the
behaviour by being the component that handles the invocation of an item in the
list, and performing destination navigation.

In a perfect world, this would would be an `ICommand` implementation sparing this
page from being aware of where it was going.

Also of note, this performs forwarding of element recycling reset to the `AlbumsControl`.
See below (Element Recycling) for more details.

## Language Choice
With C++, there are three dialects for UWP development: "naked" C++, C++/CX,
and C++/WinRT. When it comes to building UI, "naked" C++ is not really viable.
This stems from the extreme boilerplate/legwork required to support the
various interfaces.

This leaves C++/CX & C++/WinRT. From a 'click and go', C++/CX provides the
quickest start, but it's effectively deprecated, and hides a little *too* much
of the details from you.

C++/WinRT is on the cusp of being mature, and has brought an *almost* perfect
balance between "naked" & CX. Given that it is the annointed solution, I chose
to use C++/WinRT for this project.

# Specific Items of Note
## Navigation
Default implementations / guidance on navigation in XAML results in tight
bindings between any code that initiates navigation, and the destination of that
navigation. Normally, the guidance is to use `typeof`-type operators to obtain a
representation of the type. But this is a strong type, so caller needs explicit
references -- this makes it hard for things like separately compilation unit's
(DLLs, or in-binary), or even simple A/B style testing of different
destinations.

So, in this case, we use the [interop
type](https://docs.microsoft.com/en-us/uwp/api/Windows.UI.Xaml.Interop.TypeName?view=winrt-19041)
`TypeName` to help break the tight coupling.

## Album Control
In a full application, there is likely to be many use cases for display of
albums. The information required to display these will be from multiple sources
(E.g. local database, service database, playing state). Trying to build a single
data object that covers all those cases is going to be a sisyphean task.

Createing a single control for the *Display* of albums will allow the separation
of the mutiple sources. Additionally, building it as a control will allow the
display of the items to be adjusted separately from the behaviour of the items.

Interesting Wrinkle: While trying to bind the `AlbumArtUri` using
`{TemplateBinding}` in the control template, no matter what I did, I couldn't
get the binding to correctly transfer to the image. After giving up, I chanaged
to manual value transfer on the dependency property change, and in
`OnApplyTemplate` to handle template lifecycle woes.

Additional Wrinkle: Can't bind a int into a `TextBlock::Text` (it's a string) so
created a `ReleaseYearAsString` property to project a converted string. Could
have done it with a converter, but decided to be a little dirty for simplicity
reasons.

### Album Control Focus / Hover
Keyboard Focus, and Hover state are important. But they are tied to two
logically different things -- behaviour & layout. To enable the behaviour, you
have to wire up event handling, handle some state changes, and what not. But you
don't want that to be intertwined with the visuals.

XAML makes this easier with the `VisualStateManager`. In our usage here, we can
push the state management/logic for handling focus into the control code, and
then leverage the template to do the heavy lifting of the visuals.

Within infinite time, I would have liked to create some of the hover state UI on
demand through some abstractions of the actual XAML control that would handle
the hover state. This would allow lower memory/performance by not having the
'idle' elements sitting in the visual tree.

The need to handle some of this here, was a by product of using `ItemsRepeater`,
rather than a "Kitchen Sink" control such as a `ListView`.

## Element Recycling
The XAML `ItemsRepeater` control is a light weight, yet capable control for
repeating elements. It brings with it little behaviour, and allows customized
layouts if you need the power of non-uniform layouts.

It's biggest advantage is *out of the box* it comes with UI Virtualization
inside any `ScrollViewer`. You can see this at play with the 1000 album-view
that is very light on it's RAM usage. It does some with a trade off -- mandatory
managment of recycling of any used control.

Here, this means that the image & failed states need to be correctly reset when
an element is recycled. You can see this in `AlbumsPage` and `AlbumControl`. See
`ElementClearing` in `AlbumsPage`.

## Sample Data
In the interests of focusing on the UI, rather than data, there is simple async
data generation on navigating to the albums page, creating some random
information that can be used in the albums control. This includes using
loremflickr.com for the images. Sometimes images are not set to give an example
of the no-image case. Of note the 'lock' in the URL is used to help keep a
stable image, rather than having to reload everytime. These are licensed under
Creative Commons licenses.

## Navigation View
The Navigation view provides a full featured, and adaptable "Application
Navigation" UI. One downside is that supporting selection of an item requires a
meaningful amount of boilerplate to create simple data objects that can be be
used to tag items, associate with navigation, all to keep the selected state of
the menu items consisten.

It's also the opinion of the author that it leaves a quite a lot to be desired
interms of giving a sense of identity to your applications -- with this control
it stands out from the get-go that your navigation is *this* way. There are lots
of other ways to do navigation, and this control is a little constrained in
enabling that.