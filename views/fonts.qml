pragma Singleton

import QtQuick 2.0

Item {
    id: fonts

    readonly property FontLoader fontAwesome: FontLoader{
        source: "../fonts/FontAwesome5.otf"
    }

    readonly property string icons: fonts.fontAwesome.name
}
