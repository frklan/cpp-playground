#include "Panel.h"

#include <cstring>
#include <ncursesw/cursesp.h>
#include <string>

constexpr int DEFAULT_MARGIN = 4;
constexpr int ACTIVE_MARGIN = DEFAULT_MARGIN - 2;

Panel::Panel(int nlines, int ncols, int begin_y, int begin_x) :
  NCursesPanel(nlines, ncols, begin_y, begin_x) {
}

void Panel::onActivate() {
  if(this->_topLabel.length() > 0) {
    this->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    this->label((" >" + this->_topLabel + "< ").c_str(), ACTIVE_MARGIN, this->_bottomLabel.c_str(), DEFAULT_MARGIN);
  }
	
	_isViewActive = true;
}

void Panel::onDeactivate() {
  if(this->_topLabel.length() > 0) {
    this->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    this->label(this->_topLabel.c_str(), DEFAULT_MARGIN, this->_bottomLabel.c_str(), DEFAULT_MARGIN);
  }

	_isViewActive = false;
}

void Panel::label(const char* topLabel, const int topMargin, const char* bottomLabel, const int bottomMargin) {
  this->printw(0, topMargin, "%s", topLabel);
  this->printw(maxy(), maxx() - static_cast<int>(strlen(bottomLabel)) - bottomMargin, "%s", bottomLabel);
  Panel::redraw();
}

void Panel::label(const std::string& topLabel, const std::string& bottomLabel) {
  if(topLabel.length() > 0) {
    this->_topLabel = " " + topLabel + " ";
  } else {
    this->_topLabel.clear();
  } 

  if(bottomLabel.length() > 0) {
    this->_bottomLabel = " " + bottomLabel + " ";
  } else {
    this->_bottomLabel.clear();
  }

  label(this->_topLabel.c_str(), DEFAULT_MARGIN, this->_bottomLabel.c_str(), DEFAULT_MARGIN);
}
  

void Panel::clearRow(const int row) {
    auto leftBorder = this->inch(row, 0);
    auto rightBorder = this->inch(row, this->maxx());
		this->move(row, 0);
    this->clrtoeol();
    this->addch(row, 0, leftBorder);
    this->addch(row, this->maxx(), rightBorder);
}

