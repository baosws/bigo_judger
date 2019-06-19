#ifndef PRESENTATION
#define PRESENTATION
#include <bits/stdc++.h>

namespace presentation {
    enum Color {
        Red, Green, Yellow, Purple, White, Orange
    };
    std::string color_string(const std::string& str, const Color& color = Color::White);
}
#endif
