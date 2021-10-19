def CleanNotepad():
    #Runs the "notepad" tested application.
    TestedApps.notepad.Run()
    Aliases.notepad_.wndNotepad.Scintilla.Keys("^a^[ReleaseLast][BS]")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    
    
def TestInput():
    #Runs the "notepad" tested application.
    TestedApps.notepad.Run()
    #Enters 'Hello world' in the 'Scintilla' object.
    Aliases.notepad_.wndNotepad.Scintilla.Keys("Hello world")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    #Closing the "notepad" tested application.
    TestedApps.notepad.Close()
    #Getting whole text of file
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="Hello world"):
      Log.Message("Test passed")
    CleanNotepad()
    

def TestAutoFill():
    TestedApps.notepad.Run()
    Aliases.notepad_.wndNotepad.Scintilla.Keys("di[Tab]")
    #Moves the mouse cursor to the menu item specified and then simulates a single click.
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    if (s=="dialog"):
      Log.Message("Test passed")
    CleanNotepad()

def TestTabsAndFileCreation():
    TestedApps.notepad.Run()
    #Creating new file
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41001, False)
    Aliases.notepad_.wndNotepad.Scintilla.Keys("Hello")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    Aliases.notepad_.dlg_.btn_.ClickButton()
    #Selects the 'new.html' tab of the 'Tab' tab control.
    Aliases.notepad_.wndNotepad.Tab.ClickTab("new.html")
    Aliases.notepad_.wndNotepad.Scintilla.Keys("world")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    
    TestedApps.notepad.Close()
    
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="world"):
      Log.Message("Test passed")
    CleanNotepad()
      
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="Hello"):
      Log.Message("Test passed")

def TestReplace():
    TestedApps.notepad.Run()
    Aliases.notepad_.wndNotepad.Scintilla.Keys("world")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(43001, False)
    Aliases.notepad_.dlg_2.tbc_.ClickTab("Замена")
    Aliases.notepad_.dlg_2.cbx_.Edit.Drag(76, 9, -124, -3)
    Aliases.notepad_.dlg_2.cbx_.SetText("Hello")
    Aliases.notepad_.dlg_2.btn_.ClickButton()
    Aliases.notepad_.dlg_2.Close()
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="Hello"):
      Log.Message("Test passed")
    CleanNotepad()

def TestRecord():
    TestedApps.notepad.Run()
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(42018, False)
    Aliases.notepad_.wndNotepad.Scintilla.Keys("Hello world[Enter]")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(42019, False)
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(42021, False)
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="Hello world\r\nHello world\r\n"):
      Log.Message("Test passed")
    CleanNotepad()
      

def TestAltFunction():
    TestedApps.notepad.Run()
    Aliases.notepad_.wndNotepad.Scintilla.Keys("Hello[Enter]world")
    Aliases.notepad_.wndNotepad.Scintilla.Drag(129, 28, -80, -25, skAlt)
    Aliases.notepad_.wndNotepad.Scintilla.Keys("Hello world")
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    
    if (s=="Hello world\r\nHello world"):
        Log.Message("Test passed")
    CleanNotepad()
          


def TestBigData():
    TestedApps.notepad.Run()
    long = ""
    for i in range (1, 100):
      long += "Hello world"+str(i)
    Aliases.notepad_.wndNotepad.Scintilla.Keys(long)
    Aliases.notepad_.wndNotepad.ReBarWindow32.toolbar.ClickItem(41006, False)
    TestedApps.notepad.Close()
    s = aqFile.ReadWholeTextFile("D:\\PATH_TO_FILE\\FILE_NAME.TXT", aqFile.ctANSI)
    if (s==long):
      Log.Message("Test passed")
    CleanNotepad()
