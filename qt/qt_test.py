from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys

class MyWindow(QMainWindow):
    def __init__(self):
        super(MyWindow, self).__init__()
        self.setGeometry(200, 200, 300, 300)
        self.setWindowTitle("for Fun")
        self.initUI()

    def initUI(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("This is label")
        self.label.move(50, 50)

        self.b1 = QtWidgets.QPushButton(self)
        self.b1.setText("Click or Leave")
        self.b1.clicked.connect(self.clicked)
        self.b1.move(150, 150)

    def clicked(self):
        self.label.setText("Hmm did you clicked?")
        self.update()

    def update(self):
        self.label.adjustSize()


def window():
    app = QApplication(sys.argv)
    #win = QMainWindow()
    #win.setGeometry(100, 100, 640, 480)
    #win.setWindowTitle("Sundry")

    #label = QtWidgets.QLabel(win)
    #label.setText("First Qt")
    #label.move(50, 50)

    
    win = MyWindow()
    win.show()
    sys.exit(app.exec_())

window()
