#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariantMap>

namespace mtg {

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        Settings(const QString filename, QObject *parent = 0);

        bool load();
        bool save();
        void dump();
        void merge(QVariantMap *defaults);
        QVariantMap *getMap();

    private:
       // void recursiveMerge(QVariantMap *source, QVariantMap *dest);

        QVariantMap map;
        QString filename;

    };

}

#endif // SETTINGS_H
