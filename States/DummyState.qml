import QtQuick 2.0
import MemoryLeek 1.0

DummyState
{
	id: context
	focus: true

	Text
	{
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.margins: 10

		text: context.fps
		font.family: "Monospace"
		font.pointSize: 10
		color: "#ffffff"
	}
}
