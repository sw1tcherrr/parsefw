# Описание массивов в Kotlin

### Токены

```text
VAR = var
ID = /[a-zA-Z_]\w*/
:
;
<
>
,
EOF
```

### Граммматика

(не требует исправлений)

```text
Program       -> Declaration EOF
Declaration   -> VAR VariableList ;
VariableList  -> Variable MaybeListTail
MaybeListTail -> , VariableList
MaybeListTail -> EPS
Variable      -> ID : ID < Type >
Type          -> ID 
```

### FIRST

A | First(A)
-----|-------
Program       |   VAR
Declaration   |   VAR
VariableList  |   ID
MaybeListTail |   , EPS
Variable      |   ID
Type          |   ID

### FOLLOW

A | Follow(A)
--|----------
Program       |   EOF
Declaration   |   EOF
VariableList  |   ;
MaybeListTail |   ;
Variable      |   , ;
Type          |   >

### Тесты

##### Корректность AST

`var _Xa1 : Array<Int>;`

##### Не Array

`var x : Type<Int>;`

##### Несбалансированные скобки

`var x : Array < Int ;`

##### Нет ;

`var x : Array<Int>`

##### Лишнее после ;

`var x : Array<Int>; var y`

##### Неожиданный символ

`var x : ! Array<Int>;`

##### id с цифры

`var 1 : Array<Int>;`

### Демо

- Чтение из файла с многострочным инпутом
- Лог токенов с информацией о строке и позиции
- Генерация graphviz
  
test.txt

```text
var 
   x : 
    Array 
  <Int>
                ;
```

