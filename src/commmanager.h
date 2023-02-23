//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#ifndef COMMMANAGER_H
#define COMMMANAGER_H

#include <QObject>
#include <QThread>

#include "constants.h"

class PrivateData;

namespace nw_network
{
//class Receive;
//class Publish;
}

class CommManager : public QObject
{
  Q_OBJECT

public:
  static CommManager& instance(void);
  void release(void);

  void setBrokerDetails(const QString& brokerURL);
  void setBrokerDetails(const QString& brokerHost, const QString& brokerPort);

  bool start(void);

signals:
  void networkStatusUpdate(const constants::network::Status e);

public slots:
  void handleResults(const int);

private:
  CommManager(void);
  ~CommManager(void);
  PrivateData* mpData;
  static CommManager* mpSingleton;

  //nw_network::Publish* mpPublisher;
  //nw_network::Receive* mpReceiver;
};

#endif // COMMMANAGER_H
