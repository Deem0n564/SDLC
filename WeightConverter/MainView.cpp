#include "MainView.h"
#include "WeightModel.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainView::MainView(WeightModel *model, QWidget *parent)
    : QWidget(parent), m_model(model) {
    m_model->addListener(this);
    setWindowTitle("Конвертер веса");
    resize(300, 200);

    m_btnInput     = new QPushButton("Ввести данные", this);
    m_lblInputInfo = new QLabel("Введённые данные: —", this);
    m_lblResult    = new QLabel("Результат: —", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_lblInputInfo);
    layout->addWidget(m_lblResult);
    layout->addWidget(m_btnInput);
}

void MainView::onModelChanged() {
    updateFromModel();
}

void MainView::updateFromModel() {
    QString inputInfo = QString("Введено: %1 %2 → перевод в %3")
        .arg(m_model->getInputValue())
        .arg(QString::fromStdString(
            WeightModel::toRussianString(m_model->getInputUnit())))
        .arg(QString::fromStdString(
            WeightModel::toRussianString(m_model->getOutputUnit())));

    QString resultInfo = QString("Результат: %1")
        .arg(m_model->getResult());

    m_lblInputInfo->setText(inputInfo);
    m_lblResult->setText(resultInfo);
}

void MainView::showError(const QString &message) {
    QMessageBox::warning(this, "Ошибка", message);
}