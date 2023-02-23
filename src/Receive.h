//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#ifndef RECEIVE_H
#define RECEIVE_H

#include <QThread>

// External 3rd party includes
#include <activemq/library/ActiveMQCPP.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <activemq/transport/DefaultTransportListener.h>

#include <cms/Connection.h>
#include <cms/ConnectionFactory.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <cms/Session.h>

#include "commmanager.h"

namespace nw_network
{

class Receive : /*public cms::ExceptionListener, public cms::MessageListener,*/ public QThread
{
public:
  explicit Receive(const QString& brokerURI, const bool useTopic = false, const bool sessionTransacted = false);
  explicit Receive(const QString& brokerIP, const QString& brokerPort, const bool useTopic = false, const bool sessionTransacted = false);
  virtual ~Receive();

  void close(void);
  void run() override;

  // Called from the consumer since this class is a registered MessageListener.
  //void onMessage(const cms::Message* message) override;
  // Called from the consumer since this class is a registered ExceptionListener.
  //void onException(const cms::CMSException& e AMQCPP_UNUSED) override;

signals:
  void resultReady(const int count);

private:
  void cleanUp(void);

  cms::Connection* mpConnection;
  cms::Session* mpSession;
  cms::Destination* mpDestination;
  cms::MessageConsumer* mpConsumer;
  bool mSessionTransacted;
  bool mUseTopic;
  QString mBrokerURI;
  QString mBrokerHost;
  QString mBrokerPort;
};

}
#endif // RECEIVE_H
