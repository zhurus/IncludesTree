#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H
#include <QVector>
#include "graph.h"

class IncludesTree
{
public:
    IncludesTree(QString treename);

    void addChild(IncludesTree* child);
    QVector <IncludesTree*> children()const;
    QString filename()const;
private:
    QVector <IncludesTree*> m_children;
    QString m_treename;
};

#endif // INCLUDEFILE_H
