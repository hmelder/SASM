/****************************************************************************
** SASM - simple IDE for assembler development
** Copyright (C) 2013 Dmitriy Manushin
** Contact: site: http://dman95.github.io/SASM/
**          e-mail: Dman1095@gmail.com
**
** This file is part of SASM.
**
** SASM is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** SASM is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with SASM.  If not, see <http://www.gnu.org/licenses/>.
**
** Этот файл — часть SASM.
**
** SASM - свободная программа: вы можете перераспространять ее и/или
** изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
** в каком она была опубликована Фондом свободного программного обеспечения;
** либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
** версии.
**
** SASM распространяется в надежде, что она будет полезной,
** но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
** или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
** общественной лицензии GNU.
**
** Вы должны были получить копию Стандартной общественной лицензии GNU
** вместе с этой программой. Если это не так, см.
** <http://www.gnu.org/licenses/>.)
**
****************************************************************************/

#include "common.h"

/**
 * @file common.cpp
 * Contains common functions.
 */

QString Common::applicationDataPath()
{
    QString appDir = QCoreApplication::applicationDirPath();
    #ifdef Q_OS_WIN32
        if (! QFile::exists(appendPath(appDir, "NASM"))) {
            appDir = appendPath(appDir, "Windows");
        }
        return appDir;
    #elif defined(Q_OS_MAC)
        /* The default application directory path for macOS applications
         * is "ABSOLUTE_BUNDLE_PATH/MacOS". We remove "/MacOS", and
         * add the sasm resources path.
         */
        return appendPath(appDir.left(appDir.length() - 6), "Resources/sasm");
    #else
        appDir = appendPath(appDir.left(appDir.length() - 4), "/share/sasm"); //replace /bin with /share/sasm
        if (! QFile::exists(appDir)) {
            appDir = appendPath(appDir, "/share/sasm");
        }
        if (! QFile::exists(appDir)) {
            appDir = appendPath(appDir, "/Unix/share/sasm");
        }
        return appDir;
    #endif
}

QString Common::pathInTemp(QString path)
{
    QString temp = QDir::tempPath();
    QChar lastSymbol = temp[temp.length() - 1];
    if (lastSymbol == QChar('/') || lastSymbol == QChar('\\')) {
        temp.chop(1);
    }
    if (! QFile::exists(temp + "/SASM")) {
        QDir().mkpath(temp + "/SASM");
    }
    QString tempPath = temp + "/SASM";
    if (!path.isEmpty()) {
        tempPath += "/" + path;
    }
    tempPath = QDir::toNativeSeparators(tempPath);
    return tempPath;
}

QString Common::appendPath(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}
