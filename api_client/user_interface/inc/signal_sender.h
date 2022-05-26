#ifndef API_CLIENT_SIGNAL_H
#define API_CLIENT_SIGNAL_H

#include <QThread>

#define REFRESHINTERVAL 3

namespace calmgram::api_client::user_interface {

class SignalSender : public QThread {
    Q_OBJECT
public:
    explicit SignalSender(QObject *parent = 0) 
        : to_run_(true),
          QThread(parent),
          status_(false) {}
public slots:
    void StatusOn() { status_ = true; }
    void StatusOff() {status_ = false; }
    void StopRefresh() { to_run_ = false; }
signals:
    void Ping();
protected:
    virtual void run() override
    {   
        while (to_run_){
            if (status_) {
                emit Ping();
                QThread::sleep(REFRESHINTERVAL);
            }
        }
    }

private:
    bool to_run_;
    bool status_;
};

}  // namespace calmgram::api_client::user_interface

#endif  // API_CLIENT_SIGNAL_H