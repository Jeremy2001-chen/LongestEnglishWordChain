from PyQt5.QtWidgets import *
from PyQt5.QtCore import *


def getWidget():
    widget = QWidget()
    layout = QGridLayout()
    widget.setLayout(layout)
    return widget, layout


def getGroup(name):
    group = QGroupBox(name)
    layout = QGridLayout()
    group.setLayout(layout)
    return group, layout


class Surface(QWidget):

    def __init__(self):
        super().__init__()
        self.mainWidget = QWidget()
        self.mainLayout = QGridLayout()
        self.mainLayout.setSpacing(10)
        self.mainWidget.setLayout(self.mainLayout)
        self.setLayout(self.mainLayout)
        self.center()

    """
    when close, remind people whether he want to leave
    """

    '''
    def closeEvent(self, event):
        reply = QMessageBox.question(self, '提醒',
                                     "你确定要退出吗？", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)

        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
    '''

    """
    set the windows into the middle
    """

    def center(self):
        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    '''
    when press the key, event happened
    '''

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()

    def use_palette(self):
        """
        window_pale = QPalette()
        pixmap = QBrush(QPixmap("./pictures/shixiaoxin.jpg").
                        scaled(self.width(), self.height()))

        window_pale.setBrush(QPalette.Background, QBrush(pixmap))
        self.setPalette(window_pale)
        """

    def paintEvent(self, event):
        """
        painter = QPainter(self)
        pixmap = QPixmap("./pictures/login.jfif")
        painter.drawPixmap(self.rect(), pixmap)
        """
