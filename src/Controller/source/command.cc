#include "command.h"

using namespace s21;

void CommandManager::setCommand(Command *com) { command = com; }

void CommandManager::run() {
  if (command != 0) command->execute();
}
