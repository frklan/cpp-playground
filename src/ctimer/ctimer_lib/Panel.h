#pragma once

#include <ncursesw/cursesp.h>
#include <string>
#include <utility>

class Panel : public NCursesPanel {
  public:
 
  Panel(int nlines, int ncols, int begin_y, int begin_x); 
  
	bool isViewActive() const { return _isViewActive; }

  virtual void onActivate();
  virtual void onDeactivate();
  virtual int onKey(int /*key*/) {
    return false;
  }

  virtual void label(const std::string& topLabel = "", const std::string& bottomLabel = ""); 
  std::pair<std::string, std::string> getLabel() const {
    return std::make_pair(this->_topLabel, this->_bottomLabel);
  }

  protected:
    virtual void clearRow(const int row);
  
  private:
    virtual void label(const char*, const char*) override { } 
    void label(const char* topLabel, const int topMargin, const char* bottomLabel, const int bottomMargin) ;
    
    bool _isViewActive = false;
		std::string _bottomLabel = "";
    std::string _topLabel = "";
};

