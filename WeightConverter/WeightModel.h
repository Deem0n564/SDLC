#pragma once
#include <map>
#include <string>
#include <vector>
#include "MeasurementType.h"
#include "ModelChangeListener.h"

// Модель хранит данные и содержит бизнес-логику (конвертацию).
// Активная модель: при изменении состояния уведомляет подписчиков.
class WeightModel {
public:
    WeightModel();

    void addListener(ModelChangeListener *listener);
    void removeListener(ModelChangeListener *listener);

    // Геттеры и сеттеры для входных данных и результата
    double getInputValue() const;
    void setInputValue(double value);

    MeasurementType getInputUnit() const;
    void setInputUnit(MeasurementType unit);

    MeasurementType getOutputUnit() const;
    void setOutputUnit(MeasurementType unit);

    double getResult() const;

    // Запись данных, конвертация и оповещение представления
    void applyInput(double value, MeasurementType inputUnit, MeasurementType outputUnit);

    // Основной метод — выполняет конвертацию
    void convert();

    // Вспомогательные статические методы: преобразование enum в строку
    static std::string toRussianString(MeasurementType unit);

private:
    // Словарь: каждой единице соответствует коэффициент перевода в килограммы
    std::map<MeasurementType, double> m_conversion;

    double m_inputValue = 0.0;
    MeasurementType m_inputUnit = MeasurementType::Kilogram;
    MeasurementType m_outputUnit = MeasurementType::Pound;
    double m_result = 0.0;

    std::vector<ModelChangeListener *> m_listeners;

    void notifyListeners();
};