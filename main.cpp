#include "tutosql.h"
#include <QtWidgets>

int main (int argc, char *argv[]){
QApplication app (argc, argv);
tutosql form;
form.show();
return app.exec();

}
