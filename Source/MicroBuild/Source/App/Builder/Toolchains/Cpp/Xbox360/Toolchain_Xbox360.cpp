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
#include "App/Builder/Toolchains/Cpp/Xbox360/Toolchain_Xbox360.h"
#include "Core/Platform/Process.h"

namespace MicroBuild {

Toolchain_Xbox360::Toolchain_Xbox360(ProjectFile& file, uint64_t configurationHash)
	: Toolchain_Gcc(file, configurationHash)
{
}

bool Toolchain_Xbox360::Init() 
{
	m_bAvailable = FindToolchain();
	m_bRequiresCompileStep = true;
	m_description = Strings::Format("Xbox 360 (%s)", m_version.c_str());	
	return m_bAvailable;
}

bool Toolchain_Xbox360::FindToolchain()
{
	// todo
	return false;
}

}; // namespace MicroBuild