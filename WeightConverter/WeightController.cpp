#include "WeightController.h"
#include "MainView.h"
#include "InputForm.h"
#include <stdexcept>

WeightController::WeightController(WeightModel *model, MainView *view, QObject *parent)
    : QObject(parent), m_model(model), m_view(view) {
    // Подписываемся на сигнал кнопки главного окна
    connect(m_view->inputButton(), &QPushButton::clicked,
            this, &WeightController::onInputButtonClicked);
}

void WeightController::onInputButtonClicked() {
    InputForm form(m_view);

    // Восстанавливаем последние введённые данные
    form.setInitialValues(m_model->getInputValue(),
                          m_model->getInputUnit(),
                          m_model->getOutputUnit());

    // Показываем диалог модально (ShowDialog блокирует основное окно)
    if (form.exec() == QDialog::Accepted) {
        try {
            m_model->applyInput(form.getWeight(),
                                form.getInputUnit(),
                                form.getOutputUnit());
        } catch (const std::invalid_argument &e) {
            m_view->showError(QString::fromUtf8(e.what()));
        }
    }
}