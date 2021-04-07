'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
'WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
'INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
'OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
'PURPOSE

'------------------------------------------------------------------------------
'FILE DESCRIPTION: Script for registering for SMTP Protocol sinks. 
'
'File Name: smtpreg.vbs
' 
'
' Copyright (c) Microsoft Corporation 1993-1999. All rights reserved.
'------------------------------------------------------------------------------
Option Explicit

'
'
' the OnArrival event GUID
Const GUIDComCatOnArrival = "{ff3caa23-00b9-11d2-9dfb-00C04FA322BA}"
' the SMTP source type
Const GUIDSourceType = "{FB65C4DC-E468-11D1-AA67-00C04FA345F6}"
' 
Const GUIDCat = "{871736c0-fd85-11d0-869a-00c04fd65616}"
Const GUIDSources = "{DBC71A31-1F4B-11d0-869D-80C04FD65616}"

' the SMTP service display name.  This is used to key which service to
' edit
Const szService = "smtpsvc"

' the event manager object.  This is used to communicate with the 
' event binding database.
Dim EventManager
Set EventManager = WScript.CreateObject("Event.Manager")

'
' register a new sink with event manager
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name for this new sink
' szProgID - the progid to call for this event
' szRule - the rule to set for this event
'
public sub RegisterSink(iInstance, szEvent, szDisplayName, szProgID, szRule)
	Dim SourceType
	Dim szSourceDisplayName
	Dim Source
	Dim Binding
	Dim GUIDComCat
	Dim PrioVal

	' figure out which event they are trying to register with and set
	' the comcat for this event in GUIDComCat
	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select
	' enumerate through each of the registered instances for the SMTP source
	' type and look for the display name that matches the instance display
	' name
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' we've found the desired instance.  now add a new binding
			' with the right event GUID.  by not specifying a GUID to the
			' Add method we get server events to create a new ID for this
			' event
			set Binding = Source.GetBindingManager.Bindings(GUIDComCat).Add("")
			' set the binding properties
			Binding.DisplayName = szDisplayName
			Binding.SinkClass = szProgID
			' register a rule with the binding
			Binding.SourceProperties.Add "Rule", szRule
			' register a priority with the binding
			PrioVal = GetNextPrio(Source, GUIDComCat)
			If PrioVal < 0 then
				WScript.Echo "assigning priority to default value (24575)"
				Binding.SourceProperties.Add "Priority", 24575
			else	
				WScript.Echo "assigning priority (" & PrioVal & " of 32767)"
				Binding.SourceProperties.Add "Priority", PrioVal
			end if
			' save the binding
			Binding.Save
			WScript.Echo "registered " & szDisplayName
			exit sub
		end if
	next
end sub

'
' iterate through the bindings in a source, find the binding
' with the lowest priority, and return the next priority value.
' If the next value exceeds the range, return -1.
'
public function GetNextPrio(oSource, GUIDComCat)
	' it's possible that priority values will not be
	' numbers, so we add error handling for this case
	on error resume next

	Dim Bindings
	Dim Binding
	Dim nLowestPrio
	Dim nPrioVal
	nLowestPrio = 0
	set Bindings = oSource.GetBindingManager.Bindings(GUIDComCat)
	' if the bindings collection is empty, then this is the first
	' sink.  It gets the highest priority (0).
	if Bindings.Count = 0 then
		GetNextPrio = 0
	else
		' get the lowest existing priority value
		for each Binding in Bindings
			nPrioVal = Binding.SourceProperties.Item("Priority")
			if CInt(nPrioVal) > nLowestPrio then
				if err.number = 13 then
					err.clear
				else
					nLowestPrio = CInt(nPrioVal)
				end if
			end if
		next 
		' assign priority values in increments of 10 so priorities
		' can be shuffled later without the need to reorder all
		' binding priorities.  Valid priority values are 0 - 32767
		if nLowestPrio + 10 > 32767 then
			GetNextPrio = -1
		else
			GetNextPrio = nLowestPrio + 10
		end if
	end if
end function  

'
' check for a previously registered sink with the passed in name
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name of the event to check
' bCheckError - Any errors returned
public sub CheckSink(iInstance, szEvent, szDisplayName, bCheckError)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	bCheckError = FALSE
	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now log an error
					WScript.Echo "Binding with the name " & szDisplayName & " already exists"
					exit sub 
				end if
			next
		end if
	next
	bCheckError = TRUE
end sub

'
' unregister a previously registered sink
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name of the event to remove
'
public sub UnregisterSink(iInstance, szEvent, szDisplayName)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now remove it
					Bindings.Remove(Binding.ID)
					WScript.Echo "removed " & szDisplayName & " " & Binding.ID
				end if
			next
		end if
	next
end sub

'
' add or remove a property from the source or sink propertybag for an event
'
' iInstance - the SMTP instance to edit
' szEvent - the event type (OnArrival)
' szDisplayName - the display name of the event
' szPropertyBag - the property bag to edit ("source" or "sink")
' szOperation - "add" or "remove"
' szPropertyName - the name to edit in the property bag
' szPropertyValue - the value to assign to the name (ignored for remove)
'
public sub EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, szOperation, szPropertyName, szPropertyValue)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding
	Dim PropertyBag

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' figure out which set of properties we want to modify
					' based on the szPropertyBag parameter
					select case LCase(szPropertyBag)
						case "source"
							set PropertyBag = Binding.SourceProperties
						case "sink"
							set PropertyBag = Binding.SinkProperties
						case else
							WScript.echo "invalid propertybag: " & szPropertyBag
							exit sub
					end select
					' figure out what operation we want to perform
					select case LCase(szOperation)
						case "remove"
							' they want to remove szPropertyName from the
							' property bag
							PropertyBag.Remove szPropertyName
							WScript.echo "removed property " & szPropertyName
						case "add"
							' add szPropertyName to the property bag and 
							' set its value to szValue.  if this value
							' already exists then this will change  the value
							' it to szValue.
							PropertyBag.Add szPropertyName, szPropertyValue
							WScript.echo "set property " & szPropertyName & " to " & szPropertyValue
						case else
							WScript.echo "invalid operation: " & szOperation
							exit sub
					end select
					' save the binding
					Binding.Save
				end if
			next
		end if
	next
end sub

'
' this helper function takes an IEventSource object and a event category
' and dumps all of the bindings for this category under the source
'
' Source - the IEventSource object to display the bindings for
' GUIDComCat - the event category to display the bindings for
'
public sub DisplaySinksHelper(Source, GUIDComCat)
	Dim Binding
	Dim propval
	' walk each of the registered bindings for this component category
	for each Binding in Source.GetBindingManager.Bindings(GUIDComCat)
		' display the binding properties
		WScript.echo "    Binding " & Binding.ID & " {"
		WScript.echo "      DisplayName = " & Binding.DisplayName
		WScript.echo "      SinkClass = " & Binding.SinkClass
		if Binding.Enabled = True then
			WScript.echo "      Status = Enabled"
		else
			WScript.echo "      Status = Disabled"
		end if

		' walk each of the source properties and display them
		WScript.echo "      SourceProperties {"
		for each propval in Binding.SourceProperties
			WScript.echo "        " & propval & " = " & Binding.SourceProperties.Item(propval)
		next
		WScript.echo "      }"

		' walk each of the sink properties and display them
		WScript.echo "      SinkProperties {"
		for each Propval in Binding.SinkProperties
			WScript.echo "        " & propval & " = " & Binding.SinkProperties.Item(Propval)
		next
		WScript.echo "      }"
		WScript.echo "    }"
	next
end sub

'
' dumps all of the information in the binding database related to SMTP
'
public sub DisplaySinks
	Dim SourceType
	Dim Source

	' look for each of the sources registered for the SMTP source type
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	for each Source in SourceType.Sources
		' display the source properties
		WScript.echo "Source " & Source.ID & " {"
		WScript.echo "  DisplayName = " & Source.DisplayName
		' display all of the sinks registered for the OnArrival event
		WScript.echo "  OnArrival Sinks {"
		call DisplaySinksHelper(Source, GUIDComCatOnArrival)
		WScript.echo "  }"
	next
end sub

'
' enable/disable a registered sink
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name for this new sink
'
public sub SetSinkEnabled(iInstance, szEvent, szDisplayName, szEnable)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " + szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService + " " + iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now enable/disable it
					' we don't need "case else' because szEnable's value
					' is set internally, not by users
					select case LCase(szEnable)
						case "true"
							Binding.Enabled = True
							Binding.Save
							WScript.Echo "enabled " + szDisplayName + " " + Binding.ID
						case "false"
							Binding.Enabled = False
							Binding.Save
							WScript.Echo "disabled " + szDisplayName + " " + Binding.ID
						end select
				end if
			next
		end if
	next
end sub

' 
' display usage information for this script
'
public sub DisplayUsage
	WScript.echo "usage: cscript smtpreg.vbs <command> <arguments>"
	WScript.echo "  commands:"
	WScript.echo "    /add <Instance> <Event> <DisplayName> <SinkClass> <Rule>"
	WScript.echo "    /remove <Instance> <Event> <DisplayName>"
	WScript.echo "    /setprop <Instance> <Event> <DisplayName> <PropertyBag> <PropertyName> "
	WScript.echo "             <PropertyValue>"
	WScript.echo "    /delprop <Instance> <Event> <DisplayName> <PropertyBag> <PropertyName>"
	WScript.echo "    /enable <Instance> <Event> <DisplayName>"
	WScript.echo "    /disable <Instance> <Event> <DisplayName>"
	WScript.echo "    /enum"
	WScript.echo "  arguments:"
	WScript.echo "    <Instance> is the SMTP instance to work against"
	WScript.echo "    <Event> can be OnArrival"
	WScript.echo "    <DisplayName> is the display name of the event to edit"
	WScript.echo "    <SinkClass> is the sink class for the event"
	WScript.echo "    <Rule> is the rule to use for the event"	
	WScript.echo "    <PropertyBag> can be Source or Sink"
	WScript.echo "    <PropertyName> is the name of the property to edit"
	WScript.echo "    <PropertyValue> is the value to assign to the property"
end sub


Dim iInstance
Dim szEvent
Dim szDisplayName
Dim szSinkClass
Dim szRule
Dim szPropertyBag
Dim szPropertyName
Dim szPropertyValue
dim bCheck

'
' this is the main body of our script.  it reads the command line parameters
' specified and then calls the appropriate function to perform the operation
'
if WScript.Arguments.Count = 0 then
	call DisplayUsage
else 
	Select Case LCase(WScript.Arguments(0))
		Case "/add"
			if not WScript.Arguments.Count = 6 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szSinkClass = WScript.Arguments(4)
				szRule = WScript.Arguments(5)
				call CheckSink(iInstance, szEvent, szDisplayName, bCheck)
				if bCheck = TRUE then
					call RegisterSink(iInstance, szEvent, szDisplayName, szSinkClass, szRule)
				End if
			end if
		Case "/remove"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call UnregisterSink(iInstance, szEvent, szDisplayName)
			end if	
		Case "/setprop"
			if not WScript.Arguments.Count = 7 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szPropertyBag = WScript.Arguments(4)
				szPropertyName = WScript.Arguments(5)
				szPropertyValue = WScript.Arguments(6)
				call EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, "add", szPropertyName, szPropertyValue)
			end if
		Case "/delprop"
			if not WScript.Arguments.Count = 6 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szPropertyBag = WScript.Arguments(4)
				szPropertyName = WScript.Arguments(5)
				call EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, "remove", szPropertyName, "")		
			end if
		Case "/enable"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call SetSinkEnabled(iInstance, szEvent, szDisplayName, "True")
			end if
		Case "/disable"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call SetSinkEnabled(iInstance, szEvent, szDisplayName, "False")
			end if
		Case "/enum"
			if not WScript.Arguments.Count = 1 then
				call DisplayUsage
			else
				call DisplaySinks
			end if
		Case Else
			call DisplayUsage
	End Select
end if
