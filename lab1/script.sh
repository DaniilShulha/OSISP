#!/bin/bash

# Размер окна консоли
COLUMNS=$(tput cols)
LINES=$(tput lines)

# Функция для очистки экрана
clear_screen() {
    tput clear
}

# Генератор случайных чисел (мультипликативный)
random_generator() {
    seed=$(( $(date +%s) % 1000 ))
    multiplier=1103515245
    increment=12345
    modulus=2147483648
    seed=$(( (seed * multiplier + increment) % modulus ))
    echo $((seed % $1))
}

# Функция для отображения часов
show_clock() {
    local x=$1
    local y=$2
    local time=$(date +%H:%M:%S)
    tput cup "$y" "$x" # Установить курсор в нужную позицию
    echo -e "\033[1;32m$time\033[0m" # Зеленый цвет для часов
}

# Инициализация генератора
seed=$(date +%s)

# Начальные координаты
x=$(random_generator $((COLUMNS - 8)))
y=$(random_generator $((LINES - 1)))

# Счетчик для смены позиции
counter=0

clear_screen
# Основной цикл программы
while true; do
    
    # Отображение часов в текущей позиции
    show_clock "$x" "$y"
    
    # Увеличение счетчика
    ((counter++))
    
    # Смена позиции каждые 10 секунд
    if [ $counter -ge 10 ]; then
        x=$(random_generator $((COLUMNS - 8)))
        y=$(random_generator $((LINES - 1)))
        counter=0
	clear_screen
    fi
    
    # Задержка 1 секунда для обновления времени
    sleep 1
done

# Восстановление терминала при выходе
trap 'tput cnorm; clear; exit' INT TERM