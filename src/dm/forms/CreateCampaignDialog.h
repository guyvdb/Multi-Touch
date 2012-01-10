#ifndef CREATECAMPAIGNDIALOG_H
#define CREATECAMPAIGNDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
    class CreateCampaignDialog;
}

class CreateCampaignDialog : public QDialog
{
    Q_OBJECT

public:
  explicit CreateCampaignDialog(QWidget *parent = 0);
  ~CreateCampaignDialog();

  void loadGameSystems(QStringList &pairs);
  QString getGameSystem();
  QString getFileName();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
    Ui::CreateCampaignDialog *ui;
};

#endif // CREATECAMPAIGNDIALOG_H
