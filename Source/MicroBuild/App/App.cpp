/*
MicroBuild
Copyright (C) 2016 TwinDrills

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PCH.h"
#include "App/App.h"

#include "App/Commands/Generate.h"
#include "App/Commands/Build.h"
#include "App/Commands/Package.h"
#include "App/Commands/Clean.h"
#include "App/Commands/Help.h"
#include "App/Commands/Version.h"

#include "App/Ides/IdeType.h"

#include "App/Ides/MSBuild/VisualStudio_2015.h"
#include "App/Ides/Make/Make.h"
#include "App/Ides/XCode/XCode.h"
#include "App/Ides/MonoDevelop/MonoDevelop.h"
#include "App/Ides/NetBeans/NetBeans.h"
#include "App/Ides/QtCreator/QtCreator.h"
#include "App/Ides/CodeBlocks/CodeBlocks.h"
#include "App/Ides/SharpDevelop/SharpDevelop.h"
#include "App/Ides/CodeLite/CodeLite.h"

#include "Core/Config/ConfigFile.h"
#include "Core/Helpers/Time.h"
#include "Core/Helpers/Strings.h"

// x86
// x64
// anycpu
// winrt
// ios
// android
// emscripten
// ps4
// xboxone

// c++
// c#

// visual studio
// monodevelop
// netbeans
// qtcreator
// codeblocks
// sharpdevelop
// codelite
// make
// xcode

namespace MicroBuild {

App::App(int argc, char* argv[])    
	: m_argc(argc)
	, m_argv(argv)
	, m_commandLineParser(MB_NAME, MB_DESCRIPTION, MB_COPYRIGHT)
{
	m_ides.push_back(new Ide_VisualStudio_2015());
	m_ides.push_back(new Ide_MonoDevelop());
	m_ides.push_back(new Ide_NetBeans());
	m_ides.push_back(new Ide_QtCreator());
	m_ides.push_back(new Ide_CodeBlocks());
	m_ides.push_back(new Ide_SharpDevelop());
	m_ides.push_back(new Ide_CodeLite());
	m_ides.push_back(new Ide_Make());
	m_ides.push_back(new Ide_XCode());

	m_commandLineParser.RegisterCommand(new GenerateCommand(this));
	m_commandLineParser.RegisterCommand(new BuildCommand(this));
	m_commandLineParser.RegisterCommand(new PackageCommand(this));
	m_commandLineParser.RegisterCommand(new CleanCommand(this));
	m_commandLineParser.RegisterCommand(new HelpCommand(this));
	m_commandLineParser.RegisterCommand(new VersionCommand(this));
}

App::~App()
{
	for (IdeType* type : m_ides)
	{
		delete type;
	}

	m_ides.clear();
}

std::vector<IdeType*> App::GetIdes() const
{
	return m_ides;
}

IdeType* App::GetIdeByShortName(const std::string& shortName) const
{
	for (IdeType* type : m_ides)
	{
		if (Strings::CaseInsensitiveEquals(shortName, type->GetShortName()))
		{
			return type;
		}
	}
	return nullptr;
}

int App::Run()
{
	if (m_commandLineParser.Parse(m_argc, m_argv))
	{
		if (m_commandLineParser.HasCommands())
		{
			if (m_commandLineParser.DispatchCommands())
			{
				return 0;
			}
		}
		else
		{
			m_commandLineParser.PrintHelp();
		}
	}

	return 1;
}

} // namespace MicroBuild