#!/usr/bin/python
import sys
import os.path
import random
import time

from datetime import datetime

random.seed(datetime.now())
epoch_time = int(time.time())

if (len(sys.argv) > 3) or (len(sys.argv) < 2) :
	print "--- debug(1)"
	print "Please specify component name, WITHOUT 'Component' in the end!"
	print "Or use 'create_component -remove compName'"
	print "Or use 'create_component -init_factory'"
	print "Example:"
	print "create_component GameResources"
	print "will create GameResourcesComponent class in GameResourcesComponent.cpp and GameResourcesComponent.h files"
	print "and will register GameResources component in component factory."
	sys.exit()

commandStr = sys.argv[1]
compName = ""
compNameUpperCase = ""

if (commandStr[0] == '-'):
	if (len(sys.argv) == 3):
		compName = sys.argv[2]
else:
	# no command
	compName = commandStr
	commandStr = ""

compNameUpperCase = compName.upper()

compDirectoryName = "./"
factoryDirectoryName = "Settings/"
factorySysDirectoryName = "System/"
compCPPFile = compName + "Component.cpp"
compHFile = compName + "Component.h"
registerString = "    CUSTOM_COMPONENT_MACRO(" + compName + ", foo)\\"
registerMarkerString = "// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT REGISTER MARKER"
includeMarkerString = "// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT INCLUDE MARKER"

initCheckString = "#define CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK"
namespaceChangedCheck = "#define COMPONENT_FACTORY_NAMESPACE EmptyFactoryNamespace"
randomStr = str(epoch_time)

# Find root folder
# ############################


fullPath = os.getcwd()
innerPath = ""

pathInfo = os.path.split(fullPath)
rootFolder = ""
searchDepth = 0
while True:
	if os.path.isfile(rootFolder + factoryDirectoryName + "ComponentsList.h") == True:
		break;
	rootFolder = rootFolder + "../"
	innerPath = pathInfo[1] + "/" + innerPath
	pathInfo = os.path.split(pathInfo[0])
	if searchDepth == 4:
		print "Cant find factory root directory."
		print "Maybe your subfolder is too deep."
		sys.exit()
	searchDepth = searchDepth + 1

includeString = "#include \"../" + innerPath + compHFile + "\""

if (commandStr == ""):
#{
	# No command, so we'll create a new component

	# First check if factory is inited
	with open(rootFolder + factoryDirectoryName + "ComponentsList.h") as f:
		checkContent = f.readlines()
	for ln in checkContent:
		if initCheckString in ln:
			print "Please init factory first !"
			print "Use : 'create_component -init_factory'"
			sys.exit()

	# Check if factory namespace is changed
	with open(rootFolder + factoryDirectoryName + "Defines.h") as f:
		nsCheckContent = f.readlines()
	for ln in nsCheckContent:
		if namespaceChangedCheck in ln:
			print "Please change your namespace name !"
			print "Edit './Settings/Defines.h' file."
			sys.exit()

	# now we can create the new component
	print compCPPFile
	print compHFile

	if os.path.isfile(compDirectoryName + compCPPFile) == True or os.path.isfile(compDirectoryName + compHFile):
		print "Component already exist!"
		sys.exit()

	print compName

	# ARegister component
	f = open(rootFolder + factoryDirectoryName + "ComponentsList.h", 'r')
	factoryData = f.read()
	f.close()

	if registerString in factoryData:
		print "Component already registered in ComponentsList.h"
		sys.exit()

	factoryData = factoryData.replace(registerMarkerString, registerString + "\n" + registerMarkerString);

	# Add include header
	f = open(rootFolder + factoryDirectoryName + "ComponentsIncludeList.h", 'r')
	factoryIncludeData = f.read()
	f.close()

	if includeString in factoryData:
		print "Component already included in ComponentsIncludeList.h"
		sys.exit()

	factoryIncludeData = factoryIncludeData.replace(includeMarkerString, includeString + "\n" + includeMarkerString);

	# Save files
	f = open(rootFolder + factoryDirectoryName + "ComponentsList.h", 'w')
	f.write(factoryData)
	f.close()

	f = open(rootFolder + factoryDirectoryName + "ComponentsIncludeList.h", 'w')
	f.write(factoryIncludeData)
	f.close()

	# Read component template header
	f = open(rootFolder + factorySysDirectoryName + "empty_comp_h",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("$$CompName$$",compName)
	newdata = newdata.replace("$$COMPNAME$$",compNameUpperCase)
	newdata = newdata.replace("$$RANDOM$$", randomStr) 
	newdata = newdata.replace("$$RootDir$$", rootFolder)

	f = open(compDirectoryName + compHFile,'w')
	f.write(newdata)
	f.close()

	# Read component template cpp
	f = open(rootFolder + factorySysDirectoryName + "empty_comp_cpp",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("$$CompName$$",compName)
	newdata = newdata.replace("$$COMPNAME$$",compNameUpperCase)
	newdata = newdata.replace("$$RANDOM$$", randomStr)
	newdata = newdata.replace("$$RootDir$$", rootFolder)

	f = open(compDirectoryName + compCPPFile,'w')
	f.write(newdata)
	f.close()
	print "Component ready!"
	sys.exit()
#}
elif (commandStr == "-remove"):
#{
	# Remove component register
	with open(rootFolder + factoryDirectoryName + "ComponentsList.h") as f:
		content = f.readlines()
	newContent = list()
	for ln in content:
		if registerString in ln:
			continue
		newContent.append(ln)
	
	f = open(rootFolder + factoryDirectoryName + "ComponentsList.h",'w')
	for item in newContent:
		f.write("%s" % item)
	f.close()
	# Remove component include
	with open(rootFolder + factoryDirectoryName + "ComponentsIncludeList.h") as f:
		content = f.readlines()
	newContent = list()
	for ln in content:
		if includeString in ln:
			continue
		newContent.append(ln)

	f = open(rootFolder + factoryDirectoryName + "ComponentsIncludeList.h",'w')
	for item in newContent:
		f.write("%s" % item)
	f.close()

	os.remove(compDirectoryName + compHFile);
	os.remove(compDirectoryName + compCPPFile);
	print "Component removed!"
	sys.exit()
#}
elif (commandStr == "-init_factory"):
#{
	# Init manager
	# ##############################################################
	# ComponentsFactory.h
	f = open(factorySysDirectoryName + "ComponentsFactory.h",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("EMPTYLOCK", randomStr) 

	f = open(factorySysDirectoryName + "ComponentsFactory.h",'w')
	f.write(newdata)
	f.close()
	# ##############################################################
	# ComponentsFactory.cpp
	f = open(factorySysDirectoryName + "ComponentsFactory.cpp",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("EMPTYLOCK", randomStr)

	f = open(factorySysDirectoryName + "ComponentsFactory.cpp",'w')
	f.write(newdata)
	f.close()
	# ##############################################################
	# ComponentsList.h
	f = open(factoryDirectoryName + "ComponentsList.h",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("EMPTYLOCK", randomStr)

	f = open(factoryDirectoryName + "ComponentsList.h",'w')
	f.write(newdata)
	f.close()
	# ##############################################################
	print "Init ready!"
	sys.exit()
#}

print "--- debug(2)"
print "Please specify component name, WITHOUT 'Component' in the end!"
print "Or use 'create_component -remove compName'"
print "Or use 'create_component -init_factory'"
print "Example:"
print "create_component GameResources"
print "will create GameResourcesComponent class in GameResourcesComponent.cpp and GameResourcesComponent.h files"
print "and will register GameResources component in component factory."
sys.exit()
