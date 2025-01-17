#pragma once

struct InputHandlerPtr
{
  class InputHandler* ptr;
};

struct RenderEnginePtr
{
  class RenderEngine* ptr;
};


/*
* Эти структуры вероятно используются в контексте эффективного передачи указателей на экземпляры соответствующих 
* классов между разными компонентами или системами в программе. Вместо прямого использования указателей, 
* такие структуры обеспечивают определенный уровень инкапсуляции и безопасности, позволяя легче передавать 
* и управлять указателями на классы
*/