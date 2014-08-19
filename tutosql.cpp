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
"Falha na conexão com o banco de dados." + ui->edt_esquema->text() + "]\n" + db.lastError().text(),
QMessageBox::Cancel);
return;
}
 QSqlQuery qry;
qry.prepare("SELECT datetime('now')");
if (!qry.exec()){
QString erro = qry.lastError().text();
QMessageBox::critical(this, "Falha",
"Falha ao preparar consulta do BD" + erro + "\n",
QMessageBox::Cancel);
}
else if (qry.next())
QMessageBox::information(this, "Banco Tutorial",
"Conexão realizada com sucesso com o Banco ["
+ ui->edt_schema->text() + "]\n[" + qry.value(0).toDateTime().toString() + "]" ,
QMessageBox::Ok);
habilitar_query(true);
ui->txt_sql->setFocus();
}
}
void sqltest::desconectar()
{
QSqlDatabase db = QSqlDatabase::database();
db.close();
habilitar_query(false);
ui->edt_schema->setFocus();
}
void sqltest::exeSQL()
{
}
void sqltest::habilitarQuery(bool ativo)
{
ui->descbutt->setEnabled(ativo);
ui->Exebutt->setEnabled(ativo);
ui->plainTextEdit->setEnabled(ativo);
ui->plainTextEdit->setDesabled(ativo);
ui->edt_schema->setDisabled(ativo);
}
