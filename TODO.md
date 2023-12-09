Примеры:

- [ ] токен инта, флоата
- [ ] аттрибутно транслирующий калькулятор
- [ ] добавить в грамматику kotlin_func дженерик со многими параметрами `T<K, V, W>`
- [ ] добавить в грамматику kotlin_func дефолтное значение параметра (инт) `f(a: T = 5)`

Core:

- [x] аналог LLVM MemoryBuffer - обертка над готовым буфером (строкой), или memory mapped файлом => дает bidirectional итераторы
  - stdin не поддерживаем
  - `llvm::MemoryBuffer`
  - `boost::iostreams::mapped_file`
  - `wheels::ConstMemView`
- [x] буфер должен жить все время работы с парсером и AST => `string_value` токенов это `string_view` в буфер
  - решает `todo dont store string_value if it is equal to pattern`
- [x] токен знает, с какого байта начинается => хранить доп инфу про \n => уметь мапить токены в source location
- [x] рефакторить Children в AST
- [x] замена `optional` на `expected`
- [x] замена `std::regex` на `ctre` => токены имеют `static constexpr` не паттерн, а скомпилированный регекс

- [x] добавить Visit в LangNodeBase
- [x] конструкторы для токенов от string_value и тп
- [ ] не бросать в NextToken
- [ ] cmake и структура папок (target_include_directories)
- [ ] camelCase для функций в clang tidy

Тесты:

- [x] декларативное построение AST
- [ ] сравнение AST
- [ ] google test
