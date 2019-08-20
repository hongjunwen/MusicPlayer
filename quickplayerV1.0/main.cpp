/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QWindow>
#include <QQmlContext>
#include <QStandardPaths>
#include <QDir>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("QuickPlayer"));
    QCoreApplication::setApplicationVersion(QLatin1String(QT_VERSION_STR));
//    QCoreApplication::setOrganizationName(QStringLiteral("QtWinExtras"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("qt-project.org"));
    QGuiApplication::setApplicationDisplayName(QStringLiteral("QT音乐播放器"));

    QQmlApplicationEngine engine;
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QUrl musicUrl = QUrl::fromLocalFile(musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first());
    engine.rootContext()->setContextProperty(QStringLiteral("musicUrl"), musicUrl);

    QCommandLineParser parser;
    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral("url"), QStringLiteral("The URL to open."));
    parser.process(app);
    QUrl commandLineUrl;
    if (!parser.positionalArguments().isEmpty())
        commandLineUrl = QUrl::fromUserInput(parser.positionalArguments().constFirst(), QDir::currentPath(), QUrl::AssumeLocalFile);
    engine.rootContext()->setContextProperty(QStringLiteral("url"), commandLineUrl);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *root = engine.rootObjects().value(0);
    if (QWindow *window = qobject_cast<QWindow *>(root))
        window->show();
    else
        return -1;
    return app.exec();
}
