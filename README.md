OSLua - Lua bindings for [OSLib (MOD)](http://trac2.assembla.com/oslibmod)
======================================

WIP to create a lua interpreter with built-in bindings to [OSLib
MOD](http://trac2.assembla.com/oslibmod), plus [lua-fs](http://www.steve.org.uk/Software/lua-fs/) for basic filesystem operations.

 * Original OSLib project site: http://brunni.palib.info/new/index.php?page=pspsoft_oslib
 * OSLib MOD project site: http://trac2.assembla.com/oslibmod
 * lua-fs project site: http://www.steve.org.uk/Software/lua-fs/

Except for the fact that the binding breaks up the oslib functions into
separate modules, the interface is nearly identical where possible. As
such, you should refer to the library documentation, except as noted.

* OSLib MOD documentation: http://www.sakya.it/OSLib_MOD/doc/html/
* OSLua documentation: tbd

**WARNING:** As a work in progress, it is **very** possible to crash
your unit in the same manner as one might cause a crash using OSLib
improperly. I'm working on trying to track things that can cause crashes
and finding ways to avoid/mitigate them, but there are very few checks
in OSLib itself to prevent you from doing something that uses a bad
pointer reference (e.g. using an image after calling EndGfx).

**USE AT YOUR OWN RISK**

Downloading and Installing
--------------------------

OSLua works well enough to show a few demos and can be [downloaded
here](http://nick.borko.org/downloads/oslua.zip). Unzip and copy to GAME5XX.
