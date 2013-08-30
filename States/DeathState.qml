import QtQuick 2.0
import QtGraphicalEffects 1.0
import MemoryLeek 1.0

DeathState
{
	id: context
	focus: true

	Image
	{
		anchors.fill: parent
		source: "image://frame"
		cache: false

		Text
		{
			id: text
			anchors.fill: parent
			anchors.leftMargin: -50
			anchors.topMargin: -300
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

		Rectangle
		{
			id: overlay
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.verticalCenter: parent.verticalCenter
			color: "#AA000000"
			height: 100
			opacity: 0

			states: State
			{
				when: overlay.visible

				PropertyChanges { target: overlay; opacity: 1 }
			}

			transitions: Transition
			{
				PropertyAnimation { property: "opacity"; duration: 200; }
			}

			Column
			{
				anchors.centerIn: parent
				anchors.horizontalCenterOffset: -10

				Repeater
				{
					model: context.entries

					Row
					{
						spacing: 5

						Text
						{
							id: marker
							text: "»"
							font.pixelSize: 20
							font.family: "Alwyn New"
							font.bold: true
							horizontalAlignment: Text.AlignHCenter
							color: "red"
							opacity: 0

							states:
							[
								State
								{
									PropertyChanges { target: marker; opacity: 0 }
								},
								State
								{
									when: context.selectedIndex === index

									PropertyChanges { target: marker; opacity: 1 }
								}
							]
						}

						Text
						{
							id: label
							text: modelData.title
							font.pixelSize: 20
							font.family: "Alwyn New"
							font.bold: true
							horizontalAlignment: Text.AlignHCenter
							color: "white"

							states:
							[
								State
								{
									PropertyChanges { target: label; color: "white" }
								},
								State
								{
									when: context.selectedIndex === index

									PropertyChanges { target: label; color: "red" }
								}
							]
						}
					}
				}
			}
		}
	}
}
