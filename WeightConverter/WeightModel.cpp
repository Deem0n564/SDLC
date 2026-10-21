#include "WeightModel.h"
#include <stdexcept>

void WeightModel::addListener(ModelChangeListener *listener) {
    if (listener) {
        m_listeners.push_back(listener);
    }
}

void WeightModel::removeListener(ModelChangeListener *listener) {
    for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
        if (*it == listener) {
            m_listeners.erase(it);
            return;
        }
    }
}

void WeightModel::notifyListeners() {
    for (ModelChangeListener *listener : m_listeners) {
        listener->onModelChanged();
    }
}

WeightModel::WeightModel() {
    // Заполняем словарь коэффициентами (всё приводится к килограммам)
    m_conversion[MeasurementType::Kilogram]  = 1.0;
    m_conversion[MeasurementType::Pound]     = 0.453592;
    m_conversion[MeasurementType::PolarBear] = 500.0;
    m_conversion[MeasurementType::Elephant]  = 6000.0;
    m_conversion[MeasurementType::Zhiguli]   = 1000.0;
    m_conversion[MeasurementType::BeerCan]   = 0.5;
    m_conversion[MeasurementType::Chicken]   = 1.5;
    m_conversion[MeasurementType::PaperSheet]= 0.005;
}

double WeightModel::getInputValue() const { return m_inputValue; }
void WeightModel::setInputValue(double value) { m_inputValue = value; }

MeasurementType WeightModel::getInputUnit() const { return m_inputUnit; }
void WeightModel::setInputUnit(MeasurementType unit) { m_inputUnit = unit; }

MeasurementType WeightModel::getOutputUnit() const { return m_outputUnit; }
void WeightModel::setOutputUnit(MeasurementType unit) { m_outputUnit = unit; }

double WeightModel::getResult() const { return m_result; }

void WeightModel::applyInput(double value, MeasurementType inputUnit, MeasurementType outputUnit) {
    if (value < 0.0) {
        throw std::invalid_argument("Вес не может быть отрицательным");
    }
    m_inputValue = value;
    m_inputUnit = inputUnit;
    m_outputUnit = outputUnit;
    convert();
    notifyListeners();
}

void WeightModel::convert() {
    // 1. Переводим входное значение в килограммы
    double inKg = m_inputValue * m_conversion[m_inputUnit];
    // 2. Из килограммов — в целевую единицу
    m_result = inKg / m_conversion[m_outputUnit];
}

// Преобразование enum в русское название (для отображения в UI)
std::string WeightModel::toRussianString(MeasurementType unit) {
    switch (unit) {
        case MeasurementType::Pound:      return "фунт";
        case MeasurementType::Kilogram:   return "кг";
        case MeasurementType::PolarBear:  return "белый медведь";
        case MeasurementType::Elephant:   return "африканский слон";
        case MeasurementType::Zhiguli:    return "жигули";
        case MeasurementType::BeerCan:    return "банка пива";
        case MeasurementType::Chicken:    return "цыплёнок";
        case MeasurementType::PaperSheet: return "лист бумаги";
    }
    return "?";
}