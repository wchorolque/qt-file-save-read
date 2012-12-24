#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QCoreApplication>
#include <QTranslator>

QTextStream cout(stdout);
QTextStream cerr(stderr);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTranslator translator;
    translator.load("i18n_es");
    app.installTranslator(&translator);

    QString str;
    QString newstr;
    QTextStream strbuf(&str);

    int lucky = 7;
    float pi = 3.14;
    double e = 2.71;

    cout << QCoreApplication::translate("main", "An in-memory stream") << endl;
    strbuf << QCoreApplication::translate("main", "luckynumber:") << lucky << endl
        << QCoreApplication::translate("main", "pi: ") << pi << endl
        << QCoreApplication::translate("main", "e: ") << e << endl;

    cout << str;

    QFile data("mydata");
    data.open(QIODevice::WriteOnly);
    QTextStream out(&data);
    out << str;
    data.close();

    cout << QCoreApplication
            ::translate("main", "Read data from the file - watch for errors.")
         << endl;
    if (data.open(QIODevice::ReadOnly)) {
        QTextStream in(&data);
        int lucky2;
        in >> newstr >> lucky2;
        if (lucky != lucky2) {
            cerr << QCoreApplication::translate("main", "ERROR: Wrong")
                 << newstr << lucky2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }

        float pi2;
        in >> newstr >> pi2;
        if (pi2 != pi) {
            cerr << QCoreApplication::translate("main", "ERROR: Wrong")
                 << newstr << pi2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }

        double e2;
        in >> newstr >> e2;
        if (e2 != e) {
            cerr << QCoreApplication::translate("main", "ERROR: Wrong")
                 << newstr << e2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }
        data.close();
    }

    cout << QCoreApplication::translate("main", "Read from file line-by-line")
         << endl;
    if (data.open(QIODevice::ReadOnly)) {
        QTextStream in(&data);
        while (not in.atEnd()) {
            newstr = in.readLine();
            cout << newstr << endl;
        }
        data.close();
    }

    return app.exec();
}
