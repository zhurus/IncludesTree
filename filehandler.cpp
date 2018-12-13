#include "filehandler.h"
#include <QString>
#include "mainwindow.h"

FileHandler::FileHandler(QFileInfo file)
{
    m_file = file;

    //retrieving the user includes and includes tree
    QProcess process;
    process.setWorkingDirectory(m_file.absolutePath());
    QString command("gcc -H -MM " + m_file.fileName());
    process.start(command);
    process.waitForFinished();

    QString err(process.readAllStandardError());
    QString out(process.readAllStandardOutput());
    process.close();

    if(err.length() ==0 || err.at(0)!='.')
    {
        throw MainWindow::wrongFile();
    }
    // preparing for parsing
    m_allIncludes = err.remove(" ").split("\r\n");
    if(m_allIncludes.last().isEmpty())
    {
        m_allIncludes.removeLast();
    }

    m_tree = new IncludesTree(m_file.fileName());
    m_userIncludes = out.remove(m_file.baseName()+".o: ").
        replace(" \\\r\n ","\r\n").
        replace(QRegExp(" (?=[a-zA-Z\\/])"),"\r\n").
        split(QRegExp("\r\n(?=.)"));
    m_userIncludes.last().remove("\r\n");

    // parsing with recursive functions
    getIncludesTree();

}

FileHandler::~FileHandler()
{
    delete m_tree;
}

void FileHandler::getIncludesTree()
{
    int i = 0;
    int j = 1;
    int level;

    while(i!=m_allIncludes.length() &&
          m_allIncludes[i].at(0)=='.')
    {
        QString a  = QFileInfo(QString(m_allIncludes[i])
            .remove(QRegExp("^\\.+")))
            .fileName();

        QString b = QFileInfo(m_userIncludes[j]).fileName();

        if(a==b)
        {
            j++;
            i++;
        }
        else
        {
            m_allIncludes.removeAt(i);
        }
    }

    while(i!=m_allIncludes.length())
    {
        m_allIncludes.removeAt(i);
    }

    i = 0;
    while(i<m_allIncludes.length())
    {
        level = levelOfItemInTree(m_allIncludes[i]);
        m_tree->addChild(getIncludesTree(i,level));
    }
}

IncludesTree* FileHandler::getIncludesTree(int& i,int level1)
{
    QString a  = QFileInfo(QString(m_allIncludes[i])
        .remove(QRegExp("^\\.+")))
        .fileName();

    IncludesTree* res = new IncludesTree(a);
    ++i;
    int level2;
    if(i<m_allIncludes.length())
    {
        a  = QFileInfo(QString(m_allIncludes[i])
                .remove(QRegExp("^\\.+")))
                .fileName();
        while(i<m_allIncludes.length()&&
              (level2 = levelOfItemInTree(m_allIncludes[i]))>level1)
        {
            res->addChild(getIncludesTree(i,level2));
        }
    }

    return res;
}

int FileHandler::levelOfItemInTree(QString& item)const
{
    int i = 0;
    while(item[i]=='.')
    {
        i++;
    }
    return i;
}

QString FileHandler::toGraphviz()const
{
    QString result;
    result.append("graph{\r\n");
    result.append(recursiveToGraphviz(m_tree));
    result.append("}");

    return result;
}

QString FileHandler::recursiveToGraphviz(IncludesTree* tree)const
{
    QString result;
    for(auto child:tree->children())
    {
        result.append(
            tree->filename() + "--" +
            child->filename() + "\r\n");
        result.append(recursiveToGraphviz(child));
    }
    return result;
}
