#include "InputHandler.h"

#include <windows.h>
#include <algorithm>
#include <cassert>

InputHandler::InputHandler()
{
	m_strMapFilePath = "../../../Assets/Configs/actionmap.ini";
	std::replace(m_strMapFilePath.begin(), m_strMapFilePath.end(), '\\', '/');

	MapSymbol("a", 'A');
	MapSymbol("d", 'D');
	MapSymbol("left", VK_LEFT);
	MapSymbol("right", VK_RIGHT);
	MapSymbol("space", VK_SPACE);
  
  MapCommandSymbol("GoLeft", eIC_GoLeft, "a");
  MapCommandSymbol("GoRight", eIC_GoRight, "d");
  MapCommandSymbol("Jump", eIC_Jump, "space");
  MapCommandSymbol("Shoot", eIC_Shoot, "left");
  
  LoadConfiguration();
  
	Remap();
}

bool InputHandler::IsKeyDown(size_t vk_key)
{
	if (GetAsyncKeyState(vk_key) & 0x8000)
		return true;

	return false;
}

void InputHandler::MapSymbol(std::string strSymbol, size_t nSymbol)
{
	m_symbolMap[strSymbol] = nSymbol;
}

void InputHandler::MapInputEvent(std::size_t nSymbol, size_t nCommand)
{
	m_inputEventMap[nSymbol] = nCommand;
}

void InputHandler::MapCommandSymbol(std::string strCommand, size_t nCommand, std::string strDefaultSymbol)
{
	m_commandMap[strCommand] = nCommand;
	m_commandSymbolMap[strCommand] = strDefaultSymbol;
}

void InputHandler::Remap()
{
	for (auto& it : m_commandSymbolMap)
	{
		MapInputEvent(m_symbolMap[it.second], m_commandMap[it.first]);
	}
}

// We used int as return type just for demonstration. It should be done another way
void InputHandler::Update()
{
	for (auto& it : m_inputEventMap)
	{
		m_InputState.set(it.second, IsKeyDown(it.first));
	}
}

const std::bitset<eIC_Max>& InputHandler::GetInputState() const
{
	return m_InputState;
}

void InputHandler::LoadConfiguration()
{
	INIReader reader(m_strMapFilePath.c_str());
	assert(reader.ParseError() >= 0);
	auto fields = reader.GetFields("Keyboard");

	for (auto& field : fields)
	{
		std::string strCommand = field;
		std::string strSymbol = reader.Get("Keyboard", field, "");

		m_commandSymbolMap[strCommand] = strSymbol;
	}
}


/*
- InputHandler(): конструктор класса, инициализирует пути к файлу с конфигурацией и выполняет связывание символов с командами,
  а также загружает конфигурацию и выполняет привязку команд к символам.
- IsKeyDown(size_t vk_key): возвращает состояние нажатия клавиши. Если клавиша нажата, возвращает true, иначе false.
- MapSymbol(std::string strSymbol, size_t nSymbol): связывает символ с кодом символа.
- MapInputEvent(std::size_t nSymbol, size_t nCommand): связывает символ ввода с командой.
- MapCommandSymbol(std::string strCommand, size_t nCommand, std::string strDefaultSymbol): связывает команду с символом и 
  устанавливает символ по умолчанию.
- Remap(): перепривязывает команды к символам на основе текущих связей команд и символов.
- Update(): обновляет состояние ввода для всех связанных команд в соответствии с текущим состоянием символов.
- GetInputState(): возвращает состояние ввода в виде std::bitset<eIC_Max>, где каждый бит представляет состояние определенной 
  команды.
- LoadConfiguration(): загружает конфигурацию символов и команд из файла actionmap.ini с помощью библиотеки INIReader, 
  перебирает полученные поля и сохраняет связи команд и символов.

* Класс InputHandler используется для обработки ввода пользователем в игровом приложении. Он позволяет управлять состоянием 
* ввода для определенных команд, а также загружать настройки ввода из файла конфигурации и устанавливать маппинги символов 
* и команд.
*/