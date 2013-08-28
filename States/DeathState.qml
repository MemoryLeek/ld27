import QtQuick 2.0
import QtGraphicalEffects 1.0
import MemoryLeek 1.0

DeathState
{
	id: context

	Image
	{
		anchors.fill: parent
		source: "image://frame"

		Text
		{
			id: text
			anchors.fill: parent
			anchors.leftMargin: -50
			text: "SPOTTED!"
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pixelSize: 30
			font.family: "Alwyn New"
			font.bold: true
			styleColor: "#555555"
			style: Text.Outline
			color: "white"
			opacity: 0
			antialiasing: true

			states: State
			{
				when: text.visible

				PropertyChanges { target: text; opacity: 1 }
				PropertyChanges { target: text; anchors.leftMargin: 0 }
			}

			transitions: Transition
			{
				PropertyAnimation { property: "opacity"; duration: 500; }
				PropertyAnimation { property: "anchors.leftMargin"; duration: 200; }
			}
		}

		DropShadow
		{
			anchors.fill: text
			radius: 10
			samples: 16
			color: "black"
			source: text
		}
	}
}
