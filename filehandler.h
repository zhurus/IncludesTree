#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QStringList>
#include <QProcess>
#include <fstream>
#include "IncludesTree.h"

class FileHandler
{
public:
    FileHandler(QString absolutePath);

    void getIncludesTree();
    QString toGraphviz()const;

private:
    QString recursiveToGraphviz(IncludesTree*)const;
    int levelOfItemInTree(QString& item)const;
    IncludesTree* getIncludesTree(int& i,int& j,int level1);

    IncludesTree* m_tree;
    QStringList m_allIncludes;
    QString m_absolutePath;
    QStringList m_userIncludes;
};


#endif // FILEHANDLER_H
