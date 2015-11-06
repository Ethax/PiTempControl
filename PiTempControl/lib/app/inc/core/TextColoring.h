#ifndef INC_TEXTCOLORING_H_
#define INC_TEXTCOLORING_H_

#include <ostream>

/**
 * @namespace color
 * @brief Az konzolon megjelen� sz�veg sz�nez�s�hez sz�ks�ges
 * elemeket mag�ba foglal� n�vt�r.
 */
namespace color {
	/**
	 * Az adatfolyam m�dos�t�nak megadhat� sz�nk�dok felsorol�sa.
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
	 * @brief A kimen� adatfolyamot m�dos�t� oszt�ly, aminek
	 * seg�ts�g�vel sz�nezni lehet a konzolon megjelen� sz�veget.
	 */
	class modifier {
		/**
		 * A sz�nk�d t�rol�s�ra szolg�l� v�ltoz�.
		 */
		ColorType code;

	public:
		/**
		 * @brief Az oszt�ly konstruktora.
		 *
		 * @param _code A sz�nk�dot jel�l� �rt�k.
		 */
		modifier(ColorType _code) : code(_code) {}

		/**
		 * @brief A kimen� adafolyam-oper�tor kiterjeszt�se, amivel
		 * a modifier t�pus� objektumokban t�rolt sz�nk�dokat hozz�
		 * lehet �rni az adatfolyamhoz.
		 *
		 * @param os Az adatfolyamra mutat� referencia.
		 * @param mod Egy modifier t�pus� objektum, amiben a sz�nk�d
		 * tal�lhat�.
		 * @return Az els� param�terben fogadott referencia.
		 */
		friend std::ostream& operator<<(std::ostream& os, const modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}

#endif /* INC_TEXTCOLORING_H_ */