#pragma once

enum EInputCommand : size_t
{
	eIC_GoLeft = 0,
	eIC_GoRight,
	eIC_Jump,
	eIC_Shoot, 
	eIC_Max
};


/*
* Перечисление EInputCommand определяет именованные значения для различных входных команд. В данном случае, 
* перечисление определяет следующие именованные значения (элементы перечисления):
- eIC_GoLeft = 0: команда для движения влево.
- eIC_GoRight: команда для движения вправо.
- eIC_Jump: команда для прыжка.
- eIC_Shoot: команда для стрельбы.
* Также перечисление содержит элемент eIC_Max, который служит для индикации максимального значений элементов перечисления.
* Используя это перечисление, можно создавать переменные и передавать значения этих команд для управления игровым персонажем 
* или взаимодействия с игровым миром.
*/