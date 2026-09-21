#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ModelChangeListener.h"

class WeightModel;

// Главное окно. Отвечает только за отображение.
class MainView : public QWidget, public ModelChangeListener {
    Q_OBJECT
public:
    explicit MainView(WeightModel *model, QWidget *parent = nullptr);

    void onModelChanged() override;

    void showError(const QString &message);

    // Публичная кнопка, чтобы контроллер мог подписаться на её сигнал
    QPushButton *inputButton() const { return m_btnInput; }

private:
    void updateFromModel();

    WeightModel *m_model;
    QPushButton *m_btnInput;
    QLabel      *m_lblInputInfo;
    QLabel      *m_lblResult;
};