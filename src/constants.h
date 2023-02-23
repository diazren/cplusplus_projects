//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 01/23/2023
//# ----------------------------------------------------------------

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QMetaType>
#include <QString>

namespace constants
{

namespace network
{
  enum Status
  {
    Invalid = -1,
    Online,
    Connecting,
    Offline
  };

  QString toString(Status);
  Status fromString();
} // network

} // constants

Q_DECLARE_METATYPE(constants::network::Status);

#endif // CONSTANTS_H
