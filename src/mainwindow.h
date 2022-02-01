#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  bool getFirstPlay() const;

  void setFirstPlay(bool newFirstPlay);

 private slots:
  void on_actionOpen_triggered();
  void on_actionPlay_triggered();
  void on_actionPause_triggered();
  void on_actionStop_triggered();
  void mute();

 private:
  Ui::MainWindow* ui;
  const int maxVolume;
  const int minVolume;
  bool firstPlay;

  QMediaPlayer* m_player;
  QVideoWidget* m_vw;
  QProgressBar* m_bar;
  QSlider* m_slider;

  QHBoxLayout* m_hvLayout;
  QPushButton* m_btnMute;
  QLabel* m_vlbl;
  QSpinBox* m_spinboxVolume;

  void init();
  void setupVolumeBox();
  void createMediaOutput();
  void createSlider();
  void createSignalSlots();

};
#endif // MAINWINDOW_H
