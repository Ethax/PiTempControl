#ifndef INC_EXCEPTION_H_
#define INC_EXCEPTION_H_

#include <string>

/**
 * @class AppException
 * @brief �ltal�nos kiv�tel oszt�ly, amelynek objektumait az alkalmaz�s
 * moduljai dobhatj�k hiba eset�n.
 */
class AppException {
	/**
	 * A hiba�zenetet t�rol� v�ltoz�.
	 */
	std::string what;

public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param _what A hiba�zenet.
	 */
	AppException(const std::string& _what) : what(_what) {}

	/**
	 * @brief Visszaadja a hiba�zenetet.
	 *
	 * @return Az oszt�ly p�ld�nyos�t�sakor megadott �zenet.
	 */
	std::string getErrorMessage() { return what; }
};

#endif /* INC_EXCEPTION_H_ */