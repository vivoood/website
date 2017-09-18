/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#undef COMPONENT_FACTORY_NAMESPACE
// Set your factory namespace here:
#define COMPONENT_FACTORY_NAMESPACE CabinetConfig
//////////////////////////////////////////////////////////////////////

#undef MACRO_XSTR
#undef MACRO_STR
#undef FACTORY_NAMESPACE_STRING
//
#define MACRO_XSTR(x) #x
#define MACRO_STR(x) MACRO_XSTR(x)
#define FACTORY_NAMESPACE_STRING MACRO_STR(COMPONENT_FACTORY_NAMESPACE)
