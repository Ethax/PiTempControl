#ifndef INC_EXCEPTION_H_
#define INC_EXCEPTION_H_

#include <string>

/**
 * @class AppException
 * @brief Általános kivétel osztály, amelynek objektumait az alkalmazás
 * moduljai dobhatják hiba esetén.
 */
class AppException {
	/**
	 * A hibaüzenetet tároló változó.
	 */
	std::string what;

public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param _what A hibaüzenet.
	 */
	AppException(const std::string& _what) : what(_what) {}

	/**
	 * @brief Visszaadja a hibaüzenetet.
	 *
	 * @return Az osztály példányosításakor megadott üzenet.
	 */
	std::string getErrorMessage() { return what; }
};

#endif /* INC_EXCEPTION_H_ */