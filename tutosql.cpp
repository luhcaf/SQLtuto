#include "tutosql.h"
#include "ui_tutosql.h"
#include <QMessageBox>
#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
sqltest::sqltest(QWidget *parent):
QDialog(parent),
ui(new Ui::sqltest)
{
ui->setupUi(this);
this->setWindowTitle("SQL TESTE");
habilitarQuery(false);
connect (ui->bot_conectar, SIGNAL(clicked()),this, SLOT(conectar()));
connect (ui->bot_desconectar, SIGNAL(clicked()),this, SLOT(desconectar()));
connect (ui->bot_executar, SIGNAL(clicked()),this, SLOT(ExecSQL()));
ui->lineEdit_2->setFocus();
txt_query = new QSqlQueryModel;
}
tutosql::~tutosql()
{
delete ui;
}
void sqltest::Validarcampos()
{
if(ui->lineEdit_2->text().trimmed().isEmpty())
QMessageBox::critical(this, "Erro no Banco", "Digite um nome para o Banco:")
ui->lineEdit_2->setFocus();
void tutosql::conectar()
{
QSqlDatabase db = QSqlDatabase::addDatabase("SQLLITE");
db.setDatabaseName(ui->edt_esquema->text().trimmed());
if (!db.open())
{
QMessageBox::critical(this, "Error",
"Falha na conexão com o BD [" + ui->edt_esquema->text() + "]\n" + db.lastError().text(),
QMessageBox::Cancel);
return;
}
