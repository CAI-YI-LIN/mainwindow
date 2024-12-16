#include "mainwindow.h"
#include<ui_mainwindow.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    // 我要讓actionSave的triggered訊號連結到saveFile()這個槽函數做存檔的動作
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);

}

MainWindow::~MainWindow() {}

// 我要讓actionSave的triggered訊號連結到saveFile()這個槽函數做存檔的動作
void MainWindow::saveFile()
{
    // 開啟檔案對話框
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "Text Files (*.txt)");

    // 如果使用者沒有選擇檔案就直接返回
    if (fileName.isEmpty())
        return;

    // 開啟檔案
    QFile file(fileName);

    // 如果檔案無法開啟就顯示錯誤訊息
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // 建立一個文字串流物件
    QTextStream out(&file);

    // 將文字串流物件寫入文字框的文字
    out << textEdit->toPlainText();

    // 關閉檔案
    file.close();
}
