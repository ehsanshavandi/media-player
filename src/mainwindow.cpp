#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow), maxVolume(200), minVolume(0)
{
  ui->setupUi(this);
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open a file", ""
                                                 );
  on_actionStop_triggered();
  m_player->setMedia(QUrl::fromLocalFile(fileName));

  on_actionPlay_triggered();
}


void MainWindow::on_actionPlay_triggered()
{
  m_player->play();
  m_player->setVolume(50);
  m_spinboxVolume->setValue(50);
  ui->statusbar->showMessage("Playing");
}


void MainWindow::on_actionPause_triggered()
{
  m_player->pause();
  ui->statusbar->showMessage("Paused");
}


void MainWindow::on_actionStop_triggered()
{
  m_player->pause();
  ui->statusbar->showMessage("Stopped");
}

void MainWindow::mute()
{
  if (m_player->isMuted())
    m_player->setMuted(false);
  else
    m_player->setMuted(true);
}

void MainWindow::init()
{
  this->createMediaOutput();
  this->setCentralWidget(m_vw);
  this->createSlider();

  //setup volume
  this->setupVolumeBox();

  this->createSignalSlots();
  this->setWindowTitle("Media Player");
}

void MainWindow::setupVolumeBox()
{
  // create gpbox
  QGroupBox* gpbVolume = new QGroupBox(this);
  m_hvLayout = new QHBoxLayout(this);
  m_vlbl = new QLabel("Volume", this);
  m_spinboxVolume = new QSpinBox(this);
  m_spinboxVolume->setMaximum(maxVolume);
  m_spinboxVolume->setMinimum(minVolume);
  m_btnMute = new QPushButton("Mute", this);
  // add widget to layout
  m_hvLayout->addWidget(m_vlbl);
  m_hvLayout->addWidget(m_spinboxVolume);
  m_hvLayout->addWidget(m_btnMute);
  // set layout
  gpbVolume->setLayout(m_hvLayout);
  ui->statusbar->addPermanentWidget(gpbVolume);

}

void MainWindow::createMediaOutput()
{
  m_player = new QMediaPlayer(this);
  m_vw = new QVideoWidget(this);
  m_player->setVideoOutput(m_vw);
}

void MainWindow::createSlider()
{
  m_slider = new QSlider(this);
  m_bar = new QProgressBar(this);
  m_slider->setOrientation(Qt::Horizontal);

  ui->statusbar->addPermanentWidget(m_slider);
  ui->statusbar->addPermanentWidget(m_bar);

}

void MainWindow::createSignalSlots()
{
  connect(m_player, &QMediaPlayer::durationChanged, m_slider, &QSlider::setMaximum);
  connect(m_player, &QMediaPlayer::positionChanged, m_slider, &QSlider::setValue);
  connect(m_slider, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);

  connect(m_player, &QMediaPlayer::durationChanged, m_bar, &QProgressBar::setMaximum);
  connect(m_player, &QMediaPlayer::positionChanged, m_bar, &QProgressBar::setValue);
  // volume
  connect(m_spinboxVolume, QOverload<int>::of(&QSpinBox::valueChanged), m_player,
          &QMediaPlayer::setVolume);
  connect(m_btnMute, &QPushButton::clicked, this, &MainWindow::mute);
}




