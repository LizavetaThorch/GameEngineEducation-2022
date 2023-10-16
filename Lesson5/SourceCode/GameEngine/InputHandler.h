#pragma once

#include <string>
#include <unordered_map>
#include <bitset>

#include "Input.h"
#include "INIReader.h"

class InputHandler
{
public:
	InputHandler();

	void Update();

	const std::bitset<eIC_Max>& GetInputState() const;

private:
	void LoadConfiguration();

	bool IsKeyDown(size_t vk_key);

	void MapSymbol(std::string strSymbol, size_t nSymbol);
	void MapInputEvent(std::size_t nSymbol, size_t nCommand);
	void MapCommandSymbol(std::string strCommand, size_t nCommand, std::string strDefaultSymbol);
	void Remap();

	std::string m_strMapFilePath;

	typedef std::unordered_map<std::string, size_t> TCommandMap;
	typedef std::unordered_map<std::string, size_t> TSymbolMap;
	typedef std::unordered_map<size_t, size_t> TInputEventMap;
	typedef std::unordered_map<std::string, std::string> TCommandSymbolMap;

	TCommandMap m_commandMap;
	TSymbolMap m_symbolMap;
	TInputEventMap m_inputEventMap;
	TCommandSymbolMap m_commandSymbolMap;

	std::bitset<eIC_Max> m_InputState;
};


/*
* Данный код представляет собой объявление класса InputHandler.
* Класс InputHandler отвечает за обработку и управление вводом в игровом приложении. 
* Он содержит методы для загрузки конфигурации, связывания символов с командами, обновления состояния ввода и 
* получения текущего состояния ввода.

* В классе определены следующие публичные методы:
- Update(): обновляет состояние ввода на основе текущего состояния символов.
- GetInputState(): возвращает текущее состояние ввода в виде std::bitset<eIC_Max>, где каждый бит представляет состояние 
  определенной команды.

* Класс также содержит приватные методы:
- LoadConfiguration(): загружает конфигурацию символов и команд из файла.
- IsKeyDown(size_t vk_key): проверяет, нажата ли клавиша с заданным кодом.
- MapSymbol(std::string strSymbol, size_t nSymbol): связывает символ с кодом символа.
- MapInputEvent(std::size_t nSymbol, size_t nCommand): связывает символ ввода с командой.
- MapCommandSymbol(std::string strCommand, size_t nCommand, std::string strDefaultSymbol): связывает команду с символом 
  и устанавливает символ по умолчанию.
- Remap(): перепривязывает команды к символам на основе текущих связей команд и символов.

* Также класс InputHandler содержит приватные поля и типы данных для хранения связей между символами, командами и 
  входными событиями.

* Основная цель класса InputHandler - обеспечить удобную систему управления вводом в игровом приложении, а также возможность 
  настройки раскладки клавиш и связей команд с символами через конфигурационный файл.
*/
