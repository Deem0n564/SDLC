#pragma once
#include <QObject>
#include "WeightModel.h"

class MainView;

// Контроллер связывает модель и представление.
class WeightController : public QObject {
    Q_OBJECT
public:
    WeightController(WeightModel *model, MainView *view, QObject *parent = nullptr);

private slots:
    void onInputButtonClicked();  // обработчик нажатия кнопки на главной форме

private:
    WeightModel *m_model;
    MainView    *m_view;
};