#ifndef TUTOSQL_H
#define TUTOSQL_H
#include <QDialog>
#include <QSqlQueryModel>
namespace Ui {
class tutosql;
}
class tutosqç : public QDialog
{
Q_OBJECT
public slots:
void connect();
void desconnect();
public:
explicit tutosql(QWidget *parent = 0);
~tutosql();
private:
Ui::tutosql *ui;
QSqlQueryModel *txt_query;
void habilitarQuery(bool ativo);
void valoresIniciais();
};
#endif
