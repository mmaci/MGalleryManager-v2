Na pøiloženém CD je k nalezení spustitelný *.exe soubor s pøiloženými dynamickými knihovnami, pro operaèní systému Windows. V pøípadì potøeby spustit aplikaci pod operaèním systémem Linux, je tøeba projekt znovu zkompilovat.

Projekt je závislý na knihovnách libjpeg, Boost::gil (verze 1.47) s rozšíøeními, Qt (verze 4.7) a libexif.

Pøi kompilaci pod OS Linux je tøeba postupovat následovnì:
1) Nainstalovat knihovnu libjpeg, která je k nalezení na http://www.ijg.org/.
2) Stáhnout knihovnu Boost (je otestována na verzi 1.47, u verze 1.48 docházelo v dobì psaní bakaláøské práce ke kolizím jmen s knihovnou Qt) a k nalezení na http://sourceforge.net/projects/boost/files/boost/1.47.0/. Knihovna je tvoøena hlavièkovými soubory, není tak tøeba instalace. Pro GIL je tøeba i numerické rozšíøení z http://opensource.adobe.com/wiki/display/gil/Downloads.
3) Nainstalovat knihovnu libexif, která je k nalezení na http://sourceforge.net/projects/libexif/files/libexif/0.6.20/.
4) Nainstalovat Qt SDK z http://qt.nokia.com/downloads.
5) Projekt spustit v prostøedí Qt Creator.
6) Je tøeba upravit projektový soubor MGalv2.pro (napø. v prostøedí Qt Creator), kde se do LIBS pøidají odkazy na knihovny libjpeg a libexif a do INCLUDEPATH cesty k hlavièkovým souborùm Boost::GIL, libexif a libjpeg.
7) Spustit kompilaci.

Pro instalace knihoven libexif a libjpeg by mìlo staèit zmìnit cestu v konzoli na složku, do které byly knihovny nakopírovány a následnì jen spustit pøíkazy:
./configure
make
make install
