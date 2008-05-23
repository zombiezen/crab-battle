; crab_battle.nsi
;--------------------------------

!include "MUI2.nsh"

; The name of the installer
Name "Crab Battle"

; The installer's file to write
OutFile "Install Crab Battle.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Crab Battle"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
; InstallDirRegKey HKLM "Software\Crab_Battle" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------

!insertmacro MUI_LANGUAGE "English"

;--------------------------------

Section "Crab Battle" SecCrabBattle
  SectionIn Ro ; Ensure that the user cannot *not* install Crab Battle
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  ; Put files there
  File "..\build\Crab Battle.exe"
  File C:\wxDev-Cpp\bin\SDL.dll
  File SDL_image\bin\*.dll
  File SDL_mixer\bin\*.dll
  File SDL_ttf\bin\*.dll
  
  WriteUninstaller uninstall.exe
SectionEnd

Section "Start Menu Shortcuts" SecStartMenu
	CreateDirectory "$SMPROGRAMS\Crab Battle"
	CreateShortCut  "$SMPROGRAMS\Crab Battle\Crab Battle.lnk" "$INSTDIR\Crab Battle.exe" "" "$INSTDIR\Crab Battle.exe" 0
	File "/oname=$SMPROGRAMS\Crab Battle\Visit Crab Battle Project.url" "Visit Crab Battle Project.url"
	CreateShortCut  "$SMPROGRAMS\Crab Battle\Uninstall.lnk"   "$INSTDIR\uninstall.exe"   "" "$INSTDIR\uninstall.exe"   0
SectionEnd

Section "Uninstall"
	Delete "$INSTDIR\Crab Battle.exe"
	Delete "$INSTDIR\*.dll"
	Delete $INSTDIR\uninstall.exe
	
	Delete "$SMPROGRAMS\Crab Battle\*.lnk"
	Delete "$SMPROGRAMS\Crab Battle\*.url"
	
	RMDir $INSTDIR
	RMDir "$SMPROGRAMS\Crab Battle"
SectionEnd

;--------------------------------
;Descriptions

;Language strings
LangString DESC_SecCrabBattle ${LANG_ENGLISH} "The Crab Battle program and support files."
LangString DESC_SecStartMenu ${LANG_ENGLISH} "Shortcuts in the Start Menu for running and uninstalling Crab Battle."

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCrabBattle} $(DESC_SecCrabBattle)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecStartMenu} $(DESC_SecStartMenu)
!insertmacro MUI_FUNCTION_DESCRIPTION_END