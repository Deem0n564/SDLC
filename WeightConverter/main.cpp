#include <QApplication>
#include "WeightModel.h"
#include "MainView.h"
#include "WeightController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WeightModel model;
    MainView view(&model);
    WeightController controller(&model, &view);

    view.show();
    return app.exec();
}