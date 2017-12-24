/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    initialPage: Component { VisualPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.Portrait //defaultAllowedOrientations
}

