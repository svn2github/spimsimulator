#include <QObject>
#include <QCheckBox>

class settableCheckBox : public QCheckBox
{
Q_OBJECT

public:
    settableCheckBox(QWidget* w) : QCheckBox(w) {};

public slots:
    void set() {setChecked(true);}
    void unset() {setChecked(false);}
};
