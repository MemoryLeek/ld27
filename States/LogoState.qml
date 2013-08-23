import QtQuick 2.0
import MemoryLeek 1.0

LogoState
{
	focus: true

	Rectangle
	{
		anchors.fill: parent

		Image
		{
			anchors.centerIn: parent
			source: "image://local/resources/logo.png"
		}
	}
}
