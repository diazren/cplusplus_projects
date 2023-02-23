//# ----------------------------------------------------------------
//# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
//#
//# AUTHORS: RENE DIAZ JR
//# DATE: 02/22/2023
//# ----------------------------------------------------------------

#ifndef MAINAPP_H
#define MAINAPP_H

#include <QApplication>

class MainWindow;
class PrivateData;

class MainApplication : public QApplication
{
public:
  MainApplication(int &argc, char **argv);
  ~MainApplication(void);

  QString styleSheet() const;

  bool notify(QObject *receiver, QEvent *e) override;

  QPair<QString,QString> getDefaultNetworkDetails(void) const;

private:
  void setup(void);
  MainWindow* mpWindow;
  PrivateData* mpData;
};

#endif // MAINAPP_H
