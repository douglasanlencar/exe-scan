// SPDX-License-Identifier: GPL-3.0-or-later

#include "MainWindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("dizionario"));
    QApplication::setApplicationDisplayName(QStringLiteral("Dizionario"));
    QApplication::setOrganizationName(QStringLiteral("KDE"));
    QApplication::setOrganizationDomain(QStringLiteral("kde.org"));
    QApplication::setApplicationVersion(QStringLiteral(DIZIONARIO_VERSION));
    QApplication::setDesktopFileName(QStringLiteral(DIZIONARIO_APP_ID));
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.dizionario"),
                                                 QIcon::fromTheme(QStringLiteral("accessories-dictionary"))));

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("KDE/Qt port of Dizionario.exe (Italian–Chinese image dictionary)"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral("folder"),
                                 QStringLiteral("Dictionary image folder (contains headword.jpg files)"),
                                 QStringLiteral("[folder]"));
    parser.process(app);

    MainWindow window;

    const QStringList args = parser.positionalArguments();
    if (!args.isEmpty()) {
        window.openDirectory(QDir(args.first()).absolutePath(), true);
    } else if (!window.hasDictionary()) {
        // No CLI path and nothing loaded from settings: try default jpg locations.
        window.openDefaultJpgFolder(false);
    }

    window.show();
    return app.exec();
}
