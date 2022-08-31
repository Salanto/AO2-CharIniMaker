#include "ini_handler.h"

#include <QDebug>

INIHandler::INIHandler(QString f_ini_fullpath)
{
    if (f_ini_fullpath.isEmpty()) {
        qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                   << "error : empty path passed during config loading.";
        return;
    }

    QSettings m_char_ini(f_ini_fullpath, QSettings::IniFormat);
    if (m_char_ini.status() != QSettings::NoError) {
        switch (m_char_ini.status()) {
        case QSettings::AccessError:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: failed to open file; aborting (" << m_char_ini.fileName() << ")";
            break;

        case QSettings::FormatError:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: file is malformed; aborting (" << m_char_ini.fileName() << ")";
            break;

        default:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: unknown error; aborting; aborting (" << m_char_ini.fileName() << ")"
                       << "error code:" << m_char_ini.status();
            break;
        }
        return;
    }
    return;
}
