PbniList - uo_list and uo_vector
--------

PbniList is a Powerbuilder PBNI extension that wraps the C++ STL to
provide a (linked) list and a vector implementation to PB.

Both list and vector have a built-in iterator for easy crawling and
both allow addition of items at the begining, end or at any position.

You can also sort the list and vector by providing a comparator object
to the `sort()` method. The given method is called at the object, 
its prototype must be `function integer name_of_method (any a, any b)`.
The method must return -1, 0 or 1 depending on the comparison of the given values.

This is free code, released under the MIT license with the hope that
it could be useful to someone else. There is absolutely NO WARRANTY.
Please read the license.txt for details.

Remarks, comments, questions and bug reports are welcome : drop me a
message at sebastien.kirche@free.fr

Please also drop me a note if you use that extension.

## How to configure Visual Studio to debug the lib

Note: the actual setting is store in your PbniList.vcproj.<company>.<username>.user file

For a given combination of debug/release and PB version, go to the project properties / Debugging, example provided for PB12.5
- Command = C:\Program Files\Sybase\PowerBuilder 12.5\PB125.EXE
- Command arguments = /workspace worksp125.pbw
- Working directory = $(ProjectDir)
- Attach = no
