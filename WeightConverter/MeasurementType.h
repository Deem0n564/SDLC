#pragma once

// Перечисление всех доступных единиц измерения.
// enum class — «строгий» enum: обращаться нужно как MeasurementType::Pound
enum class MeasurementType {
    Pound,        // фунт
    Kilogram,     // килограмм
    PolarBear,    // белый медведь
    Elephant,     // африканский слон
    Zhiguli,      // жигули
    BeerCan,      // банка пива
    Chicken,      // цыплёнок
    PaperSheet    // лист бумаги
};