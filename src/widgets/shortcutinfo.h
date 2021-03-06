/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2018 by Luca Bellonda and individual contributors       *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/

#ifndef SHORTCUTINFO_H
#define SHORTCUTINFO_H

#include "xmlEdit.h"
#include <QHideEvent>

class ActionKeyInfo;

namespace Ui
{
class ShortcutInfo;
}

class ShortcutInfo : public QWidget
{
    Q_OBJECT
    //
    enum EClasses {
        F,
        CS,
        CA,
        C,
        CN,
        CF,
        O
    };

    QHash<QWidget*, ActionKeyInfo*> _mapper;
    bool _lightTheme ;
    QString _themeCSS;
    QString _templateTextEnabled;
    QString _templateTextDisabled;
    QString _templateQuit;
    QString _templateClose;
    QString _templateGreen;
    QString _cssQuit;
    QString _cssClose;
    QString _cssGreen;
    QList<ActionKeyInfo*> _actions;
    QList<ActionKeyInfo*> _F;
    QList<ActionKeyInfo*> _ctrShift;
    QList<ActionKeyInfo*> _ctrAlt;
    QList<ActionKeyInfo*> _C;
    QList<ActionKeyInfo*> _CN;
    QList<ActionKeyInfo*> _CF;
    QList<ActionKeyInfo*> _others;
    //---
    int _signalHidden;
    //---------------------------
    void setupData();
    QWidget *newKey(ActionKeyInfo *info, const QString &css, const QString &tpl, const QString &tplDis, const bool isAlwaysEnabled);
    void chooseTheme();
    QString readCSSData(const QString &name);
    QString readResourceString(const QString &name);
    QWidget* createWidget(const QString &text);
    QWidget* createLabel(const QString &text);
    QWidget* createButton(const QString &text);
    void refreshButtons(const QList<ActionKeyInfo*> &infos);
    //
    QString findPropertyText(QDomElement &parentElement);
    void collectAction(QDomElement &actionElement);
    bool getAllActions(QDomNode &rootNode);
    void loadActions();
    bool isCtrlFn(const QString &input);
    bool isCtrlNum(const QString &input);
    void addOther(ActionKeyInfo *info);
    QString normalizeLabel(const QString &label);
    void removeWidgets();
    QList<ActionKeyInfo*> sortActions(const QList<ActionKeyInfo*> &infos);
    QString filterCmd(const QString &input, const QString &prefix);
    void setTemplates(ActionKeyInfo *info, const QString &templateString, const QString &key, const QString &text);
protected:
    virtual void hideEvent(QHideEvent *event);
public:
    explicit ShortcutInfo(QWidget *parent = 0);
    ~ShortcutInfo();

    void setTarget(QWidget *target);
    void doResize(const bool isFirstTime);
    void autoHide();
    void autoShow();

private:
    Ui::ShortcutInfo *ui;
private slots:
    void on_type_currentIndexChanged(int index);
    void onWidgetClicked();
signals:
    void actionRequested(const QString &actionName);
    void hidden();
    void typeChanged();
};

#endif // SHORTCUTINFO_H
