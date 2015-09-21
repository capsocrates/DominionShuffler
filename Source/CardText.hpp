#pragma once

#include <array>

namespace SM { namespace Dominion {
typedef const std::array<const wchar_t*, 30180> CardTextArray;

//a std::array storing the entirety of the card text as separate words
extern CardTextArray complete_card_text;
}   //end namespace dominion
}   //end namespace SM
