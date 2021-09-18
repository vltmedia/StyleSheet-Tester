#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    QString PalettePath = "";
    QString LoadedStyle = "";
    QString ColorPalettePath = "Color_Palette.json";

private slots:

    void on_dial_valueChanged(int value);

    void on_actionDefine_theme_path_triggered();

    void on_actionReload_theme_triggered();
    void on_actionLoad_Color_Palette_triggered();

    void on_ProgessBarControl_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_actionReload_Color_Palette_triggered();

    void on_actionExport_Style_triggered();

private:
    Ui::MainWindow *ui;
    QString gsThemePath;

    bool writeReplacedStylesheet();
    bool loadThemeFile();
    bool loadThemeFileToMemory();
    bool replaceWithBasicPalletteJson();
    bool replaceWithVSCodePalletteJson();
    bool cleanWithPalletteJson();
};

#endif // MAINWINDOW_H
