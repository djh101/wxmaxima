// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//  Copyright (C) 2014-2016 Gunter Königsmann <wxMaxima@physikbuch.de>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

/*! \file
  This file declares the class ParenCell

  ParenCell is the MathCell type that represents a math element that is kept
  between parenthesis.
 */

#ifndef PARENCELL_H
#define PARENCELL_H

#include "MathCell.h"
#include "TextCell.h"
#include "Setup.h"

/*! The class that represents parenthesis that are wrapped around text

  In the case that this cell is broken into two lines in the order of
  m_nextToDraw this cell is represented by the following individual 
  cells:
  
   - The ParenCell itself
   - The opening "("
   - The contents
   - The closing ")".
   
  If it isn't broken into multiple cells m_nextToDraw points to the 
  cell that follows this Cell.
 */
class ParenCell : public MathCell
{
public:
  ParenCell();
  ~ParenCell();

  #ifdef __MSW__
  //! The character that represents an opening parenthesis
  wxString Paren_Open() { return wxT("("); }
  //! The character that represents a large opening parenthesis
  wxString Paren_Open_Large() { return wxT("("); }
  //! The character that represents the top of an opening parenthesis
  wxString Paren_Open_Top() { return wxT("\x239b"); }
  //! The character that represents an opening parenthesis
  wxString Paren_Open() { return wxT("("); }
  //! The character that represents the top of an opening parenthesis
  wxString Paren_Open_Top() { return wxT("\x239b"); }
  //! The character that represents a middle part of an opening parenthesis
  wxString Paren_Open_Mid(){return wxT("\x239c");}
  //! The character that represents the bottom of an opening parenthesis
  wxString Paren_Open_Bottom(){return wxT("\x239d");}
  //! The character that represents an closing parenthesis
  wxString Paren_Close(){return wxT(")");}
  //! The character that represents a large closing parenthesis
  wxString Paren_Close_Large() { return wxT(")"); }
  //! The character that represents the top of an closing parenthesis
  wxString Paren_Close_Top(){return wxT("\x239e");}
  //! The character that represents a middle part of an closing parenthesis
  wxString Paren_Close_Mid(){return wxT("\x239f");}
  //! The character that represents the bottom of an closing parenthesis
  wxString Paren_Close_Bottom(){return wxT("\x23a0");}
#else
  //! The character that represents an opening parenthesis
  wxString Paren_Open() { return wxT("("); }
  //! The character that represents a large opening parenthesis
  wxString Paren_Open_Large() { return wxT("\xB0"); }
  //! The character that represents the top of an opening parenthesis
  wxString Paren_Open_Top() { return wxT("\x30"); }
//! The character that represents a middle part of an opening parenthesis
  wxString Paren_Open_Mid() { return wxT("\x42"); }
  //! The character that represents the bottom of an opening parenthesis
  wxString Paren_Open_Bottom() { return wxT("\x40"); }
  //! The character that represents a closing parenthesis
  wxString Paren_Close() { return wxT(")"); }
  //! The character that represents a large closing parenthesis
  wxString Paren_Close_Large() { return wxT("\xD1"); }
  //! The character that represents the top of an closing parenthesis
  wxString Paren_Close_Top() { return wxT("\x31"); }
  //! The character that represents a middle part of an closing parenthesis
  wxString Paren_Close_Mid() { return wxT("\x43"); }
  //! The character that represents the bottom of an closing parenthesis
  wxString Paren_Close_Bottom() { return wxT("\x41"); }
#endif

  void Destroy();
  MathCell* Copy();
  void SetInner(MathCell *inner, int style);
  void SetPrint(bool print)
  {
    m_print = print;
  }
  void SelectInner(wxRect& rect, MathCell **first, MathCell **last);
  void RecalculateHeight(int fontsize);
  void RecalculateWidths(int fontsize);
  void Draw(wxPoint point, int fontsize);
  bool BreakUp();
  void Unbreak();
  wxString ToString();
  wxString ToTeX();
  wxString ToMathML();
  wxString ToOMML();
  wxString ToXML();
  void SetFont(int fontsize);
  void SetParent(MathCell *parent);
private:
  //! The argument of the parenthesis
  MathCell *m_innerCell;
  //! The opening parenthesis for the case that this cell is broken into lines
  TextCell *m_open;
  //! The closing parenthesis for the case that this cell is broken into lines
  TextCell *m_close;
  //! The last cell of the argument of the parenthesis.
  MathCell *m_last1;
  bool m_print;
  /*! The height of the top part of the parenthesis.

    Valid if the parenthesis is assembled out of more than 1 characters.
   */
  int m_parenTopHeight;
  /*! The height of the bottom part of the parenthesis.

    Valid if the parenthesis is assembled out of more than 1 characters.
   */
  int m_parenBottomHeight;
  //! The height of the parenthesis
  int m_parenHeight;
  //! The number of middle parts being needed to reach an appropriate parenthesis size
  int m_parenMidNum;
  /*! The height of a middle part character of the parenthesis.

    Valid if the parenthesis is assembled out of more than 1 characters; See also m_parenMidNum.
   */
  int m_parenMidHeight;
  //! The width of an parenthesis
  int m_parenWidth;
  enum parenthesisStyle
  {
    normal = 0,   //!< An ordinary parenthesis sign
	subSuperScript = 1,   //!< The content is slightly bigger than the average parenthesis sign, but using 
                  // a big parenthesis for a variable with a subscript is a little bit too big an unicode
				  // parenthesis.
    assembled = 2,//!< Assemble a "Parenthesis top half sign", a bot half sign and (if needed) a
                              //   vertical line.
    handdrawn = 3 //!< No suitable font => Draw the parenthesis by hand.
  };

  /* How to create a big parenthesis sign?
     - 0 = 
   */
  parenthesisStyle m_bigParenType;
};

#endif // PARENCELL_H
