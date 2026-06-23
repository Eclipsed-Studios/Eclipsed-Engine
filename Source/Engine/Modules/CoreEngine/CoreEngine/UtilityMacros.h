#pragma once

#define ECLIPSED_CLASS    \
	template<typename T>  \
	struct TypeInfo;

#define FRIEND_REFLECTION(cls) friend class TypeInfo<cls>;


#ifdef ECLIPSED_EDITOR
	#define check_asset_return(Var) if(!Var.IsValid()) { return; }
	#define check_return(Var) if(!Var) { return; }
	#define check(Var) if(!Var) { DebugBreak(); }
#else
	#define check_asset_return(Var)
	#define check_return(Var)
	#define check(Var)
#endif