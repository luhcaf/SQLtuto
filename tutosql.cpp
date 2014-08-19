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
QMessageBox::information(this, "Tutorial banco de dados",
"Conexão realizada com sucesso!"
+ ui->edt_esquema->text() + "]\n[" + qry.value(0).toDateTime().toString() + "]" ,
QMessageBox::Ok);
habilitar_query(true);
ui->txt_sql->setFocus();
}
}
void tutosql::desconectar()
{
QSqlDatabase db = QSqlDatabase::database();
db.close();
habilitar_query(false);
ui->edt_schema->setFocus();
}
void tutosql::execSQL()
{
}
void tutosql::habilitarQuery(bool ativo)
{
ui->descbuttbot_desconectarExebutt->setEnabled(ativo);
ui->Edit_txt->setEnabled(ativo);
ui->Edit_txt->setDesabled(ativo);
ui->edt_esquema->setDisabled(ativo);
}
void tutorialSQLITE::enviarQuery()
{
txt_query->clear();
ui->tbl_sql->setModel(NULL);
if(ui->txt_sql->toPlainText().trimmed().isEmpty())
{
QMessageBox::information(this, "Instrução SQL",
"Não há instrução  a ser executada");
ui->txt_sql->setFocus();
return;
}
QString sql = ui->txt_sql->toPlainText();
if (sql.toUpper().startsWith("SELECT"))
{
txt_query->setQuery(sql);
ui->tbl_sql->setModel(txt_query);
if (txt_query->lastError().isValid())
{
QMessageBox::critical(this, "SoQH SQL - ERRO",
txt_query->lastError().text());
ui->txt_sql->setFocus();
return;
}
QMessageBox::information(this, "SoQH SQL",
"Instrução SQL executada.");
}
else
{
QStringList sqls = sql.split(";");
QString strRows;
int numRows = 0;
for (int i = 0; i < sqls.size(); i++)
{
QString tmpSql = sqls.at(i);
if (tmpSql.trimmed().isEmpty())
continue;
QSqlQuery qry;
qry.prepare(sqls.at(i));
if (!qry.exec())
{
strRows.setNum(numRows);
QString numScript;
numScript.setNum(i+1);
QMessageBox::critical(this, "SOQH SQL - ERRO",
"Falha ao executar script [" + numScript + "]\n[" + strRows +
"] linha(s) afetada(s)\n" + qry.lastError().text());
ui->txt_sql->setFocus();
return;
}
 numRows += qry.numRowsAffected();
}
strRows.setNum(numRows);
QMessageBox::information(this, "SOQH SQL",
"Instrução SQL executada com sucesso\n[" + strRows +
"] linha(s) afetadas(s)");
}
}
