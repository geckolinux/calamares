/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TranslatableConfiguration.h"

#include "LabelModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace CalamaresUtils
{
namespace Locale
{
TranslatedString::TranslatedString(const QString& string)
{
    m_strings[QString()]=string;
}
TranslatedString::TranslatedString(const QVariantMap& map, const QString& key)
{
    // Get the un-decorated value for the key
    QString value = CalamaresUtils::getString( map, key );
    if ( value.isEmpty() )
    {
        value = key;
    }
    m_strings[QString()] = value;
    
    for ( auto it = m_strings.constKeyValueBegin(); it != m_strings.constKeyValueEnd(); ++it )
    {
        QString subkey = (*it).first;
        if ( subkey == key )
        {
            // Already obtained, above
        }
        else if ( subkey.startsWith( key ) )
        {
            QRegularExpressionMatch match;
            if ( subkey.indexOf( QRegularExpression("\\[([a-zA-Z_@]*)\\]"), 0, &match ) > 0 )
            {
                QString language = match.captured(1);
                cDebug() << "Found translation" << key << '[' << language << ']';
            }
        }
    }
}

}  // namespace Locale
}  // namespace CalamaresUtils
