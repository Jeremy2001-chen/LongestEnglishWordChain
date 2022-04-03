# coding=gbk

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from surface import Surface
import os

global surface



class outputSurface(Surface):
    nameSignal = pyqtSignal(str)

    def __init__(self):
        super().__init__()

        self.headLabel = QLabel("����������")
        self.headLabel.setAlignment(Qt.AlignHCenter)
        self.headLabel.setStyleSheet("font-size:80px;"
                                     "font-weight:bold;"
                                     "font-family:Roman"
                                     "times;")
        self.headLabel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.mainLayout.addWidget(self.headLabel, 0, 0, 9, 9)

        self.outputSurface = QWidget()
        self.outputSurfaceLayout = QGridLayout()
        self.outputSurface.setLayout(self.outputSurfaceLayout)
        self.mainLayout.addWidget(self.outputSurface, 1, 1, 8, 8)

        self.workLabel = QLabel("�����")
        self.workLabel.setStyleSheet("font-size:30px;"
                                     "font-family:Roman"
                                     "times;")

        self.workLabel.setAlignment(Qt.AlignLeft)
        self.outputSurfaceLayout.addWidget(self.workLabel, 0, 0, 1, 7)

        self.exportBut = QPushButton("�������ļ�")
        self.outputSurfaceLayout.addWidget(self.exportBut, 0, 5, 1, 1)

        self.wordOutput = QPlainTextEdit();
        try:
            with open("solution.txt", "r") as f:
                text = ""
                line = f.readline()
                while line:
                    text += line
                    line = f.readline()
            self.wordOutput.setPlainText(text)
        except Exception as e:
            QMessageBox.information(self, '����', "���ش��ļ��쳣���ѷ��س�ʼ���棡")
            from inputWord import inputWordSurface
            global surface
            surface = inputWordSurface()
            self.close()
            surface.show()

        self.outputSurfaceLayout.addWidget(self.wordOutput, 1, 0, 1, 6)

        self.buttonWeight = QWidget()
        self.buttonLayout = QGridLayout()
        self.buttonWeight.setLayout(self.buttonLayout)
        self.outputSurfaceLayout.addWidget(self.buttonWeight, 2, 0, 2, 5)
        self.backButton = QPushButton("����")
        self.buttonBlank = QLabel(" ")
        self.buttonLayout.addWidget(self.buttonBlank, 0, 1, 1, 2)
        self.buttonLayout.addWidget(self.backButton, 0, 3, 1, 1)


        self.resize(960, 720)
        self.setWindowTitle('����������')

        self.exportBut.clicked.connect(self.download_btn_clicked)
        self.backButton.clicked.connect(self.back_btn_clicked)
        
    def back_btn_clicked(self):
        QMessageBox.information(self, '��Ϣ', "���س�ʼҳ�棡")
        from inputWord import inputWordSurface
        global surface
        surface = inputWordSurface()
        self.close()
        surface.show()


    def download_btn_clicked(self):
        fileName, filetype = QFileDialog.getSaveFileName(self, "�����ļ�", os.getcwd(), "All Files (*);;Text Files (*.txt)")
        try:
            with open(fileName, 'w') as f:
                f.write(self.wordOutput.toPlainText())
            f.close()
        except Exception as e:
            print(e)
            QMessageBox.information(self, '����', "�����ļ��쳣�������µ�����")
            return
        QMessageBox.information(self, '��Ϣ', "���Ѿ��������ļ��У�")