#include "includestree.h"

IncludesTree::IncludesTree(QString treename)
{
    m_treename = treename;
}

void IncludesTree::addChild(IncludesTree* child)
{
    m_children.append(child);
}

QVector <IncludesTree*> IncludesTree::children()const
{
    return m_children;
}

QString IncludesTree::filename() const
{
    return m_treename;
}
