#include "filehandler.h"
#include <QString>

FileHandler::FileHandler(QString absolutePath)
{
    m_absolutePath = absolutePath;

    //retrieving the user includes and includes tree
    QProcess process;
    QString command("gcc -H -MM " + m_absolutePath);
    process.start(command);
    process.waitForFinished();

    QString err(process.readAllStandardError());
    QString out(process.readAllStandardOutput());
    process.close();

    // preparing for parsing
    m_allIncludes = err.split("\r\n");
    m_tree = new IncludesTree(m_absolutePath.
        split("\\").last());
    m_userIncludes = out.remove("main.o: ").
        replace(" \\\r\n ","\r\n").
        replace(QRegExp(" (?=[a-zA-Z\\/])"),"\r\n").
        split(QRegExp("\r\n(?=.)"));
    m_userIncludes.last().remove("\r\n");

    // parsing with recursive functions
    getIncludesTree();
}

void FileHandler::getIncludesTree()
{
    m_tree->addChild(new IncludesTree(
        m_allIncludes[0].split("/").last()));
    int i = 1;  //m_allIncludes iterator
    int j = 1;  //m_userIncludes iterator
    int level;
    while((level=levelOfItemInTree(m_allIncludes[i]))>0)
    {
        if(level>=2)
        {
            QString a = m_allIncludes[i].
                replace("/","\\").split("\\").last();
            QString b = m_userIncludes[j].
                split("\\").last();
            if(a==b)
            {
                m_tree->children().last()->
                    addChild(getIncludesTree(i,j,2));
            }
            ++i;
        }
        // if level equals 1
        else{
            QString a = m_allIncludes[i].replace("/","\\").
                split("\\").last();
            QString b = m_userIncludes[j].split("\\").last();
            m_tree->addChild(new IncludesTree(a));
            if(a==b)
            {
                ++j;
            }
            ++i;
        }
    }
}

IncludesTree* FileHandler::getIncludesTree(int& i,int& j,int level1)
{
    int level2;
    QString a = m_allIncludes[i].replace("/","\\").
        split("\\").last();
    IncludesTree* res = new IncludesTree(a);
    ++i;
    ++j;
    a = m_allIncludes[i].replace("/","\\").
        split("\\").last();
    if(j<m_userIncludes.length())
    {
        QString b = m_userIncludes[j].split("\\").last();
        while( (level2 = levelOfItemInTree(m_allIncludes[i]))>level1
               && a==b)
        {
            res->addChild(getIncludesTree(i,j,level2));
        }
    }
    return res;
}

int FileHandler::levelOfItemInTree(QString& item)const
{
    int i = 0;
    while(item[i]==".")
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
