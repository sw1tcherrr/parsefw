Примеры:
-[ ] токен инта, флоата
-[ ] аттрибутно транслирующий калькулятор
-[ ] добавить в грамматику kotlin_func дженерик со многими параметрами `T<K, V, W>`
-[ ] добавить в грамматику kotlin_func дефолтное значение параметра (инт) `f(a: T = 5)`

Core:
-[ ] аналог LLVM MemoryBuffer - обертка над готовым буфером (строкой), или memory mapped файлом => дает bidirectional итераторы
  - stdin не поддерживаем
  - `llvm::MemoryBuffer`
  - `boost::iostreams::mapped_file`
  - `wheels::ConstMemView`
-[ ] буфер должен жить все время работы с парсером и AST => `string_value` токенов это `string_view` в буфер
  -  решает `todo dont store string_value if it is equal to pattern`
-[ ] токен знает, с какого байта начинается => хранить доп инфу про \n => уметь мапить токены в source location
-[ ] рефакторить владение в AST
-[ ] замена `optional` на `expected`
-[ ] замена `std::regex` на `ctre` => токены имеют `static constexpr` не паттерн, а скомпилированный регекс 

Тесты:
-[ ] ???
