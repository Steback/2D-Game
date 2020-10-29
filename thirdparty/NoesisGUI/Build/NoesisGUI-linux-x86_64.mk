# GNU Make solution 

PROJECTS = NoesisApp Gui.XamlPlayer Samples.Integration Samples.IntegrationGLUT Samples.HelloWorld Samples.Buttons Samples.Login Samples.QuestLog Samples.Scoreboard Samples.DataBinding Samples.ApplicationTutorial Samples.Commands Samples.UserControl Samples.CustomControl Samples.BlendTutorial Samples.Menu3D Samples.Localization Samples.Inventory Samples.TicTacToe Samples.Gallery

.SUFFIXES:
.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

clean:
	@$(MAKE) --no-print-directory -C ../Src/NoesisApp/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Gui/XamlPlayer/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Integration/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/IntegrationGLUT/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/HelloWorld/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Buttons/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Login/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/QuestLog/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Scoreboard/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/DataBinding/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/ApplicationTutorial/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Commands/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/UserControl/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/CustomControl/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/BlendTutorial/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Menu3D/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Localization/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Inventory/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/TicTacToe/Projects/linux_x86_64 clean
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Gallery/Projects/linux_x86_64 clean

help:
	@echo Usage: make [CONFIG=name] [V=1] [target]
	@echo CONFIGURATIONS:
	@echo - Profile
	@echo - Release
	@echo - Debug
	@echo TARGETS:
	@echo - all [default]
	@echo - clean
	@echo - NoesisApp
	@echo - Gui.XamlPlayer
	@echo - Samples.Integration
	@echo - Samples.IntegrationGLUT
	@echo - Samples.HelloWorld
	@echo - Samples.Buttons
	@echo - Samples.Login
	@echo - Samples.QuestLog
	@echo - Samples.Scoreboard
	@echo - Samples.DataBinding
	@echo - Samples.ApplicationTutorial
	@echo - Samples.Commands
	@echo - Samples.UserControl
	@echo - Samples.CustomControl
	@echo - Samples.BlendTutorial
	@echo - Samples.Menu3D
	@echo - Samples.Localization
	@echo - Samples.Inventory
	@echo - Samples.TicTacToe
	@echo - Samples.Gallery

NoesisApp: 
	@$(MAKE) --no-print-directory -C ../Src/NoesisApp/Projects/linux_x86_64

Gui.XamlPlayer: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Gui/XamlPlayer/Projects/linux_x86_64

Samples.Integration: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Integration/Projects/linux_x86_64

Samples.IntegrationGLUT: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/IntegrationGLUT/Projects/linux_x86_64

Samples.HelloWorld: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/HelloWorld/Projects/linux_x86_64

Samples.Buttons: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Buttons/Projects/linux_x86_64

Samples.Login: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Login/Projects/linux_x86_64

Samples.QuestLog: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/QuestLog/Projects/linux_x86_64

Samples.Scoreboard: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Scoreboard/Projects/linux_x86_64

Samples.DataBinding: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/DataBinding/Projects/linux_x86_64

Samples.ApplicationTutorial: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/ApplicationTutorial/Projects/linux_x86_64

Samples.Commands: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Commands/Projects/linux_x86_64

Samples.UserControl: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/UserControl/Projects/linux_x86_64

Samples.CustomControl: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/CustomControl/Projects/linux_x86_64

Samples.BlendTutorial: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/BlendTutorial/Projects/linux_x86_64

Samples.Menu3D: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Menu3D/Projects/linux_x86_64

Samples.Localization: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Localization/Projects/linux_x86_64

Samples.Inventory: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Inventory/Projects/linux_x86_64

Samples.TicTacToe: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/TicTacToe/Projects/linux_x86_64

Samples.Gallery: NoesisApp
	@$(MAKE) --no-print-directory -C ../Src/Packages/Samples/Gallery/Projects/linux_x86_64

