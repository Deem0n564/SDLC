#pragma once
#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include "MeasurementType.h"

// Диалоговое окно ввода. Отвечает ТОЛЬКО за ввод данных.
class InputForm : public QDialog {
    Q_OBJECT   // обязательный макрос для любого класса с сигналами/слотами
public:
    explicit InputForm(QWidget *parent = nullptr);

    // Публичные методы, чтобы контроллер мог забрать введённые данные
    double getWeight() const;
    MeasurementType getInputUnit() const;
    MeasurementType getOutputUnit() const;

    // Метод для восстановления последних введённых значений
    void setInitialValues(double weight,
                          MeasurementType inputUnit,
                          MeasurementType outputUnit);

private slots:
    void onOkClicked();   // обработчик нажатия «ОК»

private:
    QDoubleSpinBox *m_spinWeight;   // поле ввода числа
    QComboBox      *m_cmbInput;     // единица ввода
    QComboBox      *m_cmbOutput;    // единица вывода
};