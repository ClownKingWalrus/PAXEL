#ifndef CREATEBOARDORTHREAD_H
#define CREATEBOARDORTHREAD_H

#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class CreateBoardOrThread;
}

class CreateBoardOrThread : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateBoardOrThread(QWidget *parent = nullptr);
    ~CreateBoardOrThread();
    bool isThread = false;
    void ChangeToThreadWindow(); //converts interest panel to line edit
    void ThreadSumbit();
    std::string boardID;
private slots:
    void on_pushButton_2_clicked();



private:
    void LoadInterest(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName, int UserID);
    Ui::CreateBoardOrThread *ui;
    QVBoxLayout* bannerLayout; //The banner layout pointer
    void onInterestButtonClick(std::string InterestID);
    std::map<std::string, bool> interestButtonMap;
};

#endif // CREATEBOARDORTHREAD_H
