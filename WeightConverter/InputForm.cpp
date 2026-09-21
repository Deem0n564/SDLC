#include "InputForm.h"
#include "WeightModel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

InputForm::InputForm(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ввод данных");

    // Поле ввода веса (QDoubleSpinBox — принимает только числа)
    m_spinWeight = new QDoubleSpinBox(this);
    m_spinWeight->setRange(0.0, 1e9);
    m_spinWeight->setDecimals(4);
    m_spinWeight->setValue(1.0);

    // Два выпадающих списка
    m_cmbInput  = new QComboBox(this);
    m_cmbOutput = new QComboBox(this);

    // Заполняем ComboBox всеми значениями перечисления
    for (int i = 0; i < 8; ++i) {
        MeasurementType t = static_cast<MeasurementType>(i);
        QString name = QString::fromStdString(WeightModel::toRussianString(t));
        m_cmbInput->addItem(name, i);
        m_cmbOutput->addItem(name, i);
    }

    // Кнопки
    QPushButton *btnOk     = new QPushButton("ОК", this);
    QPushButton *btnCancel = new QPushButton("Отмена", this);

    // Компоновка (Layout)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Вес:", this));
    mainLayout->addWidget(m_spinWeight);
    mainLayout->addWidget(new QLabel("Единица ввода:", this));
    mainLayout->addWidget(m_cmbInput);
    mainLayout->addWidget(new QLabel("Единица вывода:", this));
    mainLayout->addWidget(m_cmbOutput);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);
    mainLayout->addLayout(btnLayout);

    // Связываем кнопки с действиями
    connect(btnOk,     &QPushButton::clicked, this, &InputForm::onOkClicked);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

double InputForm::getWeight() const {
    return m_spinWeight->value();
}

MeasurementType InputForm::getInputUnit() const {
    int idx = m_cmbInput->currentData().toInt();
    return static_cast<MeasurementType>(idx);
}

MeasurementType InputForm::getOutputUnit() const {
    int idx = m_cmbOutput->currentData().toInt();
    return static_cast<MeasurementType>(idx);
}

void InputForm::setInitialValues(double weight,
                                 MeasurementType inputUnit,
                                 MeasurementType outputUnit) {
    m_spinWeight->setValue(weight);
    m_cmbInput->setCurrentIndex(static_cast<int>(inputUnit));
    m_cmbOutput->setCurrentIndex(static_cast<int>(outputUnit));
}

void InputForm::onOkClicked() {
    // QDoubleSpinBox уже защищает от некорректного ввода,
    // но проверим, что выбраны обе единицы
    if (m_cmbInput->currentIndex() < 0 || m_cmbOutput->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите единицы измерения!");
        return;
    }
    accept(); // закрывает диалог с кодом Accepted
}