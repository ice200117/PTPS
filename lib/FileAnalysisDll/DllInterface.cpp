#include "DllInterface.h"
#include "fileanalysisdll.h"

#include <QDir>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QString>
#include <QCoreApplication>
#include <QTextCodec>

#include  <unistd.h>

//bool execArge( char * iniFileName, char * readADataPath )
//char* execArge( char * iniFileName, char * readADataPath )
int execArge( char * iniFileName, char * readADataPath )
{
    printf("%s,   %s\n", iniFileName, readADataPath );
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	{
		/////////check ini///////////////////
		QString qstrIniFileNmae = QString(iniFileName);
		QFileInfo checkIni(qstrIniFileNmae);
		if (!checkIni.isFile() || !checkIni.exists()) return false;
		QString sss = checkIni.absolutePath() + "/Plugin";
		qApp->addLibraryPath(sss);
		FileAnalysisDll tmpFADLL(qstrIniFileNmae);
		tmpFADLL.m_strLogPath = checkIni.absolutePath();
		tmpFADLL.m_strXmlName = "XmlFile.xml";

		//////////handle arge/////////////////
		QStringList newFileList;
		if (!tmpFADLL.getNewFile(QString(readADataPath),newFileList)) return false;
		for (int i = 0;i < newFileList.size();i++)
		{
			if (!tmpFADLL.analysis_files(newFileList[i])) return false;
		}

		//////////handle arge/////////////////
		//QString qstrFADLL = QString(readADataPath);
		//QDir handleDir(qstrFADLL);
		//if (!handleDir.exists()) return false;
		//QStringList filter;
		//filter<<"*.txt";
		//handleDir.setNameFilters(filter);
		//QFileInfoList fileInfo = handleDir.entryInfoList(filter);
		//for (int iFileIndex = 0;iFileIndex < fileInfo.size();iFileIndex++)
		//{
		//	QFileInfo qCurFI = fileInfo[iFileIndex];
		//	QString strCurFile = qCurFI.absoluteFilePath();
		//	if (!tmpFADLL.analysis_files(strCurFile,qCurFI.absolutePath())) return false;
		//	//QString strTgtFile = qCurFI.absolutePath() + "/tempDir/" + qCurFI.fileName();
		//	//if (!QFile::copy(strCurFile,strTgtFile)) return false;
		//	//if (!tmpFADLL.analysis_files(strTgtFile,qCurFI.absolutePath())) return false;
		//}
		//for (int iFileIndex = 0;iFileIndex < fileInfo.size();iFileIndex++)
		//{
		//	QFileInfo qCurFI = fileInfo[iFileIndex];
		//	QString strCurFile = qCurFI.absoluteFilePath();
		//	if (!QFile::remove(strCurFile)) return false;
		//}
	}

    //return true;
    //return "Successful";
    printf("output = 111\n\n");
    return 111;
}

int main(int argc, char *argv[])
{

    printf("main ---  %s, %s\n", argv[1], argv[2]);
    execArge(argv[1], argv[2]);
    sleep(10);
    return 0;
}
