#include "ncscpp.h"

#include <cppurses/cppurses.hpp>
#include <iostream>

int Ncscpp::run() {
  std::cout << "Ncs::Run() - initing ncurses\n";
  // Must create this object before any Widgets are created.
    cppurses::System sys;

    // Create a text string with Attributes, has type Glyph_string.
    cppurses::Glyph_string greeting{"Hello, World!", cppurses::Attribute::Blink};

    // Create Textbox Widget with `greeting` as the initial text.
    cppurses::Textbox tb{greeting};

    // Set the background and foreground colors of the Textbox.
    tb.brush.set_background(cppurses::Color::Dark_blue);
    tb.brush.set_foreground(cppurses::Color::Light_blue);

    // Enable a border to be drawn around the Textbox.
    tb.border.enable();
    tb.border.segments.north_west = L'╭';
    tb.border.segments.north_east = L'╮';
    tb.border.segments.south_west = L'╰';
    tb.border.segments.south_east = L'╯';

    // Set the Textbox as the head(top-level) Widget, initialize the screen and
    // start the user input event loop.
    return sys.run(tb);
}

