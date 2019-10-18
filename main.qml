import QtQuick 2.13
import QtQuick.Controls 2.5
import QtQuick.Window 2.13
Window {
    visible: true
    width: 375
    height: 750
    title: qsTr("Hello World")

    Rectangle {
        id: rectangle1
        anchors.left: parent.left
        width: parent.width
        height: 100

        Text {
            id: textName
            text: qsTr("姓名:")
            width:40
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 24
        }

        TextField {
            id: inputName
            width:154
            text: qsTr("請輸入姓名")
            anchors.leftMargin: 20
            anchors.top: textName.top
            anchors.left: textName.right
            font.pixelSize: 20

        }

        Text {
            id: textTalk
            text: qsTr("訊息:")
            width:40
            anchors.left: parent.left
            anchors.top: textName.bottom
            anchors.topMargin: 10
            font.pixelSize: 24
        }

        TextField {
            id: inputTalk
            width:154
            text: qsTr("請輸入內容")
            anchors.leftMargin: 20
            anchors.top: textTalk.top
            anchors.left: textTalk.right
            font.pixelSize: 20
        }

        Text {
            id: element1
            x: 237
            y: 27
            color: "#000000"
            text: qsTr("送出")
            font.pixelSize: 24

            MouseArea {
                x: -23
                y: 21
                anchors.fill: parent
                onClicked: {
//                    if (secureWebSocket.status == WebSocket.Open) {
                        socket.sendTextMessage("{\"action\":\""+inputName.text+"\", \"data\":\""+inputTalk.text+"\"}")
//                    }else{
//                        console.log("        log        : socket not open")
//                    }
                }
            }
        }
    }

    Text {
        id: messageBox
        //text: secureWebSocket.status == WebSocket.Open ? qsTr("Sending...") : qsTr("Welcome!")
        anchors.top: rectangle1.bottom
        anchors.right: parent.right
        anchors.left: parent.left

    }
    Connections{
        target: socket
        onTextMessageReceivedChanged:{
            var jsonObject= JSON.parse(message);
            messageBox.text = jsonObject.action +"說"+ jsonObject.data + "\n" + messageBox.text
        }
    }

    Text {
        id: textExit
        width:parent.width
        color: "#111111"
        text: qsTr("關閉連接")
        font.pixelSize: 24
        anchors.bottom: parent.bottom

        MouseArea {
            anchors.fill: parent
            onClicked: {
                socket.close();
            }
        }
    }
}
