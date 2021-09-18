#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gsThemePath = QCoreApplication::applicationDirPath()  + "/Template_ColorPaletteStyleFull.qss";
    gsThemePath = QCoreApplication::applicationDirPath()  + "/Template_ColorPaletteStyle.qss";
    ui->setupUi(this);
    ColorPalettePath = QCoreApplication::applicationDirPath()  + "/Color_Palette.json";
    loadThemeFileToMemory();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dial_valueChanged(int value)
{
    this->ui->DialSliderH->setValue(value);
    this->ui->DialHScrollBar->setValue(value);
    this->ui->DialSliderV->setValue(value);
    this->ui->DialVScrollBar->setValue(value);
}

void MainWindow::on_actionDefine_theme_path_triggered()
{
    gsThemePath = QFileDialog::getOpenFileName(this, tr("Open Theme file"), "", tr("Qt StyleSheet Files (*.qss);;Text files (*.txt);;All files (*.*)"));
    loadThemeFileToMemory();
}

bool MainWindow::loadThemeFile()
{
    QFile *lobConfigFile = new QFile(gsThemePath);
    if(!lobConfigFile->open(QFile::ReadOnly)){

        return false;
    }

    QFile style(gsThemePath);

    if(style.exists() && style.open(QFile::ReadOnly)) {
        QString styleContents = QLatin1String(style.readAll());
        style.close();
        this->setStyleSheet(styleContents);
    }

    lobConfigFile->close();

    return true;
}

bool MainWindow::writeReplacedStylesheet()
{
    QFile file(QCoreApplication::applicationDirPath()  + "/temp_replaced.qss");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing: " << qPrintable(file.errorString());
        return false;
    }

    QTextStream out(&file);
    out << LoadedStyle;

    return true;
}

bool MainWindow::loadThemeFileToMemory()
{
    QFile *lobConfigFile = new QFile(gsThemePath);
    if(!lobConfigFile->open(QFile::ReadOnly)){

        return false;
    }

    QFile style(gsThemePath);

    if(style.exists() && style.open(QFile::ReadOnly)) {
        LoadedStyle = QLatin1String(style.readAll());
        style.close();
        cleanWithPalletteJson();
        //writeReplacedStylesheet();
    }

    lobConfigFile->close();

    return true;
}

bool MainWindow::cleanWithPalletteJson()
{
    if(LoadedStyle.indexOf("@Primary",0,Qt::CaseSensitivity::CaseSensitive) == -1){
        replaceWithVSCodePalletteJson();
    }else{
        replaceWithBasicPalletteJson();
    }
return true;
}

bool MainWindow::replaceWithBasicPalletteJson()
{
    // Find the File
    // Read Json File
    QString val;
    QFile file;
    file.setFileName(QCoreApplication::applicationDirPath()  + "/Color_Palette_Basic.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    // Get Json Object
    QJsonDocument jsdoc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsobj = jsdoc.object();

    // Get Array Objects
    QJsonArray states = jsobj["colors"].toArray();
    QString tempstring = LoadedStyle;
    //int32 indexx = QString::ind("poo");
    // Iterate through the QJsonArray
    for (auto v : states) {
        QJsonValue value = v;
        QJsonObject item = value.toObject();

        QString ReplaceName = "@" + item.value("type").toString();
        QRegularExpression regexp(ReplaceName);
        tempstring = LoadedStyle.replace(regexp,"#"+item.value("hex").toString());
        LoadedStyle = tempstring;
       // qDebug() << LoadedStyle;
        // Add Value to the combobox
    }
    this->setStyleSheet(LoadedStyle);
    return true;
}

bool MainWindow::replaceWithVSCodePalletteJson()
{
    // Find the File
    // Read Json File
    QString val;
    QFile file;
    file.setFileName(ColorPalettePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    // Get Json Object
    QJsonDocument jsdoc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsobj = jsdoc.object();
QJsonObject jsobj_Colors = jsobj.value("colors").toObject();
 QStringList keys = jsobj_Colors.keys();
    // Get Array Objects
    QJsonArray states = jsobj["colors"].toArray();
    QString tempstring = LoadedStyle;
    //int32 indexx = QString::ind("poo");
    // Iterate through the QJsonArray
    for (QString value : keys) {


        QString ReplaceName = "@" + value;
        QRegularExpression regexp(ReplaceName);
        tempstring = LoadedStyle.replace(regexp,jsobj_Colors.value(value).toString());
        LoadedStyle = tempstring;
       // qDebug() << LoadedStyle;
        // Add Value to the combobox
    }
    this->setStyleSheet(LoadedStyle);
    return true;
}

void MainWindow::on_actionReload_theme_triggered()
{
    this->loadThemeFileToMemory();
}

void MainWindow::on_ProgessBarControl_valueChanged(int value)
{
    ui->progressBar->setValue(value);
    ui->lcdNumber->display(value);
}

void MainWindow::on_pushButton_2_clicked()
{
    QColorDialog *lobColorDialog = new QColorDialog;
    lobColorDialog->setCurrentColor(QColor("255,255,255"));
    lobColorDialog->setVisible(true);
}

void MainWindow::on_actionLoad_Color_Palette_triggered()
{
ColorPalettePath = QFileDialog::getOpenFileName(this, tr("Open Color Palette file"), "", tr("Color Palette Files (*.json);;All files (*.*)"));
loadThemeFileToMemory();
}

void MainWindow::on_actionReload_Color_Palette_triggered()
{
    loadThemeFileToMemory();
}

void MainWindow::on_actionExport_Style_triggered()
{
    QString outPath = QFileDialog::getSaveFileName(this, tr("Set Export path for QT Style Sheet"), "", tr("QT Style Sheet (*.qss);;All files (*.*)"));
    QFile file(outPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing: " << qPrintable(file.errorString());
    }

    QTextStream out(&file);
    out << LoadedStyle;

    file.close();
    ui->statusBar->showMessage("Saved QT Style Sheet to : " + outPath);
}
