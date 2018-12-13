#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QStringList>
#include <QProcess>
#include <fstream>
#include "includestree.h"
#include <QFileInfo>

class FileHandler
{
public:
    FileHandler(QFileInfo fi);
    ~FileHandler();

    QString toGraphviz()const;

private:
    void getIncludesTree();
    QString recursiveToGraphviz(IncludesTree*)const;
    int levelOfItemInTree(QString& item)const;
    IncludesTree* getIncludesTree(int& i,int level1);

    IncludesTree* m_tree;
    QStringList m_allIncludes;
    QFileInfo m_file;
    QStringList m_userIncludes;
    QStringList m_userIncludesTree;
};


#endif // FILEHANDLER_H
