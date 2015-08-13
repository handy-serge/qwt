import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.2

import 'styles' as CustomStyle
import '.' as Gui


/*
Application window allows user to perform some set of activities.
Each activity may need some special GUI.

User is able to switch to current activities by using activity
selector on on a right.

*/

TabView {
    style: CustomStyle.CustomTabViewStyle {}
    currentIndex: 1
    Tab {
        title: 'Analysis'
        Row {
            Image {
                source: 'images/analysis-plots.png'
            }
            Image {
                source: 'images/analysis-stats.png'
            }
        }
    }

    Gui.SettingsPage {}
}
