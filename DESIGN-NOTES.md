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