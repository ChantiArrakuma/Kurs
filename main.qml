import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Qt.labs.qmlmodels 1.0

import Qt.labs.folderlistmodel 2.15

ApplicationWindow {
    id: root
    width: 1000
    height: 1000

    visible: true
    title: String(myModel.getMaxLine()-1)
    color: "#21a69f"

    Dialog
    {
        id: openDialog1
        title: qsTr("<- 0 ->")
        anchors.centerIn: parent
        Label
        {
            anchors.fill: parent
            text: qsTr("Переход по вариантам ответов  \n \n")
            horizontalAlignment: Text.AlignHCenter
            Button
            {
                text: qsTr("Ok")
                height: 20
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: openDialog1.close()
            }
        }
    }

    Dialog
    {
        id: openDialog2
        title: qsTr("Открыть N")
        anchors.centerIn: parent
        Label
        {
            anchors.fill: parent
            text: qsTr("Открыть вычисленное решение \n решение должно находиться по пути: ./out/ \n \n")
            horizontalAlignment: Text.AlignHCenter
            Button
            {
                text: qsTr("Ok")
                height: 20
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: openDialog2.close()
            }
        }
    }

    Dialog
    {
        id: openDialog3
        title: qsTr("Многопоточное вычисление")
        anchors.centerIn: parent
        Label
        {
            anchors.fill: parent
            text: qsTr("Первая строка ввода - кол-во потоков\n Вторая строка ввода - N \n \n")
            horizontalAlignment: Text.AlignHCenter
            Button
            {
                text: qsTr("Ok")
                height: 20
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: openDialog3.close()
            }
        }
    }


    menuBar: MenuBar
    {
        MenuBarItem
        {
            text: "<-"
            onTriggered:
            {
                if(parseInt(displayCount.text) > 0)
                    displayCount.text = parseInt(displayCount.text) - 1
                myModel.setNewLine(displayCount.text)
            }
        }




        MenuBarItem
        {
            id: displayCount
            text: qsTr("0")
            onClicked:
            {

            }
        }

        MenuBarItem
        {
            text: "->"
            onTriggered:
            {
                if(myModel.getMaxLine()-2 > parseInt(displayCount.text))
                    displayCount.text = parseInt(displayCount.text) + 1
                myModel.setNewLine(displayCount.text)
            }

        }


        Menu
        {
            title: "Открыть N"
            width: 100
            Column
            {
                spacing: 3
                Rectangle
                {
                    color: "grey"
                    width: parent.width
                    height: 20
                    id: nnN
                    TextEdit
                    {
                        id: nn
                        anchors.fill: parent
                    }
                }
                Button
                {

                    width: parent.width
                    height: 20
                    text: "set n"

                    background: Rectangle
                    {
                        anchors.fill: parent
                        color: "Green"
                    }

                    onClicked:
                    {
                        myModel.setN(nn.text)
                        nn.text = ""
                        displayCount.text = "0"
                        root.title = String(myModel.getMaxLine()-1)
                    }
                }
            }

        }

        Menu
        {
            title: qsTr("Многопоточное вычисление ♛")
            width: 100

            Column
            {
                anchors.centerIn: parent
                spacing: 3
                Rectangle{
                    height: 20
                    width: parent.width
                    color: "grey"
                    TextEdit
                    {
                        id: thrEdit
                        anchors.fill: parent

                    }
                }
                Rectangle
                {
                    height: 20
                    width: parent.width
                    color: "grey"
                    TextEdit
                    {
                        id: numEdit
                        anchors.fill: parent

                    }
                }
                Button
                {
                    id: calculate
                    height: 20
                    width: parent.width
                    text: "Calculate"
                    background: Rectangle
                    {
                        id: calculateBG
                        anchors.fill: parent
                        color: "Green"
                    }
                    onClicked:
                    {
                        art.cute(thrEdit.text,numEdit.text)
                        //thrEdit.text = ""
                        numEdit.text = ""
                        //calculateBG.color = "Red"
                    }
                }
            }   //
        }

        Menu
        {
            title: qsTr("Справка")
            MenuItem  {
                text: qsTr("<- 0 ->")
                onTriggered:
                {
                   openDialog1.open()
                }
            }
            MenuItem  {
                text: qsTr("Открыть N")
                onTriggered:
                {
                   openDialog2.open()
                }
            }
            MenuItem  {
                text: qsTr("Многопоточное вычисление")
                onTriggered:
                {
                   openDialog3.open()
                }
            }
        }

    }


    TableView
    {
        id: vTable
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true
        model: myModel
        delegate:
            Rectangle
            {
                implicitWidth: 50
                implicitHeight: 50
                border.width: 1

                Text
                {
                    scale: 3
                    text: place
                    anchors.centerIn: parent
                }
            }
    }

}
