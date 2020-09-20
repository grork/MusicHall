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