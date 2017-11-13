﻿// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2012 Doug Ilijev <doug.ilijev@gmail.com>
//            (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
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

/*!\file 
This file declares the class wxMaximaFrame

wxMaximaFrame draws everything which can be seen
surrounding the worksheet.
*/
#ifndef WXMAXIMAFRAME_H
#define WXMAXIMAFRAME_H

#include <wx/wx.h>

#include <wx/dirctrl.h>
#include <wx/filehistory.h>
#include <wx/listbox.h>
#include <wx/bmpbuttn.h>
#include <wx/arrstr.h>
#include <wx/aui/aui.h>
#include <wx/notifmsg.h>

#include "MathCtrl.h"
#include "Setup.h"
#include "History.h"
#include "ToolBar.h"
#include "XmlInspector.h"
#include "StatusBar.h"
#include <list>


/*! The frame containing the menu and the sidebars
 */
class wxMaximaFrame : public wxFrame
{
public:
  wxMaximaFrame(wxWindow *parent, int id, const wxString &title, const wxString configFile,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE);

  /*! The destructor
  */
  ~wxMaximaFrame();

  /*! Shows or hides the toolbar
    \param show
    - true:  Show the toolbar
    - false: Hide the toolbar
   */
  void ShowToolBar(bool show);

  /*! A list of all events the maxima frame can receive

    This list serves several purposes:
    - wxwidgets uses this list to tell us what kind of events it has to inform us about.
    - we use these events for inter process communication.\n
    For example the "evaluate this cell" menu is clicked by the enter (or the shift+enter,
    depending on what option is set in the configuration).
    - Thirdly his enum is used for assigning panels an ID that matches the ID of the event
    that toggles them which makes the handling of these IDs easier.
  */
  enum Event
  {

    /*! Hide all panes
      
      This event is assigned an ID higher than the highest ID wxWidgets assigns to 
      its internal events in order to avoid ID clashes.
    */
            menu_pane_hideall = wxID_HIGHEST + 1,
    /*! Both used as the "toggle the math pane" command and as the ID of the math pane

      Since this enum is also used for iterating over the panes it is vital 
      that this entry stays that of the first pane in this enum.
    */
            menu_pane_math,
    menu_pane_history,    //!< Both the "toggle the history pane" command and the history pane
    menu_pane_structure,        //!< Both the "toggle the structure pane" command and the structure
    menu_pane_xmlInspector,        //!< Both the "toggle the xml monitor" command and the monitor pane
    menu_pane_format,    //!< Both the "toggle the format pane" command and the format pane
#ifdef wxUSE_UNICODE
    menu_pane_greek,            //!< Both the "toggle the format pane" command for the "greek" pane
    menu_pane_symbols,          //!< Both the "toggle the format pane" command for the "symbols" pane
#endif
    /*! Both used as the "toggle the stats pane" command and as the ID of the stats pane

      Since this enum is also used for iterating over the panes it is vital 
      that this entry stays that of the last pane in this enum.
    */
            menu_pane_stats,

    socket_client_id,
    socket_server_id,
    input_line_id,
    refresh_id,
    menu_new_id,
    menu_open_id,
    menu_batch_id,
    menu_save_id,
    menu_save_as_id,
    menu_load_id,
    menu_sconsole_id,
    menu_interrupt_id,
    menu_solve,
    menu_solve_to_poly,
    menu_solve_num,
    menu_allroots,
    menu_bfallroots,
    menu_realroots,
    menu_solve_lin,
    menu_solve_algsys,
    menu_eliminate,
    menu_solve_ode,
    menu_ivp_1,
    menu_ivp_2,
    menu_bvp,
    menu_gen_mat,
    menu_gen_mat_lambda,
    menu_enter_mat,
    menu_invert_mat,
    menu_cpoly,
    menu_determinant,
    menu_eigen,
    menu_eigvect,
    menu_fun_def,
    menu_adjoint_mat,
    menu_transpose,
    menu_map_mat,
    menu_ratsimp,
    menu_radsimp,
    menu_factor,
    menu_gfactor,
    menu_expand,
    menu_talg,
    menu_tellrat,
    menu_modulus,
    menu_trigsimp,
    menu_trigreduce,
    menu_trigexpand,
    menu_trigrat,
    menu_rectform,
    menu_polarform,
    menu_demoivre,
    menu_exponentialize,
    menu_num_out,
    menu_to_float,
    menu_to_bfloat,
    menu_to_numer,
    menu_set_precision,
    menu_functions,
    menu_variables,
    menu_clear_var,
    menu_clear_fun,
    menu_integrate,
    menu_risch,
    menu_laplace,
    menu_ilt,
    menu_continued_fraction,
    menu_gcd,
    menu_lcm,
    menu_divide,
    menu_partfrac,
    menu_sum,
    menu_limit,
    menu_lbfgs,
    menu_series,
    menu_pade,
    menu_map,
    menu_diff,
    menu_solve_de,
    menu_atvalue,
    menu_lhs,
    menu_rhs,
    menu_maximahelp,
    menu_example,
    menu_apropos,
    menu_product,
    menu_make_list,
    menu_apply,
    menu_time,
    menu_factsimp,
    menu_factcomb,
    menu_realpart,
    menu_imagpart,
    menu_subst,
<<<<<<< HEAD
    menu_jumptoerror,
    menu_math_as_1D_ASCII,
    menu_math_as_2D_ASCII,
    menu_math_as_graphics,
=======
    menu_triggerEvaluation,
    menu_listCreate,
>>>>>>> 23e5779d7a21a04ff2a128fdfecaaa7d648a8524
    button_factor_id,
    button_solve,
    button_solve_ode,
    button_limit,
    button_taylor,
    button_expand,
    button_ratsimp,
    button_radcan,
    button_trigsimp,
    button_trigexpand,
    button_trigreduce,
    button_trigrat,
    button_integrate,
    button_diff,
    button_sum,
    button_product,
    button_button_constant,
    button_factor,
    button_subst,
    button_plot2,
    button_plot3,
    button_rectform,
    button_map,
    gp_plot2,
    gp_plot3,
    menu_animationautostart,
    menu_animationframerate,
    menu_display,
    menu_soft_restart,
    menu_plot_format,
    menu_build_info,
    menu_bug_report,
    menu_add_path,
    menu_evaluate_all_visible,
    menu_evaluate_all,
    menu_show_tip,
    menu_copy_from_console,
    menu_copy_tex_from_console,
    menu_copy_text_from_console,
    menu_undo,
    menu_redo,
    menu_select_all,
    menu_logcontract,
    menu_logexpand,
    menu_to_fact,
    menu_to_gamma,
    menu_texform,
    button_enter,
    menu_zoom_80,
    menu_zoom_100,
    menu_zoom_120,
    menu_zoom_150,
    menu_zoom_200,
    menu_zoom_300,
    menu_copy_as_bitmap,
    menu_copy_as_svg,
    menu_save_as_svg,
    menu_copy_as_rtf,
    menu_copy_to_file,
    menu_export_html,
    menu_change_var,
    menu_nouns,
    menu_evaluate,
    menu_convert_to_code,
    menu_add_comment,
    menu_convert_to_comment,
    menu_add_subsubsection,
    menu_convert_to_subsubsection,
    menu_add_subsection,
    menu_convert_to_subsection,
    menu_add_section,
    menu_convert_to_section,
    menu_add_title,
    menu_convert_to_title,
    menu_add_pagebreak,
    menu_fold_all_cells,
    menu_unfold_all_cells,
    menu_insert_input,
    menu_insert_previous_input,
    menu_insert_previous_output,
    menu_autocomplete,
    menu_autocomplete_templates,
    menu_cut,
    menu_paste,
    menu_paste_input,
    menu_fullscreen,
    menu_remove_output,
    mac_newId,
    mac_openId,
    mac_closeId,
    menu_list_create_from_elements,
    menu_list_create_from_rule,
    menu_list_create_from_list,
    menu_list_actual_values_storage,
    menu_list_sort,
    menu_list_length,
    menu_list_push,
    menu_list_pop,
    menu_list_reverse,
    menu_list_first,
    menu_list_last,
    menu_list_nth,
    menu_list_map,
    menu_list_use_actual_values,
    menu_list_as_function_arguments,
    menu_list_do_for_each_element,
    menu_list_remove_duplicates,
    menu_list_remove_element,
    menu_list_append,
    menu_list_interleave,
    menu_recent_documents,
    menu_recent_document_0,
    menu_recent_document_1,
    menu_recent_document_2,
    menu_recent_document_3,
    menu_recent_document_4,
    menu_recent_document_5,
    menu_recent_document_6,
    menu_recent_document_7,
    menu_recent_document_8,
    menu_recent_document_9,
    menu_recent_document_10,
    menu_recent_document_11,
    menu_recent_document_12,
    menu_recent_document_13,
    menu_recent_document_14,
    menu_recent_document_15,
    menu_recent_document_16,
    menu_recent_document_17,
    menu_recent_document_18,
    menu_recent_document_19,
    menu_recent_document_20,
    menu_recent_document_21,
    menu_recent_document_22,
    menu_recent_document_23,
    menu_recent_document_24,
    menu_recent_document_25,
    menu_recent_document_26,
    menu_recent_document_27,
    menu_recent_document_28,
    menu_recent_document_29,
    menu_recent_document_separator,
    menu_unsaved_document_0,
    menu_unsaved_document_1,
    menu_unsaved_document_2,
    menu_unsaved_document_3,
    menu_unsaved_document_4,
    menu_unsaved_document_5,
    menu_unsaved_document_6,
    menu_unsaved_document_7,
    menu_unsaved_document_8,
    menu_unsaved_document_9,
    menu_unsaved_document_10,
    menu_unsaved_document_11,
    menu_unsaved_document_12,
    menu_unsaved_document_13,
    menu_unsaved_document_14,
    menu_unsaved_document_15,
    menu_unsaved_document_16,
    menu_unsaved_document_17,
    menu_unsaved_document_18,
    menu_unsaved_document_19,
    menu_unsaved_document_20,
    menu_unsaved_document_21,
    menu_unsaved_document_22,
    menu_unsaved_document_23,
    menu_unsaved_document_24,
    menu_unsaved_document_25,
    menu_unsaved_document_26,
    menu_unsaved_document_27,
    menu_unsaved_document_28,
    menu_unsaved_document_29,
    menu_insert_image,
    menu_stats_mean,
    menu_stats_median,
    menu_stats_var,
    menu_stats_dev,
    menu_stats_tt1,
    menu_stats_tt2,
    menu_stats_tnorm,
    menu_stats_linreg,
    menu_stats_lsquares,
    menu_stats_histogram,
    menu_stats_scatterplot,
    menu_stats_barsplot,
    menu_stats_piechart,
    menu_stats_boxplot,
    menu_stats_readm,
    menu_stats_enterm,
    menu_stats_subsample,
    menu_format_code,
    menu_format_text,
    menu_format_subsubsection,
    menu_format_subsection,
    menu_format_section,
    menu_format_title,
    menu_format_image,
    menu_format_pagebreak,
    menu_help_tutorials,
    menu_show_toolbar,
    menu_edit_find,
    menu_history_previous,
    menu_history_next,
    menu_check_updates
  };

  /*! Update the recent documents list

    Copies the string array containing the list of recent documents to the
    recent documents menu.
   */
  void UpdateRecentDocuments();

  //! Add an entry to the "Recent Documents" list.
  void AddRecentDocument(wxString file);

  /*! Remove a file from the "Recent Documents" list.

    Removing and re-adding a file will move it to the top of the list.
   */
  void RemoveRecentDocument(wxString file);

  //! Read the nth entry in the list of recent documents.
  wxString GetRecentDocument(int i)
  { return m_recentDocuments[i]; }

  /*! true, if a Pane is currently enabled

    \param id The event that toggles the visibility of the pane that is
    to be queried
   */
  bool IsPaneDisplayed(Event id);

  /*! Show or hide a sidebar
    
    \param id The type of the sidebar to show/hide
    \param hide 
     - true: show the sidebar
     - false: hide it
   */
  void ShowPane(Event id, bool hide);

  //! Adds a command to the list  of recently used maxima commands
  void AddToHistory(wxString cmd)
  { m_history->AddToHistory(cmd); }

  enum ToolbarStatus
  {
    wait_for_start,
    process_wont_start,
    waiting,
    calculating,
    parsing,
    transferring,
    userinput,
    disconnected
  };

  /*! Inform the user about the length of the evaluation queue.

   */
  void EvaluationQueueLength(int length, int numberOfCommands = -1);

  /*! Set the status according to if maxima is calculating 

    \param status
      - true:  Maxima is calculating
      - false: Maxima is waiting for input
   */
  void StatusMaximaBusy(ToolbarStatus status){m_StatusMaximaBusy_next = status;}
  void UpdateStatusMaximaBusy();

  //! True=Maxima is currently busy.
  ToolbarStatus m_StatusMaximaBusy;

  ToolbarStatus m_StatusMaximaBusy_next;

  //! Set the status to "Maxima is saving"
  void StatusSaveStart();

  //! Set the status to "Maxima has finished saving"
  void StatusSaveFinished();

  //! Set the status to "Saving has failed"
  void StatusSaveFailed();

  //! Set the status to "Maxima is exporting"
  void StatusExportStart();

  //! Set the status to "Maxima has finished exporting"
  void StatusExportFinished();

  //! Set the status to "Exporting has failed"
  void StatusExportFailed();

protected:
  //! The process id of maxima. Is determined by ReadFirstPrompt.
  long m_pid;
  //! The last name GetTempAutosavefileName() has returned.
  wxString m_tempfileName;
  //! Issued if a notification is closed.
  void OnNotificationClose(wxCommandEvent WXUNUSED(&event));
  //! The status bar
  StatusBar *m_statusBar;
  //! The menu bar
  wxMenuBar *m_MenuBar;
  //! The file menu.
  wxMenu *m_FileMenu;
  //! The edit menu.
  wxMenu *m_EditMenu;
  //! The cell menu.
  wxMenu *m_CellMenu;
  //! The zoom submenu
  wxMenu *m_Edit_Zoom_Sub;
  //! The panes submenu
  wxMenu *m_Maxima_Panes_Sub;
  //! The equations menu.
  wxMenu *m_EquationsMenu;
  //! The maxima menu.
  wxMenu *m_MaximaMenu;
  //! The algebra menu.
  wxMenu *m_Algebra_Menu;
  //! The simplify menu
  wxMenu *m_SimplifyMenu;
  //! The factorials and gamma submenu
  wxMenu *m_Simplify_Gamma_Sub;
  //! The trigonometric submenu
  wxMenu *m_Simplify_Trig_Sub;
  //! The complex submenu
  wxMenu *m_Simplify_Complex_Sub;
  //! The calculus menu
  wxMenu *m_CalculusMenu;
  //! The plot menu
  wxMenu *m_PlotMenu;
  //! The list menu
  wxMenu *m_listMenu;
  //! The numeric menu
  wxMenu *m_NumericMenu;
  //! The help menu
  wxMenu *m_HelpMenu;
  //! Remove an eventual temporary autosave file.
  void RemoveTempAutosavefile();
  //! Re-read the configuration.
  void ReReadConfig();  
  /*! Determine a suitable name for a temporary autosave file.
    
    Is used if we want to autosave the current file, but still have no 
    filename to save it to.
  */  
  wxString GetTempAutosavefileName();
  //! Remember an temporary autosave file name.
  void RegisterAutoSaveFile(wxString name);
  //! Generates a list of all temporary autosave files we didn't open yet.
  std::list<wxString> GetTempAutosaveFiles();
private:
  //! A panel that shows all user-defined symbols on the symbols pane.
  wxPanel *m_userSymbols;
  //! A button per user defined symbol
  std::list<wxPanel *> m_userSymbolButtons;
  wxGridSizer *m_userSymbolsSizer;
  //! True=We are currently saving.
  bool m_StatusSaving;
  void set_properties();

  void do_layout();

#if defined (__WXMSW__) || defined (__WXGTK20__) || defined (__WXMAC__)

  void SetupToolBar();

#endif
/*! 
  Create the menus.
*/
  void SetupMenu();

  wxPanel *CreateStatPane();

  wxPanel *CreateMathPane();

  wxPanel *CreateFormatPane();

  /*! A button for the greek pane
    
    \param parent The parent panel/window
    \param ch The unicode symbol
    \param description The help text for the symbol
    \param matchesMaximaCommand true means that this symbol is automatically
                                translated into a maxima command/operator

   */
  wxPanel *CharButton(wxPanel *parent, wxChar ch, wxString description = wxEmptyString,
                      bool matchesMaximaCommand = false);

#ifdef wxUSE_UNICODE

  wxPanel *CreateGreekPane();

  wxPanel *CreateSymbolsPane();

#endif
protected:
  //! The name of the config file or wxEmptyString if the default is used.
  wxString m_configFileName;
  //! Update the "user symbols" portion of the symbols pane.
  void UpdateUserSymbols();
  //! Do we need to update the display showing the evaluation queue length?
  bool m_updateEvaluationQueueLengthDisplay;
  //! The current length of the evaluation queue of commands we still need to send to maxima
  int m_EvaluationQueueLength;
  //! The number of commands left in the current of the evaluation queue item
  int m_commandsLeftInCurrentCell;

  //! Do we expect the 1st prompt from maxima to appear?
  bool m_first;

  void CharacterButtonPressed(wxMouseEvent &event);

  void LoadRecentDocuments();

  void SaveRecentDocuments();

  wxAuiManager m_manager;
  //! A XmlInspector-like xml monitor
  XmlInspector *m_xmlInspector;
  //! true=force an update of the status bar at the next call of StatusMaximaBusy()
  bool m_forceStatusbarUpdate;
  //! The worksheet itself
  MathCtrl *m_console;
  //! The history pane
  History *m_history;
  wxArrayString m_recentDocuments;
  wxMenu *m_recentDocumentsMenu;
};

#endif // WXMAXIMAFRAME_H
