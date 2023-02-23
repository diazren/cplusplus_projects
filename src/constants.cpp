//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 01/23/2023
//# ----------------------------------------------------------------

#include "constants.h"

namespace constants
{

namespace network
{

////
/// \brief toString
/// \param e
/// \return
///
QString toString(Status e)
{
  QString retVal;

  switch (e)
  {
  case Online:
    retVal = "Online";
    break;
  case Connecting:
    retVal = "Connecting";
    break;
  case Offline:
    retVal = "Offline";
    break;
  case Invalid:
    retVal = "Invalid";
  }

  return retVal;
}

////
/// \brief fromString
/// \param str
/// \return
///
Status fromString(const QString& str)
{
  Status retVal = Invalid;

  if (str.compare("Online", Qt::CaseInsensitive) == 0)
  {
    retVal = Online;
  }
  else if (str.compare("Connecting", Qt::CaseInsensitive) == 0)
  {
    retVal = Connecting;
  }
  else if (str.compare("Offline", Qt::CaseInsensitive) == 0)
  {
    retVal = Offline;
  }

  return retVal;
}

} // network

} // constants
