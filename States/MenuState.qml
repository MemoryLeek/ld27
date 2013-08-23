import QtQuick 2.0
import MemoryLeek 1.0

MenuState
{
	id: context
	focus: true

	Column
	{
		anchors.centerIn: parent
		spacing: 10

		Repeater
		{
			model: context.entries

			Text
			{
				id: label
				text: modelData.title
				font.pixelSize: 20
				font.family: "Sans"
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
