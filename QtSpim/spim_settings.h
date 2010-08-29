#ifndef SPIM_SETTING_DIALOG_H
#define SPIM_SETTING_DIALOG_H

#include <QObject>
#include <QFont>
#include <QColor>

#include "ui_settings.h"

namespace Ui{

    class SpimSettingDialog : public QObject, public SettingDialog
{
Q_OBJECT

public:
    SpimSettingDialog() : SettingDialog()
    {
        regWinFont = NULL;
        regWinColor = NULL;
        regWinBackground = NULL;

        textWinFont = NULL;
        textWinColor = NULL;
        textWinBackground = NULL;
    }

    QFont* regWinFont;
    QColor* regWinColor;
    QColor* regWinBackground;

    QFont* textWinFont;
    QColor* textWinColor;
    QColor* textWinBackground;


public slots:
    void setRegWinFont(QFont f)
    {
        regWinFont = new QFont(f);
        regWinFontLineEdit->setText(f.family());
    }

    void setRegWinColor(QColor c)
    {
        regWinColor = new QColor(c);
        regWinFontColorLineEdit->setText(c.name());
    }

    void setRegWinBackground(QColor c)
    {
        regWinBackground = new QColor(c);
        regWinBackgroundLineEdit->setText(c.name());
    }


    void setTextWinFont(QFont f)
    {
        textWinFont = new QFont(f);
        textWinFontLineEdit->setText(f.family());
    }

    void setTextWinColor(QColor c)
    {
        textWinColor = new QColor(c);
        textWinFontColorLineEdit->setText(c.name());
    }

    void setTextWinBackground(QColor c)
    {
        textWinBackground = new QColor(c);
        textWinBackgroundLineEdit->setText(c.name());
    }
};

}
#endif // SPIM_SETTING_DIALOG_H
