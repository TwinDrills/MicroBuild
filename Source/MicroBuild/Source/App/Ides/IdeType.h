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

#pragma once

#include "Schemas/Database/DatabaseFile.h"
#include "Schemas/Workspace/WorkspaceFile.h"
#include "Schemas/Project/ProjectFile.h"
#include "Core/Helpers/TextStream.h"
#include "App/Ides/IdeHelper.h"

namespace MicroBuild {

// Base class for all IDE targets.
class IdeType
{
public:

	IdeType();
	virtual ~IdeType();

	// Gets the short-named use on the command line and in config files
	// to refer to this IDE.
	std::string GetShortName();

	// Takes a fully resolved workspace file and generates the project
	// files it defines.
	virtual bool Generate(
		DatabaseFile& databaseFile,
		WorkspaceFile& workspaceFile, 
		std::vector<ProjectFile>& projectFiles) = 0;

protected:

	void SetShortName(const std::string& value);

private:

	std::string m_shortName;

};

}; // namespace MicroBuild