/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  watchdog Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include <vector>

class wdDC;
class TiXmlElement;

enum AlarmType {LANDFALL, BOUNDARY, NMEADATA, DEADMAN, ANCHOR, COURSE, SPEED};

class Alarm : public wxEvtHandler {
public:
    static void RenderAll(wdDC &dc, PlugIn_ViewPort &vp);
    static void LoadConfigAll();
    static void SaveConfigAll();
    static void DeleteAll();
    static void ResetAll();
    static void NMEAStringAll(const wxString &sentence);
    static Alarm *NewAlarm(enum AlarmType type);
    static void SaveAlarms(wxString filename);
    static void LoadAlarms(wxString filename);

    static std::vector<Alarm*> s_Alarms;

    Alarm(int interval=1);

    wxString Action();
    void Run();

    virtual wxString Type() = 0;
    virtual wxString Options() = 0;
    virtual bool Test() = 0;
    virtual wxString GetStatus() = 0;
    virtual void NMEAString(const wxString &sentence) {}
    virtual void Render(wdDC &dc, PlugIn_ViewPort &vp) {}
    virtual wxWindow *OpenPanel(wxWindow *parent) = 0;
    virtual void SavePanel(wxWindow *panel) = 0;
    virtual void LoadConfig(TiXmlElement *e) = 0;
    virtual void SaveConfig(TiXmlElement *c) = 0;

    void LoadConfigBase(TiXmlElement *e);
    void SaveConfigBase(TiXmlElement *c);

    void OnTimer(wxTimerEvent &);

    bool m_bEnabled, m_bgfxEnabled;
    bool m_bFired;

private:
    friend class EditAlarmDialog;

    void ConfigItem(bool read, wxString name, wxControl *control);
    virtual void GetStatusControls(wxControl *&Text, wxControl *&status) { Text = status = NULL; }

    bool m_bSound, m_bCommand, m_bMessageBox, m_bRepeat, m_bAutoReset;
    wxString m_sSound, m_sCommand;
    int m_iRepeatSeconds;

    int m_interval;

    wxTimer    m_Timer;
    wxDateTime m_LastAlarmTime;
};
