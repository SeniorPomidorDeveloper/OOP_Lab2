# Лабораторная работа по ООП №1

## Вариант 7 - игральные кости

### Простой класс

Игральная кость – определяется выпавшим значением от 1 до 6 (либо
другой диапазон по вашему желанию) и вероятностью выпадения каждого из значений (у
“честной” кости все значения имеют вероятность 1/6, однако кость может быть
взвешенной). Сумма вероятностей должна равняться 1 с учётом погрешности работы с
числами с плавающей запятой.

#### Методы простого класса (помимо общих):

* создание экземпляра класса с инициализацией выпавшим значением и
  вероятностями выпадения сторон (вероятности должны иметь значение по
  умолчанию, приводящее к созданию “честной” кости);

- создание экземпляра класса с инициализацией случайным значением и
  вероятностями выпадения сторон (вероятности должны иметь значение по
  умолчанию, приводящее к созданию “честной” кости) (допустимо использование
  static метода вместо конструктора);
- генерация случайного значения для кости с учётом вероятностей (с помощью
  генератора случайных чисел);
- (==) сравнение двух костей;
- форматирование значения кости в виде ascii-арта.

### Сложный класс

Группа костей – определяется массивом игральных костей и размером
этого массива.

#### Методы сложного класса:

- создание экземпляров класса с инициализацией количеством “честных” костей,
  которые заполняются случайными значениями (допустимо использование static
  метода вместо конструктора);
- создание экземпляров класса с инициализацией количеством “честных” костей и
  массивом их начальных значений;
- ( () ) выполнение операции “бросить кости” (получить новые случайные значения
  всех костей);
- ( () ) перебросить кость с заданным номером;
- (+=) добавление кости к группе;
- (-=) изъятие из группы кости (всех костей) с заданным значением, если она есть в
  группе;
- ([]) получение кости в группе по её номеру (возврат по ссылке);
- подсчёт суммы очков в группе костей;
- проверка есть ли в группе кость с заданным значением;
- форматирование группы костей в виде ascii-арта.

## Инструкция по сборке

Чтобы собрать прикладную программу используйте cmake без опций.

Чтобы собрать тесты используйте cmake c опцией `BUILD_TEST`.