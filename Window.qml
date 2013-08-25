import QtQuick 2.0
import MemoryLeek 1.0

Window
{
	id: window

	Rectangle
	{
		anchors.fill: parent
		color: "black"
	}

	Loader
	{
		id: loader
		anchors.fill: parent
		source: window.activeState
		focus: true
	}
}
