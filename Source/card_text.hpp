#pragma once

#include <array>

namespace SM { namespace dominion {
typedef const std::array<const wchar_t*, 30180> card_text_array;

//a std::array storing the entirety of the card text as separate words
extern card_text_array complete_card_text;
}   //end namespace dominion
}   //end namespace SM
