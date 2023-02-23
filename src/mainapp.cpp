//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#include "mainapp.h"

#include <QSettings>

#include "mainwindow.h"

namespace
{
  const QString DEFAULT_SETTINGSPATH = "./config/Default.ini";
  const QString DEFAULT_HOSTNAME = "127.0.0.1";
  const QString DEFAULT_PORT = "61616";
}

////
/// \brief The PrivateData class
///
class PrivateData
{
  public:
  PrivateData(void)
    : hostname(DEFAULT_HOSTNAME)
    , port(DEFAULT_PORT)
  {}
  ~PrivateData(void)
  {}

  QString hostname;
  QString port;
};

////
/// \brief MainApplication::MainApplication
/// \param argc
/// \param argv
///
MainApplication::MainApplication(int& argc, char** argv)
  : QApplication(argc, argv)
  , mpWindow(nullptr)
  , mpData(nullptr)
{
  setup();
}

////
/// \brief MainApplication::~MainApplication
///
MainApplication::~MainApplication(void)
{
  if(mpData)
    delete mpData;

  if(mpWindow)
    mpWindow->deleteLater();
}

////
/// \brief MainApplication::styleSheet
/// \return QString
///
QString MainApplication::styleSheet() const
{
  return QApplication::styleSheet();
}

////
/// \brief MainApplication::notify
/// \param receiver
/// \param e
/// \return bool
///
bool MainApplication::notify(QObject* receiver, QEvent* e)
{
  return QApplication::notify(receiver, e);
}

////
/// \brief MainApplication::getDefaultNetworkDetails
/// \return QPair<QString,QString>
///
QPair<QString,QString> MainApplication::getDefaultNetworkDetails(void) const
{
  return QPair<QString,QString>(mpData->hostname, mpData->port);
}

////
/// \brief MainApplication::setup
///
void MainApplication::setup(void)
{
  if (mpData == nullptr)
  {
    mpData = new PrivateData();
  }

  if (mpWindow == nullptr)
  {
    QSettings appSettings(DEFAULT_SETTINGSPATH, QSettings::IniFormat);
    QString hostname = appSettings.value("ActiveMQ/HOSTNAME").toString();
    QString port = appSettings.value("ActiveMQ/PORT").toString();

    if (!hostname.isEmpty()) {
      mpData->hostname = hostname;
    }

    if (!port.isEmpty()) {
      mpData->port = port;
    }

    mpWindow = new MainWindow();
    mpWindow->show();
  }
}
