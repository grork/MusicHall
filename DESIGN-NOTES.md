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

Additional Wrinkle: Can't bind a int into a `TextBlock::Text` (it's a string)
so created a `ReleaseYearAsString` property to project a converted string.
Could have done it with a converter, but decided to be a little dirty for
simplicity reasons.

## Sample Data
In the interests of focusing on the UI, rather than data, there is simple
async data generation on navigating to the albums page, creating some
random information that can be used in the albums control. This includes
using loremflickr.com for the images. Sometimes images are not set to
give an example of the no-image case. Of note the 'lock' in the URL is used to
help keep a stable image, rather than having to reload everytime. These are
licensed under Creative Commons licenses.