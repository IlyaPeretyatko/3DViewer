#ifndef SRC_CONTROLLER_COMMAND_H_
#define SRC_CONTROLLER_COMMAND_H_

/**
 * @brief The Command class is an abstract base class for all commands.
 *
 * This class defines an interface for commands that can be executed.
 */
class Command {
 public:
  /**
   * @brief Default constructor.
   */
  Command(){};

  /**
   * @brief Virtual destructor (defaulted).
   */
  ~Command() = default;

  /**
   * @brief Pure virtual function to execute the command.
   *
   * Subclasses must implement this method to define specific command behavior.
   */
  virtual void execute() = 0;
};

namespace s21 {

/**
 * @brief The CommandManager class manages and executes a single Command object.
 *
 * This class is responsible for setting a command and executing it when
 * required.
 */
class CommandManager {
  Command *command;  ///< Pointer to the current Command object.

 public:
  /**
   * @brief Default constructor.
   */
  CommandManager(){};

  /**
   * @brief Sets the command to be managed.
   *
   * @param com Pointer to the Command object to be set.
   */
  void setCommand(Command *com);

  /**
   * @brief Executes the currently set command.
   *
   * This method calls the execute() method on the currently set Command object.
   */
  void run();
};

}  // namespace s21

#endif  // SRC_CONTROLLER_COMMAND_H_