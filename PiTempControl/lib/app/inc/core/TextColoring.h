#ifndef INC_TEXTCOLORING_H_
#define INC_TEXTCOLORING_H_

#include <ostream>

/**
 * @namespace color
 * @brief Az konzolon megjelenõ szöveg színezéséhez szükséges
 * elemeket magába foglaló névtér.
 */
namespace color {
	/**
	 * Az adatfolyam módosítónak megadható színkódok felsorolása.
	 */
	enum ColorType {
		FG_BLACK = 30,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_YELLOW = 33,
		FG_BLUE = 34,
		FG_MAGENTA = 35,
		FG_CYAN = 36,
		FG_WHITE = 37,
		FG_DEFAULT = 39,
		BG_BLACK = 40,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_YELLOW = 43,
		BG_BLUE = 44,
		BG_MAGENTA = 45,
		BG_CYAN = 46,
		BG_WHITE = 47,
		BG_DEFAULT = 49
	};

	/**
	 * @class modifier
	 * @brief A kimenõ adatfolyamot módosító osztály, aminek
	 * segítségével színezni lehet a konzolon megjelenõ szöveget.
	 */
	class modifier {
		/**
		 * A színkód tárolására szolgáló változó.
		 */
		ColorType code;

	public:
		/**
		 * @brief Az osztály konstruktora.
		 *
		 * @param _code A színkódot jelölõ érték.
		 */
		modifier(ColorType _code) : code(_code) {}

		/**
		 * @brief A kimenõ adafolyam-operátor kiterjesztése, amivel
		 * a modifier típusú objektumokban tárolt színkódokat hozzá
		 * lehet írni az adatfolyamhoz.
		 *
		 * @param os Az adatfolyamra mutató referencia.
		 * @param mod Egy modifier típusú objektum, amiben a színkód
		 * található.
		 * @return Az elsõ paraméterben fogadott referencia.
		 */
		friend std::ostream& operator<<(std::ostream& os, const modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}

#endif /* INC_TEXTCOLORING_H_ */