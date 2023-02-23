//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#include "commmanager.h"

#include "mainapp.h"
#include "Receive.h"

////
/// \brief The PrivateData class
///
class PrivateData
{
  public:
  PrivateData(void)
    // default to openwire
    : url("failover:(tcp://localhost:61616)")
    , hostname("localhost")
    , port("61616")
  {}
  ~PrivateData(void)
  {}

  QString url;
  QString hostname;
  QString port;
};

CommManager* CommManager::mpSingleton = nullptr;

////
/// \brief CommManager::CommManager
///
CommManager::CommManager(void)
  : QObject(nullptr)
  , mpData(nullptr)
  //, mpPublisher(nullptr)
  //, mpReceiver(nullptr)
{
  // Get the default settings from mainapp
  if (MainApplication* mainApp = dynamic_cast<MainApplication*>(QApplication::instance()))
  {
    QPair<QString,QString> networkDetails = mainApp->getDefaultNetworkDetails();
    mpData = new PrivateData();
    mpData->hostname = networkDetails.first;
    mpData->port = networkDetails.second;
  }
}

////
/// \brief CommManager::~CommManager
///
CommManager::~CommManager(void)
{
  if (mpData)
    delete mpData;

//  if (mpPublisher)
//    delete mpPublisher;

//  if (mpReceiver)
//    delete mpReceiver;
}

////
/// \brief setBrokerDetails
/// \param brokerURL
///
void CommManager::setBrokerDetails(const QString& brokerURL)
{
  if (mpData && mpData->url != brokerURL)
  {
    mpData->url = brokerURL;
  }
}

////
/// \brief setBrokerDetails
/// \param brokerHost
/// \param brokerPort
///
void CommManager::setBrokerDetails(const QString& brokerHost, const QString& brokerPort)
{
  if (mpData)
  {
    bool change = false;

    if (mpData->hostname != brokerHost)
    {
      mpData->hostname = brokerHost;
      change = true;
    }

    if (mpData->port != brokerPort)
    {
      mpData->port = brokerPort;
      change = true;
    }

    if (change)
    {
      mpData->url = QString("failover:(tcp://%1:%2)")
        .arg(brokerHost)
        .arg(brokerPort);
    }
  }
}

////
/// \brief CommManager::start
/// \return
///
bool CommManager::start(void)
{
  bool retVal = false;

  try
  {
    emit networkStatusUpdate(constants::network::Connecting);
//    if (mpReceiver == nullptr)
//    {
//      mpReceiver = new nw_network::Receive(mpData->hostname, mpData->port, true, true);
//      mpReceiver->run();
//      retVal = true;
//    }
  }
  catch (std::exception& e)
  {
    printf("Exception Occured. %s\\n", e.what());
  }

  return retVal;
}

////
/// \brief CommManager::instance
/// \return
///
CommManager& CommManager::instance(void)
{
  if (mpSingleton == nullptr)
    mpSingleton = new CommManager();

  return *mpSingleton;
}

////
/// \brief CommManager::release
///
void CommManager::release(void)
{
  if (mpSingleton) {
    delete mpSingleton;
  }
}

////
/// \brief CommManager::handleResults
/// \param count
///
void CommManager::handleResults(const int count)
{
  Q_UNUSED(count);
}
