//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#include "Receive.h"

// TESTING ONLY
#include <cms/TextMessage.h>

#include <iostream>
#include <memory>

namespace nw_network
{

////
/// \brief Receive::Receive
/// \param brokerURI
///
Receive::Receive(const QString& brokerURI, const bool useTopic, const bool sessionTransacted)
  : mpConnection(nullptr)
  , mpSession(nullptr)
  , mpDestination(nullptr)
  , mpConsumer(nullptr)
  , mBrokerURI(brokerURI)
  , mSessionTransacted(sessionTransacted)
  , mUseTopic(useTopic)
{
}

////
/// \brief Receive::Receive
/// \param brokerIP
/// \param brokerPort
///
Receive::Receive(const QString& brokerIP, const QString& brokerPort, const bool useTopic, const bool sessionTransacted)
  : mpConnection(nullptr)
  , mpSession(nullptr)
  , mpDestination(nullptr)
  , mpConsumer(nullptr)
  , mBrokerHost(brokerIP)
  , mBrokerPort(brokerPort)
  , mSessionTransacted(sessionTransacted)
  , mUseTopic(useTopic)
{
  // TODO config how many attempts we should have
  mBrokerURI = QString("failover:(tcp://%1:%2)?maxReconnectAttempts=2")
      .arg(mBrokerHost)
      .arg(mBrokerPort);
}

////
/// \brief Receive::~Receive
///
Receive::~Receive(void)
{
  cleanUp();
}

////
/// \brief Receive::close
///
void Receive::close(void)
{
  cleanUp();
}

////
/// \brief Receive::run
///
void Receive::run()
{
  try {

//    // Create a ConnectionFactory
//    std::auto_ptr<cms::ConnectionFactory> connectionFactory(cms::ConnectionFactory::createCMSConnectionFactory(mBrokerURI.toStdString()));

//    // Create a Connection
//    mpConnection = connectionFactory->createConnection();
//    mpConnection->start();
//    mpConnection->setExceptionListener(this);

//    // Create a Session
//    if (mSessionTransacted == true) {
//      mpSession = mpConnection->createSession(cms::Session::SESSION_TRANSACTED);
//    } else {
//      mpSession = mpConnection->createSession(cms::Session::AUTO_ACKNOWLEDGE);
//    }

//    // Create the destination (Topic or Queue)
//    if (mUseTopic) {
//      mpDestination = mpSession->createTopic("TEST.FOO");
//    } else {
//      mpDestination = mpSession->createQueue("TEST.FOO");
//    }

//    // Create a MessageConsumer from the Session to the Topic or Queue
//    mpConsumer = mpSession->createConsumer(mpDestination);

//    mpConsumer->setMessageListener(this);

//    std::cout.flush();
//    std::cerr.flush();
  }
  catch (cms::CMSException& e)
  {
    // Indicate we are ready for messages.
    e.printStackTrace();
  }
}

////
/// \brief Receive::onMessage
/// \param message
///
//void Receive::onMessage(const cms::Message* message)
//{
//  static int count = 0;

//  try {
//    count++;
//    const cms::TextMessage* textMessage = dynamic_cast<const cms::TextMessage*> (message);
//    std::string text = "";

//    if (textMessage != nullptr) {
//      text = textMessage->getText();
//    } else {
//      text = "NOT A TEXTMESSAGE!";
//    }

//    printf("Message #%d Received: %s\\n", count, text.c_str());

//  }
//  catch (cms::CMSException& e) {
//    e.printStackTrace();
//  }
//}

////
/// \brief Receive::onException
/// \param e
///
//void Receive::onException(const cms::CMSException& e)
//{
//  printf("CMS Exception occurred. Shutting down Receive client.\\n");
//  e.printStackTrace();
//  exit(1);
//}

////
/// \brief Receive::cleanUp
///
void Receive::cleanUp(void)
{
  if (mpConnection)
  {
    try {
      mpConnection->close();
    }
    catch (cms::CMSException& e) {
      e.printStackTrace();
    }
  }

  try
  {
    delete mpDestination;
    mpDestination = nullptr;

    delete mpConsumer;
    mpConsumer = nullptr;

    delete mpSession;
    mpSession = nullptr;

    delete mpConnection;
    mpConnection = nullptr;
  }
  catch (cms::CMSException& e) {
    e.printStackTrace();
  }
}

}
