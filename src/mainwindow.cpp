//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 01/23/2023
//# ----------------------------------------------------------------

#include "mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QMenu>
#include <QMessageBox>

#include "mainapp.h"
#include "commmanager.h"

#include "ui_mainwindow.h"

namespace
{
  const QString VERSION = "0.0.0.2";
  const QString ABOUT = "Network Watcher is a tool to monitor traffic over an ActiveMQ broker.";
}

// ----------------------------------------------------------------
// ctor
// ----------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  // ******* Setup the Ui and MainWindow *******
  ui->setupUi(this);
  init();
}

// ----------------------------------------------------------------
// dtor
// ----------------------------------------------------------------
MainWindow::~MainWindow()
{
  if (ui)
  {
    delete ui;
    ui = nullptr; // Not needed but just cause
  }

}

// ----------------------------------------------------------------
// aboutThisApp
// ----------------------------------------------------------------
void MainWindow::aboutThisApp(void)
{
  QMessageBox msgBox;
  QString msg = QString("Verison %1\n\n%2").arg(VERSION).arg(ABOUT);

  msgBox.setText(msg);
  msgBox.exec();
}

// ----------------------------------------------------------------
// updateNetworkStatus
// ----------------------------------------------------------------
void MainWindow::updateNetworkStatus(const constants::network::Status e)
{
  if (ui)
  {
    ui->status_value->setText(constants::network::toString(e));
  }
}

// ----------------------------------------------------------------
// init
// ----------------------------------------------------------------
void MainWindow::init(void)
{
  // Get the default settings from mainapp
  if (MainApplication* mainApp = dynamic_cast<MainApplication*>(QApplication::instance()))
  {
    QPair<QString,QString> networkDetails = mainApp->getDefaultNetworkDetails();
    ui->broker_lineEdit->setText( networkDetails.first );
    ui->broker_port_lineEdit->setText( networkDetails.second );
  }

  // File Menu
  QMenu* fileMenu = ui->menubar->addMenu("File");

  QAction* quitAction = new QAction("Quit", this);
  quitAction->setStatusTip(tr("Quit this Game"));
  connect(quitAction, &QAction::triggered, this, &MainWindow::close);

  // Add the actions to file
  fileMenu->addAction(quitAction);

  // Settings Menu
  QMenu* settingsMenu = ui->menubar->addMenu("Settings");

  // Help Menu
  QMenu* helpMenu = ui->menubar->addMenu("Help");

  // Actions for the help menu
  QAction* aboutMeAction = new QAction("About NetworkWatcher", this);
  aboutMeAction->setStatusTip("Learn more!");
  connect(aboutMeAction, &QAction::triggered, this, &MainWindow::aboutThisApp);

  // Add the action to help
  helpMenu->addAction(aboutMeAction);

  // Start the comm managers
  // Consumer and Producer
  CommManager& rCommMgr = CommManager::instance();
  rCommMgr.setBrokerDetails(ui->broker_lineEdit->text(), ui->broker_port_lineEdit->text());
  connect(&rCommMgr, &CommManager::networkStatusUpdate, this, &MainWindow::updateNetworkStatus);
  rCommMgr.start();
}
