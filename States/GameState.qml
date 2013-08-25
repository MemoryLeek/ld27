import QtQuick 2.0
import MemoryLeek 1.0

GameState
{
	id: context
	focus: true

	Rectangle
	{
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.margins: 10
		anchors.topMargin: 10 + (10 - context.timePool) * 10

		color: "#0000ff"
		height: context.timePool * 10
		width: 20
	}

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
