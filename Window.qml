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

	Repeater
	{
		model: window.availableStates
		anchors.fill: parent

		Loader
		{
			id: loader
			anchors.fill: parent
			opacity: 0
			source: modelData

			states:
			[
				State
				{
					when: window.activeState != modelData

					PropertyChanges { target: loader; opacity: 0 }
					PropertyChanges { target: loader; focus: false }
				},
				State
				{
					name: "ActiveState"
					when: window.activeState == modelData

					PropertyChanges { target: loader; opacity: 1 }
					PropertyChanges { target: loader; focus: true }
				}
			]

			transitions:
			[
				Transition
				{
					NumberAnimation { property: "opacity"; duration: 500 }
				},
				Transition
				{
					to: "ActiveState"

					SequentialAnimation
					{
						PauseAnimation { duration: 500; }
						NumberAnimation { property: "opacity"; duration: 500 }
					}
				}
			]
		}
	}
}
