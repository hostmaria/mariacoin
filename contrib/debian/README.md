
Debian
====================
This directory contains files used to package mariad/maria-qt
for Debian-based Linux systems. If you compile mariad/maria-qt yourself, there are some useful files here.

## maria: URI support ##


maria-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install maria-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your maria-qt binary to `/usr/bin`
and the `../../share/pixmaps/maria128.png` to `/usr/share/pixmaps`

maria-qt.protocol (KDE)

