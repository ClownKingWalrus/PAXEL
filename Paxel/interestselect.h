#ifndef INTERESTSELECT_H
#define INTERESTSELECT_H

#include <QDialog>
#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class interestselect;
}

class interestselect : public QDialog
{
    Q_OBJECT

public:
    explicit interestselect(QWidget *parent = nullptr);
    ~interestselect();
    std::string userName;

private slots:
    void on_pushButton_clicked();

private:

    Ui::interestselect *ui;
    void LoadInterest(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName);
    QVBoxLayout* bannerLayout;
    void onInterestButtonClick(std::string InterestID);
    std::map<std::string, bool> interestButtonMap;
};

#endif // INTERESTSELECT_H
